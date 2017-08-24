/**
  ******************************************************************************
  * @file    ZYSlib/zlib_soft_timer.c
  * @author  ZYS
  * @version V1.0.0
  * @date    08/19/2015
  * @brief   这是一个简单的软件定时器模块，定时器被设计成执行一次就不再执行，
             如果需要周期执行，可以在回调函数内重新启动定时器。
  ******************************************************************************
  */


/* Debug log -----------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include ".\zlib_soft_timer.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum
{
    STIMER_STOP = 0,
    STIMER_START = !STIMER_STOP
} zl_SoftTimerCtrl_emt;

typedef struct
{
    uint32_t wTimer;                            /* 定时计数器 */
    uint16_t hwCtrl;                             /* 定时器开关控制 */
    uint32_t wRunCnt;                          /* 运行计数器 */
    zlfn_st_t fn_call_back;                     /* 回调函数 */
} zl_SoftTimer_t, *ptSoftTimer;

/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* 定时器队列 */
static zl_SoftTimer_t s_tSoftTimer[ZL_SOFT_TIMER_MAX_NUM];

/* 软件定时器模块初始化成功标志 */
static uint32_t s_wSoftTimerInitOK = 0;

/* Global  variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/





/*   Z L _ D U M M Y _ F U N C _ S O F T _ T I M E R   */
/*-------------------------------------------------------------------------
    * 功能：空函数，供函数指针初始化使用。
    * 参数：无
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
static void zl_dummy_func_soft_timer(void)
{
    /* do nothing */
}


/*   Z L _ S O F T _ T I M E R _ S E T   */
/*-------------------------------------------------------------------------
    * 功能：设置一个定时器。
    * 参数：1.定时器编号，0 至 ZL_SOFT_TIMER_MAX_NUM；
    *       2.定时时间；
    *       3.回调函数。
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_soft_timer_set(uint8_t chTimerNum, uint32_t wTime, zlfn_st_t fn_call_back)
{
    if (!s_wSoftTimerInitOK)
    {
        return;
    }

    if (chTimerNum >= ZL_SOFT_TIMER_MAX_NUM)
    {
        return;                                 /* 超出定时器数量，直接退出 */
    }

    if (0 == wTime)
    {
        return;                                 /* 定时时间为 0 ，直接退出 */
    }


    zl_enter_critical();

    s_tSoftTimer[chTimerNum].wTimer = wTime;

    if (NULL == fn_call_back)
    {
        s_tSoftTimer[chTimerNum].fn_call_back = zl_dummy_func_soft_timer;
    }
    else
    {
        s_tSoftTimer[chTimerNum].fn_call_back = fn_call_back;
    }

    s_tSoftTimer[chTimerNum].hwCtrl = STIMER_START;

    zl_exit_critical();

}


/*   Z L _ S O F T _ T I M E R _ K I L L   */
/*-------------------------------------------------------------------------
    * 功能：停止指定编号的定时器。
    * 参数：1.定时器编号 0 至 ZL_SOFT_TIMER_MAX_NUM。
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_soft_timer_kill(uint8_t chTimerNum)
{
    if (!s_wSoftTimerInitOK)
    {
        return;
    }

    if (chTimerNum >= ZL_SOFT_TIMER_MAX_NUM)
    {
        return;                                 /* 超出定时器数量，直接退出 */
    }

    zl_enter_critical();

    s_tSoftTimer[chTimerNum].hwCtrl = STIMER_STOP;

    zl_exit_critical();
}


/*   Z L _ S O F T _ T I M E R _ I N I T   */
/*-------------------------------------------------------------------------
    * 功能：初始化软件定时器模块。
    * 参数：无
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_soft_timer_init(void)
{
    s_wSoftTimerInitOK = 0;

    zl_memory_clear((uint8_t*)s_tSoftTimer, sizeof(s_tSoftTimer));

    s_wSoftTimerInitOK = 1;
}


/*   Z L _ S O F T _ T I M E R _ L O O P   */
/*-------------------------------------------------------------------------
    * 功能：软件定时器任务，在心跳中断里运行。
    * 参数：无
    * 返回：无
    * 备注：OK.

    该函数的运行周期决定定时器的时基。
-------------------------------------------------------------------------*/
void zl_soft_timer_loop(void)
{
    uint16_t i;


    if (!s_wSoftTimerInitOK)
    {
        return;
    }

    for (i = 0; i < ZL_SOFT_TIMER_MAX_NUM; i++)
    {
        if (s_tSoftTimer[i].hwCtrl)
        {
            if (0 == s_tSoftTimer[i].wTimer)
            {
                s_tSoftTimer[i].hwCtrl = STIMER_STOP;           /* 定时时间到就停掉定时器 */
                s_tSoftTimer[i].wRunCnt++;                     /* 更新运行计数器 */
            }
            else
            {
                s_tSoftTimer[i].wTimer--;
            }
        }
    }
}


/*   Z L _ S O F T _ T I M E R _ S E R V I C E   */
/*-------------------------------------------------------------------------
    * 功能：软件定时器服务，在超级循环里运行。
    * 参数：无
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_soft_timer_service(void)
{
    uint16_t i;


    if (!s_wSoftTimerInitOK)
    {
        return;
    }

    for (i = 0; i < ZL_SOFT_TIMER_MAX_NUM; i++)
    {
        if (s_tSoftTimer[i].wRunCnt)
        {
            s_tSoftTimer[i].fn_call_back();                 /* 执行回调函数 */
            s_tSoftTimer[i].wRunCnt--;
        }
    }
}

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

