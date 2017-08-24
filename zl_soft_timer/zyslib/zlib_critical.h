/**
  ******************************************************************************
  * @file    ZYSlib/zlib_critical.h
  * @author  ZYS
  * @version V1.0.0
  * @date    01/20/2015
  * @brief   
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZLIB_CRITICAL_H__
#define __ZLIB_CRITICAL_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include ".\zlib_config.h"

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void zl_enable_irq(void);
void zl_disable_irq(void);
void zl_enter_critical(void);
void zl_exit_critical(void);


#ifdef __cplusplus
}
#endif

#endif /* __ZLIB_CRITICAL_H__ */

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

