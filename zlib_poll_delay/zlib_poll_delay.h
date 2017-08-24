/**
  ******************************************************************************
  * @file    ZYSlib/zlib_poll_delay.h 
  * @author  ZYS
  * @version V1.0.0
  * @date    01/20/2017
  * @brief   
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZLIB_POLL_DELAY_H__
#define __ZLIB_POLL_DELAY_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
/**
* ͷ�ļ��İ����Ź�������ȶ�������
* �����仯�Ĳ��ȶ�ͷ�ļ���ǰ�棬�ȶ������׼������ͷ�ļ��ź��档
* �������ĺô��ǿ������緢�ֱ�����󣬼��ٲ��ֱ���ʱ�䡣
**/
#include "stm32f10x.h"

#include <stdbool.h>     
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
bool zl_poll_delay_set(uint8_t chUserId, uint16_t hwTime);
bool zl_poll_delay_timeout(uint8_t chUserId);
void zl_poll_delay_tick(void);


#ifdef __cplusplus
}
#endif

#endif /* __ZLIB_POLL_DELAY_H__ */

/*************************** (C) COPYRIGHT 2017 ZYS ************END OF FILE****/

