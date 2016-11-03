#ifndef __SOC_MEDIATEK_MTKSIP_H
#define __SOC_MEDIATEK_MTKSIP_H

#define MTK_SIP_PWR_ON_MTCMOS			0x82000402
#define MTK_SIP_PWR_OFF_MTCMOS			0x82000403
#define MTK_SIP_PWR_MTCMOS_SUPPORT		0x82000404

#ifdef CONFIG_MTK_SIP
int mtk_sip_simple_call(unsigned long func_id,
			unsigned long a1,
			unsigned long a2,
			unsigned long a3);
#else
static inline int mtk_sip_simple_call(unsigned long func_id,
				      unsigned long a1,
				      unsigned long a2,
				      unsigned long a3)
{       return -EOPNOTSUPP; }
#endif

#endif /*__SOC_MEDIATEK_MTKSIP_H*/
