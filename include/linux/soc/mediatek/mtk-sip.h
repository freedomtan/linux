#ifndef __SOC_MEDIATEK_MTKSIP_H
#define __SOC_MEDIATEK_MTKSIP_H

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
