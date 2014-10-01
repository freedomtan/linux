/*
 * drivers/base/power/cpu_domains.c - Helper functions to create CPU PM domains.
 *
 * Copyright (C) 2016 Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/cpu.h>
#include <linux/cpu_domains.h>
#include <linux/cpu_pm.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/of.h>
#include <linux/pm_domain.h>
#include <linux/rculist.h>
#include <linux/rcupdate.h>
#include <linux/slab.h>

#define CPU_PD_NAME_MAX 36

struct cpu_pm_domain {
	struct list_head link;
	struct cpu_pd_ops ops;
	struct generic_pm_domain *genpd;
	struct cpu_pm_domain *parent;
};

/* List of CPU PM domains we care about */
static LIST_HEAD(of_cpu_pd_list);
static DEFINE_MUTEX(cpu_pd_list_lock);

static inline
struct cpu_pm_domain *to_cpu_pd(struct generic_pm_domain *d)
{
	struct cpu_pm_domain *pd;
	struct cpu_pm_domain *res = NULL;

	rcu_read_lock();
	list_for_each_entry_rcu(pd, &of_cpu_pd_list, link)
		if (pd->genpd == d) {
			res = pd;
			break;
		}
	rcu_read_unlock();

	return res;
}

static int cpu_pd_attach_cpu(int cpu)
{
	int ret;
	struct device *cpu_dev;

	cpu_dev = get_cpu_device(cpu);
	if (!cpu_dev) {
		pr_warn("%s: Unable to get device for CPU%d\n",
				__func__, cpu);
		return -ENODEV;
	}

	ret = genpd_dev_pm_attach(cpu_dev);
	if (ret)
		dev_warn(cpu_dev,
			"%s: Unable to attach to power-domain: %d\n",
			__func__, ret);
	else
		dev_dbg(cpu_dev, "Attached to domain\n");

	return ret;
}

static int cpu_pd_power_on(struct generic_pm_domain *genpd)
{
	struct cpu_pm_domain *pd = to_cpu_pd(genpd);

	return pd->ops.power_on ? pd->ops.power_on() : 0;
}

static int cpu_pd_power_off(struct generic_pm_domain *genpd)
{
	struct cpu_pm_domain *pd = to_cpu_pd(genpd);

	return pd->ops.power_off ? pd->ops.power_off(genpd->state_idx,
					genpd->states[genpd->state_idx].param),
					: 0;
}

/**
 * of_init_cpu_pm_domain() - Initialize a CPU PM domain from a device node
 *
 * @dn: The domain provider's device node
 * @ops: The power_on/_off callbacks for the domain
 *
 * Returns the generic_pm_domain (genpd) pointer to the domain on success
 */
static struct generic_pm_domain *of_init_cpu_pm_domain(struct device_node *dn,
				const struct cpu_pd_ops *ops)
{
	struct cpu_pm_domain *pd = NULL;
	struct generic_pm_domain *genpd = NULL;
	int ret = -ENOMEM;

	if (!of_device_is_available(dn))
		return ERR_PTR(-ENODEV);

	genpd = kzalloc(sizeof(*genpd), GFP_KERNEL);
	if (!genpd)
		goto fail;

	genpd->name = kstrndup(dn->full_name, CPU_PD_NAME_MAX, GFP_KERNEL);
	if (!genpd->name)
		goto fail;

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		goto fail;

	pd->genpd = genpd;
	pd->genpd->power_off = cpu_pd_power_off;
	pd->genpd->power_on = cpu_pd_power_on;
	pd->genpd->flags |= GENPD_FLAG_IRQ_SAFE;
	pd->ops.power_on = ops->power_on;
	pd->ops.power_off = ops->power_off;

	INIT_LIST_HEAD_RCU(&pd->link);
	mutex_lock(&cpu_pd_list_lock);
	list_add_rcu(&pd->link, &of_cpu_pd_list);
	mutex_unlock(&cpu_pd_list_lock);

	/* Register the CPU genpd */
	pr_debug("adding %s as CPU PM domain\n", pd->genpd->name);
	ret = of_pm_genpd_init(dn, pd->genpd, &simple_qos_governor, false);
	if (ret) {
		pr_err("Unable to initialize domain %s\n", dn->full_name);
		goto fail;
	}

	ret = of_genpd_add_provider_simple(dn, pd->genpd);
	if (ret)
		pr_warn("Unable to add genpd %s as provider\n",
				pd->genpd->name);

	return pd->genpd;
fail:

	kfree(genpd->name);
	kfree(genpd);
	kfree(pd);
	return ERR_PTR(ret);
}

