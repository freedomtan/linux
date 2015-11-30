/*
 * Copyright (c) 2015 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/arm-smccc.h>
#include <linux/soc/mediatek/mtk-sip.h>

int mtk_sip_simple_call(unsigned long func_id,
			unsigned long a1,
			unsigned long a2,
			unsigned long a3)
{
	struct arm_smccc_res res;

	arm_smccc_smc(func_id, a1, a2, a3, 0, 0, 0, 0, &res);

	return res.a0;
}
