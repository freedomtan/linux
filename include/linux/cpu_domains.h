/*
 * include/linux/cpu_domains.h
 *
 * Copyright (C) 2016 Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __CPU_DOMAINS_H__
#define __CPU_DOMAINS_H__

#include <linux/types.h>

struct cpumask;

struct cpu_pd_ops {
	int (*power_off)(u32 state_idx, u32 param, const struct cpumask *mask);
	int (*power_on)(void);
};

#ifdef CONFIG_PM_GENERIC_DOMAINS_OF
int of_setup_cpu_pd_single(int cpu, const struct cpu_pd_ops *ops);
int of_setup_cpu_pd(const struct cpu_pd_ops *ops);
#else
static inline int of_setup_cpu_pd_single(int cpu, const struct cpu_pd_ops *ops)
{
	return -ENODEV;
}
static inline int of_setup_cpu_pd(const struct cpu_pd_ops *ops)
{
	return -ENODEV;
}
#endif /* CONFIG_PM_GENERIC_DOMAINS_OF */

#endif /* __CPU_DOMAINS_H__ */
