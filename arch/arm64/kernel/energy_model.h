/*
 * arch/arm64/kernel/energy_model.h
 *
 * Copyright (C) 2016 ARM Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <linux/of_fdt.h>

/*
 * Energy cost model data. There are no unit requirements for the data.
 * Data can be normalized to any reference point, but the normalization
 * must be consistent. That is, one bogo-joule/watt must be the same
 * quantity for all data, but we don't care what it is.
 */

/* Juno (r0, r2) */

static struct idle_state idle_states_cluster_juno_a53[] = {
	{ .power = 56 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 56 }, /* WFI */
	{ .power = 56 }, /* cpu-sleep-0 */
	{ .power = 17 }, /* cluster-sleep-0 */
};

static struct idle_state idle_states_cluster_juno_a57[] = {
	{ .power = 65 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 65 }, /* WFI */
	{ .power = 65 }, /* cpu-sleep-0 */
	{ .power = 24 }, /* cluster-sleep-0 */
};

static struct capacity_state cap_states_cluster_juno_a53[] = {
	{ .cap =  235, .power = 26, }, /*  450 MHz */
	{ .cap =  303, .power = 30, }, /*  575 MHz */
	{ .cap =  368, .power = 39, }, /*  700 MHz */
	{ .cap =  406, .power = 47, }, /*  775 MHz */
	{ .cap =  447, .power = 57, }, /*  850 Mhz */
};

static struct capacity_state cap_states_cluster_juno_a57[] = {
	{ .cap =  417, .power = 24, }, /*  450 MHz */
	{ .cap =  579, .power = 32, }, /*  625 MHz */
	{ .cap =  744, .power = 43, }, /*  800 MHz */
	{ .cap =  883, .power = 49, }, /*  950 MHz */
	{ .cap = 1024, .power = 64, }, /* 1100 MHz */
};

static struct sched_group_energy energy_cluster_juno_a53 = {
	.nr_idle_states = ARRAY_SIZE(idle_states_cluster_juno_a53),
	.idle_states    = idle_states_cluster_juno_a53,
	.nr_cap_states  = ARRAY_SIZE(cap_states_cluster_juno_a53),
	.cap_states     = cap_states_cluster_juno_a53,
};

static struct sched_group_energy energy_cluster_juno_a57 = {
	.nr_idle_states = ARRAY_SIZE(idle_states_cluster_juno_a57),
	.idle_states    = idle_states_cluster_juno_a57,
	.nr_cap_states  = ARRAY_SIZE(cap_states_cluster_juno_a57),
	.cap_states     = cap_states_cluster_juno_a57,
};

static struct idle_state idle_states_core_juno_a53[] = {
	{ .power = 6 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 6 }, /* WFI */
	{ .power = 0 }, /* cpu-sleep-0 */
	{ .power = 0 }, /* cluster-sleep-0 */
};

static struct idle_state idle_states_core_juno_a57[] = {
	{ .power = 15 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 15 }, /* WFI */
	{ .power = 0  }, /* cpu-sleep-0 */
	{ .power = 0  }, /* cluster-sleep-0 */
};

static struct capacity_state cap_states_core_juno_a53[] = {
	{ .cap =  235, .power =  33, }, /*  450 MHz */
	{ .cap =  302, .power =  46, }, /*  575 MHz */
	{ .cap =  368, .power =  61, }, /*  700 MHz */
	{ .cap =  406, .power =  76, }, /*  775 MHz */
	{ .cap =  447, .power =  93, }, /*  850 Mhz */
};

static struct capacity_state cap_states_core_juno_a57[] = {
	{ .cap =  417, .power = 168, }, /*  450 MHz */
	{ .cap =  579, .power = 251, }, /*  625 MHz */
	{ .cap =  744, .power = 359, }, /*  800 MHz */
	{ .cap =  883, .power = 479, }, /*  950 MHz */
	{ .cap = 1024, .power = 616, }, /* 1100 MHz */
};

static struct sched_group_energy energy_core_juno_a53 = {
	.nr_idle_states = ARRAY_SIZE(idle_states_core_juno_a53),
	.idle_states    = idle_states_core_juno_a53,
	.nr_cap_states  = ARRAY_SIZE(cap_states_core_juno_a53),
	.cap_states     = cap_states_core_juno_a53,
};

