/**
  ******************************************************************************
  * @file    ZYSlib/zlib_critical.c
  * @author  ZYS
  * @version V1.0.0
  * @date    01/20/2015
  * @brief   这是一个提供临界区保护的模块。
  ******************************************************************************
  */


/* Debug log -----------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include ".\zlib_critical.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* 临界区嵌套计数器 */
static uint8_t s_chCriticalNesting = 0;

/* Global  variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


#ifdef ZL_USE_IAR_IDE
typedef __istate_t   istate_t;
static istate_t s_tState = 0;
#endif


#ifdef ZL_USE_STM32_KEIL_IDE
static uint32_t s_wState = 0;
#endif


#ifdef ZL_USE_MCS51_KEIL_IDE
static uint8_t s_chState = 0;
#endif


#ifdef ZL_USE_OTHER_MCU_IDE
/* add user code here */

#endif


/*   Z L _ E N A B L E _ I R Q   */
/*-------------------------------------------------------------------------
    * 功能：使能全局中断。
    * 参数：无
    * 返回：无
    * 备注：该函数需要使用者跟据所用平台，自行编写。
-------------------------------------------------------------------------*/
void zl_enable_global_irq(void)
{
#ifdef ZL_USE_IAR_IDE
    __enable_interrupt();
#endif

#ifdef ZL_USE_STM32_KEIL_IDE
    __enable_irq();
#endif

#ifdef ZL_USE_MCS51_KEIL_IDE
    EA = 1;
#endif

#ifdef ZL_USE_OTHER_MCU_IDE
    /* add user code here */

#endif
}


/*   Z L _ D I S A B L E _ I R Q   */
/*-------------------------------------------------------------------------
    * 功能：失能全局中断。
    * 参数：无
    * 返回：无
    * 备注：该函数需要使用者跟据所用平台，自行编写。
-------------------------------------------------------------------------*/
void zl_disable_global_irq(void)
{
#ifdef ZL_USE_IAR_IDE
    __disable_interrupt();
#endif

#ifdef ZL_USE_STM32_KEIL_IDE
    __disable_irq();
#endif

#ifdef ZL_USE_MCS51_KEIL_IDE
    EA = 0;
#endif

#ifdef ZL_USE_OTHER_MCU_IDE
    /* add user code here */

#endif
}


/*   Z L _ E N T E R _ C R I T I C A L   */
/*-------------------------------------------------------------------------
    * 功能：进入临界区。
    * 参数：无
    * 返回：无
    * 备注：OK。
-------------------------------------------------------------------------*/
void zl_enter_critical(void)
{
    if (0 == s_chCriticalNesting)
    {
        /* 只对最外层执行关中断操作,首先获取中断状态，然后关闭中断 */
#ifdef ZL_USE_IAR_IDE
        s_tState = __get_interrupt_state();
#endif

#ifdef ZL_USE_STM32_KEIL_IDE
        s_wState = __get_PRIMASK();
#endif

#ifdef ZL_USE_MCS51_KEIL_IDE
        s_chState = EA;
#endif

#ifdef ZL_USE_OTHER_MCU_IDE
        /* add user code here */

#endif

        zl_disable_global_irq();
    }

    /* 临界嵌套层数加一 */
    s_chCriticalNesting++;
}


/*   Z L _ E X I T _ C R I T I C A L   */
/*-------------------------------------------------------------------------
    * 功能：退出临界区。
    * 参数：无
    * 返回：无
    * 备注：OK。
-------------------------------------------------------------------------*/
void zl_exit_critical(void)
{
    /* 临界嵌套层数减一 */
    s_chCriticalNesting--;

    if (0 == s_chCriticalNesting)
    {
        /* 只对最外层执行开中断操作 */

#ifdef ZL_USE_IAR_IDE
        __set_interrupt_state(s_tState);
#endif

#ifdef ZL_USE_STM32_KEIL_IDE
        __set_PRIMASK(s_wState);
#endif

#ifdef ZL_USE_MCS51_KEIL_IDE
        EA = s_chState;
#endif

#ifdef ZL_USE_OTHER_MCU_IDE
        /* add user code here */

#endif
    }
}

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

