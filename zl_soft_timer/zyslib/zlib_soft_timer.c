/**
  ******************************************************************************
  * @file    ZYSlib/zlib_soft_timer.c
  * @author  ZYS
  * @version V1.0.0
  * @date    08/19/2015
  * @brief   ����һ���򵥵������ʱ��ģ�飬��ʱ������Ƴ�ִ��һ�ξͲ���ִ�У�
             �����Ҫ����ִ�У������ڻص�����������������ʱ����
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
    uint32_t wTimer;                            /* ��ʱ������ */
    uint16_t hwCtrl;                             /* ��ʱ�����ؿ��� */
    uint32_t wRunCnt;                          /* ���м����� */
    zlfn_st_t fn_call_back;                     /* �ص����� */
} zl_SoftTimer_t, *ptSoftTimer;

/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ��ʱ������ */
static zl_SoftTimer_t s_tSoftTimer[ZL_SOFT_TIMER_MAX_NUM];

/* �����ʱ��ģ���ʼ���ɹ���־ */
static uint32_t s_wSoftTimerInitOK = 0;

/* Global  variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/





/*   Z L _ D U M M Y _ F U N C _ S O F T _ T I M E R   */
/*-------------------------------------------------------------------------
    * ���ܣ��պ�����������ָ���ʼ��ʹ�á�
    * ��������
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
static void zl_dummy_func_soft_timer(void)
{
    /* do nothing */
}


/*   Z L _ S O F T _ T I M E R _ S E T   */
/*-------------------------------------------------------------------------
    * ���ܣ�����һ����ʱ����
    * ������1.��ʱ����ţ�0 �� ZL_SOFT_TIMER_MAX_NUM��
    *       2.��ʱʱ�䣻
    *       3.�ص�������
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
void zl_soft_timer_set(uint8_t chTimerNum, uint32_t wTime, zlfn_st_t fn_call_back)
{
    if (!s_wSoftTimerInitOK)
    {
        return;
    }

    if (chTimerNum >= ZL_SOFT_TIMER_MAX_NUM)
    {
        return;                                 /* ������ʱ��������ֱ���˳� */
    }

    if (0 == wTime)
    {
        return;                                 /* ��ʱʱ��Ϊ 0 ��ֱ���˳� */
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
    * ���ܣ�ָֹͣ����ŵĶ�ʱ����
    * ������1.��ʱ����� 0 �� ZL_SOFT_TIMER_MAX_NUM��
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
void zl_soft_timer_kill(uint8_t chTimerNum)
{
    if (!s_wSoftTimerInitOK)
    {
        return;
    }

    if (chTimerNum >= ZL_SOFT_TIMER_MAX_NUM)
    {
        return;                                 /* ������ʱ��������ֱ���˳� */
    }

    zl_enter_critical();

    s_tSoftTimer[chTimerNum].hwCtrl = STIMER_STOP;

    zl_exit_critical();
}


/*   Z L _ S O F T _ T I M E R _ I N I T   */
/*-------------------------------------------------------------------------
    * ���ܣ���ʼ�������ʱ��ģ�顣
    * ��������
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
void zl_soft_timer_init(void)
{
    s_wSoftTimerInitOK = 0;

    zl_memory_clear((uint8_t*)s_tSoftTimer, sizeof(s_tSoftTimer));

    s_wSoftTimerInitOK = 1;
}


/*   Z L _ S O F T _ T I M E R _ L O O P   */
/*-------------------------------------------------------------------------
    * ���ܣ������ʱ�������������ж������С�
    * ��������
    * ���أ���
    * ��ע��OK.

    �ú������������ھ�����ʱ����ʱ����
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
                s_tSoftTimer[i].hwCtrl = STIMER_STOP;           /* ��ʱʱ�䵽��ͣ����ʱ�� */
                s_tSoftTimer[i].wRunCnt++;                     /* �������м����� */
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
    * ���ܣ������ʱ�������ڳ���ѭ�������С�
    * ��������
    * ���أ���
    * ��ע��OK.
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
            s_tSoftTimer[i].fn_call_back();                 /* ִ�лص����� */
            s_tSoftTimer[i].wRunCnt--;
        }
    }
}

/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