static struct sched_group_energy energy_core_juno_a57 = {
	  .nr_idle_states = ARRAY_SIZE(idle_states_core_juno_a57),
	  .idle_states    = idle_states_core_juno_a57,
	  .nr_cap_states  = ARRAY_SIZE(cap_states_core_juno_a57),
	  .cap_states     = cap_states_core_juno_a57,
};

/* MT8173 */
static struct idle_state idle_states_cluster_mt8173_a53[] = {
	{ .power = 184 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 184 }, /* WFI */
	{ .power = 147 }, /* cpu-sleep-0 */
	{ .power = 4 }, /* cluster-sleep-0 */
};

static struct idle_state idle_states_cluster_mt8173_a57[] = {
	{ .power = 171 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 171 }, /* WFI */
	{ .power = 100 }, /* cpu-sleep-0 */
	{ .power = 18 }, /* cluster-sleep-0 */
};

static struct capacity_state cap_states_cluster_mt8173_a53[] = {
	{ .cap =  184, .power = 174, },
	{ .cap =  256, .power = 107, },
	{ .cap =  368, .power = 138, },
	{ .cap =  399, .power = 145, },
	{ .cap =  430, .power = 144, },
	{ .cap =  512, .power = 150, },
	{ .cap =  552, .power = 165, },
	{ .cap =  573, .power = 164, },
};

static struct capacity_state cap_states_cluster_mt8173_a57[] = {
	{ .cap =  256, .power = 56, },
	{ .cap =  358, .power = 89, },
	{ .cap =  512, .power = 78, },
	{ .cap =  614, .power = 47, },
	{ .cap =  716, .power = 101, },
	{ .cap =  819, .power = 122, },
	{ .cap =  921, .power = 103, },
	{ .cap =  1024, .power = 150, },
};

static struct sched_group_energy energy_cluster_mt8173_a53 = {
	.nr_idle_states = ARRAY_SIZE(idle_states_cluster_mt8173_a53),
	.idle_states    = idle_states_cluster_mt8173_a53,
	.nr_cap_states  = ARRAY_SIZE(cap_states_cluster_mt8173_a53),
	.cap_states     = cap_states_cluster_mt8173_a53,
};

static struct sched_group_energy energy_cluster_mt8173_a57 = {
	.nr_idle_states = ARRAY_SIZE(idle_states_cluster_mt8173_a57),
	.idle_states    = idle_states_cluster_mt8173_a57,
	.nr_cap_states  = ARRAY_SIZE(cap_states_cluster_mt8173_a57),
	.cap_states     = cap_states_cluster_mt8173_a57,
};

static struct idle_state idle_states_core_mt8173_a53[] = {
	{ .power = 6 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 6 }, /* WFI */
	{ .power = 0 }, /* cpu-sleep-0 */
	{ .power = 0 }, /* cluster-sleep-0 */
};

static struct idle_state idle_states_core_mt8173_a57[] = {
	{ .power = 15 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 15 }, /* WFI */
	{ .power = 0  }, /* cpu-sleep-0 */
	{ .power = 0  }, /* cluster-sleep-0 */
};

static struct capacity_state cap_states_core_mt8173_a53[] = {
	{ .cap =  184, .power = 57, },
	{ .cap =  256, .power = 156, },
	{ .cap =  368, .power = 255, },
	{ .cap =  399, .power = 299, },
	{ .cap =  430, .power = 339, },
	{ .cap =  512, .power = 472, },
	{ .cap =  552, .power = 529, },
	{ .cap =  573, .power = 574, },
};

static struct capacity_state cap_states_core_mt8173_a57[] = {
	{ .cap =  256, .power = 316, },
	{ .cap =  358, .power = 374, },
	{ .cap =  512, .power = 640, },
	{ .cap =  614, .power = 885, },
	{ .cap =  716, .power = 1079, },
	{ .cap =  819, .power = 1376, },
	{ .cap =  921, .power = 1738, },
	{ .cap =  1024, .power = 2207, },
};

static struct sched_group_energy energy_core_mt8173_a53 = {
	.nr_idle_states = ARRAY_SIZE(idle_states_core_mt8173_a53),
	.idle_states    = idle_states_core_mt8173_a53,
	.nr_cap_states  = ARRAY_SIZE(cap_states_core_mt8173_a53),
	.cap_states     = cap_states_core_mt8173_a53,
};