static struct generic_pm_domain *of_get_cpu_domain(struct device_node *dn,
		const struct cpu_pd_ops *ops, int cpu)
{
	struct of_phandle_args args;
	struct generic_pm_domain *genpd, *parent;
	struct cpu_pm_domain *cpu_pd, *parent_cpu_pd;
	int ret;

	/* Do we have this domain? If not, create the domain */
	args.np = dn;
	args.args_count = 0;

	genpd = of_genpd_get_from_provider(&args);
	if (!IS_ERR(genpd))
		return genpd;

	genpd = of_init_cpu_pm_domain(dn, ops);
	if (IS_ERR(genpd))
		return genpd;

	/* Is there a domain provider for this domain? */
	ret = of_parse_phandle_with_args(dn, "power-domains",
			"#power-domain-cells", 0, &args);
	if (ret < 0)
		goto skip_parent;

	/* Find its parent and attach this domain to it, recursively */
	parent = of_get_cpu_domain(args.np, ops, cpu);
	if (IS_ERR(parent))
		goto skip_parent;

	ret = pm_genpd_add_subdomain(genpd, parent);
	if (ret) {
		pr_err("%s: Unable to add sub-domain (%s)\n err: %d",
				__func__, genpd->name, ret);
		return ERR_PTR(ret);
	}

	/*
	 * Reference parent domain for easy access.
	 * Note: We could be attached to a domain that is not a
	 * CPU PM domain in that case don't reference the parent.
	 */
	cpu_pd = to_cpu_pd(genpd);
	parent_cpu_pd = to_cpu_pd(parent);

	if (cpu_pd && parent_cpu_pd)
		cpu_pd->parent = parent_cpu_pd;

skip_parent:
	of_node_put(dn);
	return genpd;
}

/**
 * of_setup_cpu_pd_single() - Setup the PM domains for a CPU
 *
 * @cpu: The CPU for which the PM domain is to be set up.
 * @ops: The PM domain suspend/resume ops for the CPU's domain
 *
 * If the CPU PM domain exists already, then the CPU is attached to
 * that CPU PD. If it doesn't, the domain is created, the @ops are
 * set for power_on/power_off callbacks and then the CPU is attached
 * to that domain. If the domain was created outside this framework,
 * then we do not attach the CPU to the domain.
 */
int of_setup_cpu_pd_single(int cpu, const struct cpu_pd_ops *ops)
{

	struct device_node *dn;
	struct generic_pm_domain *genpd;

	dn = of_get_cpu_node(cpu, NULL);
	if (!dn)
		return -ENODEV;

	dn = of_parse_phandle(dn, "power-domains", 0);
	if (!dn)
		return -ENODEV;

	/* Find the genpd for this CPU, create if not found */
	genpd = of_get_cpu_domain(dn, ops, cpu);
	if (IS_ERR(genpd))
		return PTR_ERR(genpd);

	of_node_put(dn);
	return cpu_pd_attach_cpu(cpu);
}
EXPORT_SYMBOL(of_setup_cpu_pd_single);

/**
 * of_setup_cpu_pd() - Setup the PM domains for all CPUs
 *
 * @ops: The PM domain suspend/resume ops for all the domains
 *
 * Setup the CPU PM domain and attach all possible CPUs to their respective
 * domains. The domains are created if not already and then attached.
 */
int of_setup_cpu_pd(const struct cpu_pd_ops *ops)
{
	int cpu;
	int ret;

	for_each_possible_cpu(cpu) {
		ret = of_setup_cpu_pd_single(cpu, ops);
		if (ret)
			break;
	}

	return ret;
}
EXPORT_SYMBOL(of_setup_cpu_pd);
