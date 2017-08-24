/**
  ******************************************************************************
  * @file    ZYSlib/zlib_printf.h
  * @author  ZYS
  * @version V1.0.0
  * @date    01/20/2015
  * @brief   
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZLIB_PRINTF_H__
#define __ZLIB_PRINTF_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include ".\zlib_config.h"
     
     
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
     
/* */     
typedef void (*fnusart_send_byte_t)(uint8_t chData);
     
/* Exported functions ------------------------------------------------------- */
bool zl_printf_init(fnusart_send_byte_t fnusart_send_byte_user);
void zl_printf_byte(uint8_t chData);
void zl_printf(uint8_t *Data,...);
void zl_printf_string(const uint8_t *pchStr);


#ifdef __cplusplus
}
#endif

#endif /* __ZLIB_PRINTF_H__ */

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