static struct sched_group_energy energy_core_mt8173_a57 = {
	.nr_idle_states = ARRAY_SIZE(idle_states_core_mt8173_a57),
	.idle_states    = idle_states_core_mt8173_a57,
	.nr_cap_states  = ARRAY_SIZE(cap_states_core_mt8173_a57),
	.cap_states     = cap_states_core_mt8173_a57,
};

/* MT6797 */
static struct idle_state idle_states_cluster_mt6797_LL[] = {
	{ .power = 184 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 184 }, /* WFI */
	{ .power = 147 }, /* cpu-sleep-0 */
	{ .power = 4 }, /* cluster-sleep-0 */
};

static struct idle_state idle_states_cluster_mt6797_L[] = {
	{ .power = 184 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 184 }, /* WFI */
	{ .power = 147 }, /* cpu-sleep-0 */
	{ .power = 4 }, /* cluster-sleep-0 */
};

static struct idle_state idle_states_cluster_mt6797_b[] = {
	{ .power = 171 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 171 }, /* WFI */
	{ .power = 100 }, /* cpu-sleep-0 */
	{ .power = 18 }, /* cluster-sleep-0 */
};

static struct capacity_state cap_states_cluster_mt6797_LL[] = {
	{ .cap =  184, .power = 174, },
	{ .cap =  256, .power = 107, },
	{ .cap =  368, .power = 138, },
	{ .cap =  399, .power = 145, },
	{ .cap =  430, .power = 144, },
	{ .cap =  512, .power = 150, },
	{ .cap =  552, .power = 165, },
	{ .cap =  573, .power = 164, },
};

static struct capacity_state cap_states_cluster_mt6797_L[] = {
	{ .cap =  184, .power = 174, },
	{ .cap =  256, .power = 107, },
	{ .cap =  368, .power = 138, },
	{ .cap =  399, .power = 145, },
	{ .cap =  430, .power = 144, },
	{ .cap =  512, .power = 150, },
	{ .cap =  552, .power = 165, },
	{ .cap =  573, .power = 164, },
};

static struct capacity_state cap_states_cluster_mt6797_b[] = {
	{ .cap =  256, .power = 56, },
	{ .cap =  358, .power = 89, },
	{ .cap =  512, .power = 78, },
	{ .cap =  614, .power = 47, },
	{ .cap =  716, .power = 101, },
	{ .cap =  819, .power = 122, },
	{ .cap =  921, .power = 103, },
	{ .cap =  1024, .power = 150, },
};

static struct sched_group_energy energy_cluster_mt6797_LL = {
	.nr_idle_states = ARRAY_SIZE(idle_states_cluster_mt6797_LL),
	.idle_states    = idle_states_cluster_mt6797_LL,
	.nr_cap_states  = ARRAY_SIZE(cap_states_cluster_mt6797_LL),
	.cap_states     = cap_states_cluster_mt6797_LL,
};

static struct sched_group_energy energy_cluster_mt6797_L = {
	.nr_idle_states = ARRAY_SIZE(idle_states_cluster_mt6797_L),
	.idle_states    = idle_states_cluster_mt6797_L,
	.nr_cap_states  = ARRAY_SIZE(cap_states_cluster_mt6797_L),
	.cap_states     = cap_states_cluster_mt6797_L,
};

static struct sched_group_energy energy_cluster_mt6797_b = {
	.nr_idle_states = ARRAY_SIZE(idle_states_cluster_mt6797_b),
	.idle_states    = idle_states_cluster_mt6797_b,
	.nr_cap_states  = ARRAY_SIZE(cap_states_cluster_mt6797_b),
	.cap_states     = cap_states_cluster_mt6797_b,
};

static struct idle_state idle_states_core_mt6797_LL[] = {
	{ .power = 6 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 6 }, /* WFI */
	{ .power = 0 }, /* cpu-sleep-0 */
	{ .power = 0 }, /* cluster-sleep-0 */
};

static struct idle_state idle_states_core_mt6797_L[] = {
	{ .power = 6 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 6 }, /* WFI */
	{ .power = 0 }, /* cpu-sleep-0 */
	{ .power = 0 }, /* cluster-sleep-0 */
};

static struct idle_state idle_states_core_mt6797_b[] = {
	{ .power = 15 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 15 }, /* WFI */
	{ .power = 0  }, /* cpu-sleep-0 */
	{ .power = 0  }, /* cluster-sleep-0 */
};

