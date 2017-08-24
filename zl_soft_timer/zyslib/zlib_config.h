/**
  ******************************************************************************
  * @file    ZYSlib/zlib_config.h 
  * @author  ZYS
  * @version V1.0.0
  * @date    01/20/2015
  * @brief   
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZLIB_CONFIG_H__
#define __ZLIB_CONFIG_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
/* 例子说明：保存上级文件夹内的头文件*/     
/*#include "..\app_cfg.h" */
/* 例子说明：保存当前文件夹内的头文件*/     
/*#include ".\app_cfg.h" */
     
#include <stdint.h>       
#include <stdbool.h>      
     
/*#include <stdlib.h>       */
/*#include <string.h>       */

#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
     
/* 选择一项，用于临界区代码保护 在zlib_critical.c */
//#define ZL_USE_IAR_IDE          /* 使用IAR */
#define ZL_USE_STM32_KEIL_IDE      /* 使用STM32 + KEIL */
//#define ZL_USE_MCS51_KEIL_IDE      /* 使用MCS51 + KEIL*/
//#define ZL_USE_OTHER_MCU_IDE        /* 使用其它的MCU和IDE，需要使用者自行修改zlib_critical.c */



/* 定义空指针 */
#ifndef NULL
    #define NULL  0
#endif 

     
     



     
/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif

#endif /* __ZLIB_CONFIG_H__ */

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/
