/**
  ******************************************************************************
  * @file    ZYSlib/zlib_led.c
  * @author  ZYS
  * @version V1.0.0
  * @date    08/02/2015
  * @brief   ����һ���򵥵� LED ״ָ̬ʾģ�飬֧��������ʱ�䡢��˸�������趨��
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
/* ���庯��ָ�����������ʼ��Ϊ�պ��� */
static zlfn_led_t s_fnled_flash_on   = zl_dummy_func_led;
static zlfn_led_t s_fnled_flash_off  = zl_dummy_func_led;

static uint8_t s_chFlashFsmSta   = 2;              /* led flash״̬���������,Ĭ��ֹͣ״̬ */
static uint8_t s_chFlashCnt      = 0;
static uint16_t s_hwFlashOnTime  = 0;
static uint16_t s_hwFlashOffTime = 0;


/* Global  variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
* ���ܣ��պ���������ʼ��ʹ�á�
* ��������
* ���أ���
* ��ע���ú���δ���ԡ�
*/

/*   Z L _ D U M M Y _ F U N C _ L E D   */
/*-------------------------------------------------------------------------
    * ���ܣ��պ���������ʼ��ʹ�á�
    * ��������
    * ���أ���
    * ��ע��OK.
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
    * ���ܣ�ע���û�led���ƺ�����
    * ������1.LED������ָ�룻
    *       2.LED����ָ�롣
    * ���أ��ɹ�����TRUE��ʧ�ܷ���FALSE��
    * ��ע��OK.
-------------------------------------------------------------------------*/
bool zl_led_init(zlfn_led_t fn_led_on, zlfn_led_t fn_led_off)
{
    if ((NULL == fn_led_on) || (NULL == fn_led_off))
    {
        return false;
    }

    /* ע���û����� */
    s_fnled_flash_on  = fn_led_on;
    s_fnled_flash_off = fn_led_off;

    zl_led_flash_off();
    return true;
}


/*   Z L _ L E D _ F L A S H _ S E T   */
/*-------------------------------------------------------------------------
    * ���ܣ�����LED��˸������
    * ������1.��˸����������0��ʾ���޴���˸��
    *       2.��ʱ�䣬����0��ʾ������
    *       3.��ʱ�䣬����0��ʾ����
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
void zl_led_flash_set(uint8_t chFlashCnt, uint16_t hwOnTime, uint16_t hwOffTime)
{
    /* ������ز��� */
    s_chFlashCnt     = chFlashCnt;
    s_hwFlashOnTime  = hwOnTime;
    s_hwFlashOffTime = hwOffTime;

    /* ��λ״̬�� */
    s_chFlashFsmSta = 0;
}


/*   Z L _ L E D _ F L A S H _ L O O P   */
/*-------------------------------------------------------------------------
    * ���ܣ�LED��˸����,��Ҫ����ִ��,������ʱ���ж���ִ�С�
    * ��������
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
void zl_led_flash_loop(void)
{
    static uint16_t s_hwTime     = 0;               /* ������ʱ */
    static uint8_t s_chLedSta    = 0;               /* LED״̬��0��ʾON��1��ʾ�� */
    static uint8_t s_chFlashMode = 0;               /* ��˸ģʽ��1��ʾ���ޣ�0��ʾ���� */


    switch (s_chFlashFsmSta)
    {
        case 0:
            if (0 == s_chFlashCnt)
            {
                /* ����0��ʾ���޴�����˸ */
                s_chFlashMode = 1;
            }
            else
            {
                s_chFlashMode = 0;
            }

            zl_led_flash_off();                         /* ��ʼ״̬Ҫ���� */
            s_chLedSta = 1;                             /* ��ʼLED״̬ */
            s_chFlashFsmSta = 1;                        /* �л�����˸״̬ */

            break;

        case 1:
            if (s_chLedSta)
            {
                /* Led off sta */
                if (0 == s_hwTime)                      /* ���ʱ��ִ���� */
                {
                    /* ����״̬�ж�ִ�д��� */
                    if (0 == s_chFlashCnt && 0 == s_chFlashMode)
                    {
                        /* ���޴���ִ����ɣ��л���ֹͣ״̬ */
                        s_chFlashFsmSta = 2;
                        break;
                    }

                    if (s_hwFlashOnTime)                /* ��Ҫ���� */
                    {
                        zl_led_flash_on();
                        s_hwTime = s_hwFlashOnTime;     /* ����ʱ�� */
                        s_chLedSta = 0;                 /* �л�������״̬ */
                    }
                }
                else
                {
                    s_hwTime--;                         /* ���¼����� */
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

                        /* ��ÿ���������ڼ����˸ģʽ */
                        if (!s_chFlashMode)
                        {

                            /* ����ģʽ����ٴ��� */
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