static struct capacity_state cap_states_core_mt6797_LL[] = {
	{ .cap =  184, .power = 57, },
	{ .cap =  256, .power = 156, },
	{ .cap =  368, .power = 255, },
	{ .cap =  399, .power = 299, },
	{ .cap =  430, .power = 339, },
	{ .cap =  512, .power = 472, },
	{ .cap =  552, .power = 529, },
	{ .cap =  573, .power = 574, },
};

static struct capacity_state cap_states_core_mt6797_L[] = {
	{ .cap =  184, .power = 57, },
	{ .cap =  256, .power = 156, },
	{ .cap =  368, .power = 255, },
	{ .cap =  399, .power = 299, },
	{ .cap =  430, .power = 339, },
	{ .cap =  512, .power = 472, },
	{ .cap =  552, .power = 529, },
	{ .cap =  573, .power = 574, },
};

static struct capacity_state cap_states_core_mt6797_b[] = {
	{ .cap =  256, .power = 316, },
	{ .cap =  358, .power = 374, },
	{ .cap =  512, .power = 640, },
	{ .cap =  614, .power = 885, },
	{ .cap =  716, .power = 1079, },
	{ .cap =  819, .power = 1376, },
	{ .cap =  921, .power = 1738, },
	{ .cap =  1024, .power = 2207, },
};

static struct sched_group_energy energy_core_mt6797_LL = {
	.nr_idle_states = ARRAY_SIZE(idle_states_core_mt6797_LL),
	.idle_states    = idle_states_core_mt6797_LL,
	.nr_cap_states  = ARRAY_SIZE(cap_states_core_mt6797_LL),
	.cap_states     = cap_states_core_mt6797_LL,
};

static struct sched_group_energy energy_core_mt6797_L = {
	.nr_idle_states = ARRAY_SIZE(idle_states_core_mt6797_L),
	.idle_states    = idle_states_core_mt6797_L,
	.nr_cap_states  = ARRAY_SIZE(cap_states_core_mt6797_L),
	.cap_states     = cap_states_core_mt6797_L,
};

static struct sched_group_energy energy_core_mt6797_b = {
	.nr_idle_states = ARRAY_SIZE(idle_states_core_mt6797_b),
	.idle_states    = idle_states_core_mt6797_b,
	.nr_cap_states  = ARRAY_SIZE(cap_states_core_mt6797_b),
	.cap_states     = cap_states_core_mt6797_b,
};

/* HiKey */

static struct idle_state idle_states_system_hikey[] = {
	{ .power = 0 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 0 }, /* WFI */
	{ .power = 0 }, /* cpu-sleep */
	{ .power = 0 }, /* cluster-sleep */
};

static struct capacity_state cap_states_system_hikey[] = {
	{ .cap = 1024, .power = 0, },
};

static struct sched_group_energy energy_system_hikey = {
	.nr_idle_states = ARRAY_SIZE(idle_states_system_hikey),
	.idle_states    = idle_states_system_hikey,
	.nr_cap_states  = ARRAY_SIZE(cap_states_system_hikey),
	.cap_states     = cap_states_system_hikey,
};

static struct idle_state idle_states_cluster_hikey[] = {
	{ .power = 107 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 107 }, /* WFI */
	{ .power =  47 }, /* cpu-sleep */
	{ .power =   0 }, /* cluster-sleep */
};

static struct capacity_state cap_states_cluster_hikey[] = {
	{ .cap =  178, .power =  16, }, /*  208 MHz */
	{ .cap =  369, .power =  29, }, /*  432 MHz */
	{ .cap =  622, .power =  47, }, /*  729 MHz */
	{ .cap =  819, .power =  75, }, /*  960 MHz */
	{ .cap = 1024, .power = 112, }, /* 1200 MHz */
};

static struct sched_group_energy energy_cluster_hikey = {
	.nr_idle_states = ARRAY_SIZE(idle_states_cluster_hikey),
	.idle_states    = idle_states_cluster_hikey,
	.nr_cap_states  = ARRAY_SIZE(cap_states_cluster_hikey),
	.cap_states     = cap_states_cluster_hikey,
};

static struct idle_state idle_states_core_hikey[] = {
	{ .power = 15 }, /* arch_cpu_idle() (active idle) = WFI */
	{ .power = 15 }, /* WFI */
	{ .power =  0 }, /* cpu-sleep */
	{ .power =  0 }, /* cluster-sleep */
};

