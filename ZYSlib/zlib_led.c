/**
  ******************************************************************************
  * @file    ZYSlib/zlib_led.c
  * @author  ZYS
  * @version V1.0.0
  * @date    08/02/2015
  * @brief   这是一个简单的 LED 状态指示模块，支持亮、灭时间、闪烁次数的设定。
  ******************************************************************************
  */


/* Debug log -----------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include ".\zlib_led.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void zl_dummy_func_led(void);

/* Private variables ---------------------------------------------------------*/
/* 定义函数指针变量，并初始化为空函数 */
static zlfn_led_t s_fnled_flash_on   = zl_dummy_func_led;
static zlfn_led_t s_fnled_flash_off  = zl_dummy_func_led;

static uint8_t s_chFlashFsmSta   = 2;              /* led flash状态机步骤变量,默认停止状态 */
static uint8_t s_chFlashCnt      = 0;
static uint16_t s_hwFlashOnTime  = 0;
static uint16_t s_hwFlashOffTime = 0;


/* Global  variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
* 功能：空函数，供初始化使用。
* 参数：无
* 返回：无
* 备注：该函数未测试。
*/

/*   Z L _ D U M M Y _ F U N C _ L E D   */
/*-------------------------------------------------------------------------
    * 功能：空函数，供初始化使用。
    * 参数：无
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
static void zl_dummy_func_led(void)
{
    /* do nothing */
}


/*   Z L _ L E D _ F L A S H _ O N   */
/*-------------------------------------------------------------------------
    OK.
-------------------------------------------------------------------------*/
static void zl_led_flash_on(void)
{
    (*s_fnled_flash_on)();
}


/*   Z L _ L E D _ F L A S H _ O F F   */
/*-------------------------------------------------------------------------
    OK.
-------------------------------------------------------------------------*/
static void zl_led_flash_off(void)
{
    (*s_fnled_flash_off)();
}


/*   Z L _ L E D _ I N I T   */
/*-------------------------------------------------------------------------
    * 功能：注册用户led控制函数。
    * 参数：1.LED亮函数指针；
    *       2.LED灭函数指针。
    * 返回：成功返回TRUE，失败返回FALSE。
    * 备注：OK.
-------------------------------------------------------------------------*/
bool zl_led_init(zlfn_led_t fn_led_on, zlfn_led_t fn_led_off)
{
    if ((NULL == fn_led_on) || (NULL == fn_led_off))
    {
        return false;
    }

    /* 注册用户函数 */
    s_fnled_flash_on  = fn_led_on;
    s_fnled_flash_off = fn_led_off;

    zl_led_flash_off();
    return true;
}


/*   Z L _ L E D _ F L A S H _ S E T   */
/*-------------------------------------------------------------------------
    * 功能：设置LED闪烁参数。
    * 参数：1.闪烁次数，等于0表示无限次闪烁；
    *       2.亮时间，等于0表示不亮；
    *       3.灭时间，等于0表示不灭。
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_led_flash_set(uint8_t chFlashCnt, uint16_t hwOnTime, uint16_t hwOffTime)
{
    /* 更新相关参数 */
    s_chFlashCnt     = chFlashCnt;
    s_hwFlashOnTime  = hwOnTime;
    s_hwFlashOffTime = hwOffTime;

    /* 复位状态机 */
    s_chFlashFsmSta = 0;
}


/*   Z L _ L E D _ F L A S H _ L O O P   */
/*-------------------------------------------------------------------------
    * 功能：LED闪烁任务,需要周期执行,建议在时标中断里执行。
    * 参数：无
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_led_flash_loop(void)
{
    static uint16_t s_hwTime     = 0;               /* 辅助计时 */
    static uint8_t s_chLedSta    = 0;               /* LED状态，0表示ON，1表示灭 */
    static uint8_t s_chFlashMode = 0;               /* 闪烁模式，1表示有限，0表示无限 */


    switch (s_chFlashFsmSta)
    {
        case 0:
            if (0 == s_chFlashCnt)
            {
                /* 等于0表示无限次数闪烁 */
                s_chFlashMode = 1;
            }
            else
            {
                s_chFlashMode = 0;
            }

            zl_led_flash_off();                         /* 初始状态要关灭 */
            s_chLedSta = 1;                             /* 初始LED状态 */
            s_chFlashFsmSta = 1;                        /* 切换至闪烁状态 */

            break;

        case 1:
            if (s_chLedSta)
            {
                /* Led off sta */
                if (0 == s_hwTime)                      /* 灭灯时间执行完 */
                {
                    /* 在灭状态判断执行次数 */
                    if (0 == s_chFlashCnt && 0 == s_chFlashMode)
                    {
                        /* 有限次数执行完成，切换至停止状态 */
                        s_chFlashFsmSta = 2;
                        break;
                    }

                    if (s_hwFlashOnTime)                /* 需要亮灯 */
                    {
                        zl_led_flash_on();
                        s_hwTime = s_hwFlashOnTime;     /* 更新时间 */
                        s_chLedSta = 0;                 /* 切换至亮灯状态 */
                    }
                }
                else
                {
                    s_hwTime--;                         /* 更新计数器 */
                }
            }
            else
            {
                /* Led on sta */
                if (0 == s_hwTime)
                {
                    if (s_hwFlashOffTime)
                    {
                        zl_led_flash_off();
                        s_hwTime = s_hwFlashOffTime;
                        s_chLedSta = 1;

                        /* 在每个亮灭周期检查闪烁模式 */
                        if (!s_chFlashMode)
                        {

                            /* 有限模式里减少次数 */
                            if (s_chFlashCnt)
                            {
                                s_chFlashCnt--;
                            }
                            else
                            {
                                /* do nothing */
                            }
                        }
                    }
                }
                else
                {
                    s_hwTime--;
                }
            }

            break;

        case 2:
            /* do nothing */
            break;

        default:
            break;
    }
}



/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

