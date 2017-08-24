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
* 头文件的包含排规则采用稳定度排序。
* 经常变化的不稳定头文件放前面，稳定的如标准库的相关头文件放后面。
* 这样做的好处是可以提早发现编译错误，减少部分编译时间。
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