static struct capacity_state cap_states_core_hikey[] = {
	{ .cap =  178, .power =  69, }, /*  208 MHz */
	{ .cap =  369, .power = 125, }, /*  432 MHz */
	{ .cap =  622, .power = 224, }, /*  729 MHz */
	{ .cap =  819, .power = 367, }, /*  960 MHz */
	{ .cap = 1024, .power = 670, }, /* 1200 MHz */
};

static struct sched_group_energy energy_core_hikey = {
	.nr_idle_states = ARRAY_SIZE(idle_states_core_hikey),
	.idle_states    = idle_states_core_hikey,
	.nr_cap_states  = ARRAY_SIZE(cap_states_core_hikey),
	.cap_states     = cap_states_core_hikey,
};

/* An energy model contains core, cluster and system sched group energy
 * for 2 clusters (cluster id 0 and 1). set_energy_model() relies on
 * this feature. It is enforced by a BUG_ON in energy().
 */

struct energy_model {
	struct sched_group_energy *core_energy[3];
	struct sched_group_energy *cluster_energy[3];
	struct sched_group_energy *system_energy[3];
};

static struct energy_model juno_model = {
	{ &energy_core_juno_a57, &energy_core_juno_a53, },
	{ &energy_cluster_juno_a57, &energy_cluster_juno_a53, },
	{},
};

static struct energy_model hikey_model = {
	{ &energy_core_hikey, &energy_core_hikey, },
	{ &energy_cluster_hikey, &energy_cluster_hikey, },
	{ &energy_system_hikey, &energy_system_hikey, },
};

static struct energy_model mt8173_model = {
	{ &energy_core_mt8173_a53, &energy_core_mt8173_a57, },
	{ &energy_cluster_mt8173_a53, &energy_cluster_mt8173_a57, },
	{},
};

static struct energy_model mt6797_model = {
	{ &energy_core_mt6797_LL, &energy_core_mt6797_L, &energy_core_mt6797_b},
	{ &energy_cluster_mt6797_LL, &energy_cluster_mt6797_L, &energy_cluster_mt6797_b,},
	{},
};

static struct of_device_id model_matches[] = {
	{ .compatible = "arm,juno", .data = &juno_model },
	{ .compatible = "hisilicon,hi6220-hikey", .data = &hikey_model },
	{ .compatible = "mediatek,mt8173", .data = &mt8173_model },
	{ .compatible = "mediatek,mt6797", .data = &mt6797_model },
	{},
};

struct sched_group_energy **core_energy, **cluster_energy, **system_energy;

static void __init set_energy_model(void)
{
	const struct of_device_id *match;
	struct energy_model *em;

	BUG_ON(core_energy || cluster_energy || system_energy);

	match = of_match_node(model_matches, of_root);

	if (!match)
		return;

	em = (struct energy_model *) match->data;

	core_energy = em->core_energy;
	cluster_energy = em->cluster_energy;
	system_energy = em->system_energy;

	pr_debug("energy model core[0,1]=[%p,%p] cluster=[%p,%p] system=[%p,%p]\n",
		 em->core_energy[0], em->core_energy[1],
		 em->cluster_energy[0], em->cluster_energy[1],
		 em->system_energy[0], em->system_energy[1]);
}

static inline
struct sched_group_energy *energy(int cpu, struct sched_group_energy **sge)
{
	int idx = cpu_topology[cpu].cluster_id;

	BUG_ON(idx != 0 && idx != 1 && idx != 2);

	pr_debug("cpu=%d %s%s[%d]=%p\n", cpu, (sge == core_energy) ?
		 "core" : (sge == cluster_energy) ? "cluster" :
		 "system", "_energy", idx, sge[idx]);

	return sge[idx];
}

static inline
const struct sched_group_energy * const cpu_core_energy(int cpu)
{
	return core_energy ? energy(cpu, core_energy) : NULL;
}

static inline
const struct sched_group_energy * const cpu_cluster_energy(int cpu)
{
	return cluster_energy ? energy(cpu, cluster_energy) : NULL;
}

static inline
const struct sched_group_energy * const cpu_system_energy(int cpu)
{
	return system_energy ? energy(cpu, system_energy) : NULL;
}
