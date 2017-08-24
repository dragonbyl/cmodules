/**
  ******************************************************************************
  * @file    ZYSlib/zlib_memory.h
  * @author  ZYS
  * @version V1.0.0
  * @date    08/21/2015
  * @brief   
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ZLIB_MEMORY_H__
#define __ZLIB_MEMORY_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include ".\zlib_config.h"

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void zl_memory_set(uint8_t *pchDest, uint8_t chData, uint16_t hwSize);     
void zl_memory_clear(uint8_t *pchDest, uint16_t hwSize);
void zl_memory_copy(uint8_t *pchDest, uint8_t *pchSrc, uint16_t hwSize);     
void zl_memory_swap(void *const Datax, void *const Datay, uint8_t chSize);


#ifdef __cplusplus
}
#endif

#endif /* __ZLIB_MEMORY_H__ */

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

