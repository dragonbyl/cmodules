/**
  ******************************************************************************
  * @file    ZYSlib/zlib_soft_timer.h 
  * @author  ZYS
  * @version V1.0.0
  * @date    08/19/2015
  * @brief   
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZLIB_SOFT_TIMER_H__
#define __ZLIB_SOFT_TIMER_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include ".\zlib_critical.h"
#include ".\zlib_memory.h"     
/* Exported constants --------------------------------------------------------*/
/* 配置支持的软件定时器数量，最大为 255 */
#define ZL_SOFT_TIMER_MAX_NUM       5

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef void (*zlfn_st_t)(void);
     
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void zl_soft_timer_set(uint8_t chTimerNum, uint32_t wTime, zlfn_st_t fn_call_back);
void zl_soft_timer_kill(uint8_t chTimerNum);
void zl_soft_timer_init(void);
void zl_soft_timer_loop(void);
void zl_soft_timer_service(void);


#ifdef __cplusplus
}
#endif

#endif /* __ZLIB_SOFT_TIMER_H__ */

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

