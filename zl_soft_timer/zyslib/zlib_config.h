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
/* ����˵���������ϼ��ļ����ڵ�ͷ�ļ�*/     
/*#include "..\app_cfg.h" */
/* ����˵�������浱ǰ�ļ����ڵ�ͷ�ļ�*/     
/*#include ".\app_cfg.h" */
     
#include <stdint.h>       
#include <stdbool.h>      
     
/*#include <stdlib.h>       */
/*#include <string.h>       */

#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
     
/* ѡ��һ������ٽ������뱣�� ��zlib_critical.c */
//#define ZL_USE_IAR_IDE          /* ʹ��IAR */
#define ZL_USE_STM32_KEIL_IDE      /* ʹ��STM32 + KEIL */
//#define ZL_USE_MCS51_KEIL_IDE      /* ʹ��MCS51 + KEIL*/
//#define ZL_USE_OTHER_MCU_IDE        /* ʹ��������MCU��IDE����Ҫʹ���������޸�zlib_critical.c */



/* �����ָ�� */
#ifndef NULL
    #define NULL  0
#endif 

     
     



     
/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif

#endif /* __ZLIB_CONFIG_H__ */

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/
