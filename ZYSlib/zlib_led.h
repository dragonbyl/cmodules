/**
  ******************************************************************************
  * @file    ZYSlib/zlib_led.h 
  * @author  ZYS
  * @version V1.0.0
  * @date    08/02/2015
  * @brief   
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZLIB_LED_H__
#define __ZLIB_LED_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>       
#include <stdbool.h>      

/* Exported constants --------------------------------------------------------*/
/* 定义空指针 */
#ifndef NULL
    #define NULL  0
#endif 
     
/* Exported macro ------------------------------------------------------------*/    
/* Exported types ------------------------------------------------------------*/
/* 定义 led on off 注册函数指针类型 */
typedef void (*zlfn_led_t)(void);

/* Exported functions ------------------------------------------------------- */
bool zl_led_init(zlfn_led_t fn_led_on, zlfn_led_t fn_led_off);
void zl_led_flash_set(uint8_t chFlashCnt, uint16_t hwOnTime, uint16_t hwOffTime);
void zl_led_flash_loop(void);


#ifdef __cplusplus
}
#endif

#endif /* __ZLIB_LED_H__ */

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/
