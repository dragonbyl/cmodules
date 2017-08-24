/**
  ******************************************************************************
  * @file    ZYSlib/zlib_printf.c
  * @author  ZYS
  * @version V1.0.0
  * @date    01/20/2015
  * @brief   ����һ���򵥵Ĵ���ͨѶ����ģ�飬ʵ�� C99 ��׼�£��� MCU ƽ̨�޹�
             �Ĵ�ӡ���������
  ******************************************************************************
  */


/* Debug log -----------------------------------------------------------------*/


/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>             /* ϵͳ��׼ͷ�ļ���֧�ֿɱ�������� */
#include <stdio.h>              /* ϵͳ��׼ͷ�ļ���֧��IO���� */
#include ".\zlib_printf.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ���û�ע�ᴮ�ڷ��ͺ����ĺ���ָ�� */
static fnusart_send_byte_t s_fnusart_send_byte = NULL;

/* Global  variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/





/*   Z L _ P R I N T F _ I N I T   */
/*-------------------------------------------------------------------------
    * ���ܣ���ʼ�� zl_printf ģ�飬���û�ע��һ�����͵��ֽڵĺ�����
    * ������1.����һ���ֽڵĴ��ں�����ָ�롣
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
bool zl_printf_init(fnusart_send_byte_t fnusart_send_byte_user)
{
    if (NULL == fnusart_send_byte_user)
    {
        return false;
    }

    s_fnusart_send_byte = fnusart_send_byte_user;

    return true;
}


/*   Z L _ P R I N T F _ B Y T E   */
/*-------------------------------------------------------------------------
    * ���ܣ�ͨ�����ڷ���һ���ֽڵ�����
    * ������1.�����͵��ֽ����ݡ�
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
void zl_printf_byte(uint8_t chData)
{
    (*s_fnusart_send_byte)(chData);
}


/*   F P U T C   */
/*-------------------------------------------------------------------------
* ���ܣ��ض���c�⺯�� printf �� MCU �� USART.
* ������1.�������ַ���
*       2.�ļ�ָ�롣
* ���أ������ַ���
* ��ע��OK.
        �ú�����ϵͳ printf ���ã����û��޹ء�
-------------------------------------------------------------------------*/
int fputc(int ch, FILE *f)
{
    /* ��Printf���ݷ������� */
    zl_printf_byte((uint8_t)ch);
    return (ch);
}


/*   F G E T C   */
/*-------------------------------------------------------------------------
    * ���ܣ��ض���c�⺯����
    * ������1.�ļ�ָ�롣
    * ���أ���ȡ�����ַ���
    * ��ע��δ���ԡ�
-------------------------------------------------------------------------*/
int fgetc(FILE *f)
{
    return 0;
}


/*   I T O A   */
/*-------------------------------------------------------------------------
    * ���ܣ������������ת�����ַ�����
    * ������1.��ת�������֣�
    *       2.���ת���õ��ַ���������ָ�룻
    *       3.���ݽ��ƣ�֧�� 2 ��8 �� 10 ��16���ơ�
    * ���أ�����ָ�롣
    * ��ע��OK.
-------------------------------------------------------------------------*/
static char *itoa(int num, char *str, int radix)
{
    char string[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    char* ptr = str;
    int i;
    int j;


    /* �޸�ԭ��������� 0 ֵ */
    if (0 == num)
    {
        *ptr++ = string[num];
        *ptr = '\0';
        return str;
    }

    while (num)
    {
        *ptr++ = string[num % radix];
        num /= radix;

        if (num < radix)
        {
            *ptr++ = string[num];
            *ptr = '\0';
            break;
        }
    }

    j = ptr - str - 1;

    for (i = 0; i < (ptr - str) / 2; i++)
    {
        int temp = str[i];
        str[i]   = str[j];
        str[j--] = temp;
    }

    return str;
}


/*   Z L _ P R I N T F   */
/*-------------------------------------------------------------------------
    * ���ܣ���ʽ������ַ�����
    * ������1.�������ַ�����ָ�룻
    *       2.����б�
    * ���أ��ޡ�
    * ��ע��OK.
-------------------------------------------------------------------------*/
void zl_printf(uint8_t *Data,...)
{

    const char *s;
    int d;
    char buf[16];
    va_list ap;


    va_start(ap, Data);

    while ( *Data != 0)                         /* �ж��ַ��������� */
    {
        if ( *Data == 0x5c )                   /* '\' */
        {
            switch ( *++Data )
            {
                case 'r':                      /* �س��� */
                    zl_printf_byte(0x0d);
                    Data ++;
                    break;

                case 'n':                      /* ���з� */
                    zl_printf_byte(0x0a);
                    Data ++;
                    break;

                default:
                    Data ++;
                    break;
            }
        }
        else if ( *Data == '%')
        {
            switch ( *++Data )
            {
                case 's':
                    s = va_arg(ap, const char *);
                    for ( ; *s; s++)
                    {
                        zl_printf_byte(*s);
                    }
                    Data++;
                    break;

                case 'd':
                case 'i':
                    d = va_arg(ap, int);
                    itoa(d, buf, 10);
                    for (s = buf ; *s; s++)
                    {
                        zl_printf_byte(*s);
                    }
                    Data++;
                    break;

                case 'x':
                case 'X':
                    d = va_arg(ap, int);
                    itoa(d, buf, 16);
                    for (s = buf ; *s; s++)
                    {
                        zl_printf_byte(*s);
                    }
                    Data++;
                    break;

                default:
                    Data ++;
                    break;
            }
        }
        else
        {
            zl_printf_byte(*Data++);
        }
    }
}


/*   Z L _ P R I N T F _ S T R I N G   */
/*-------------------------------------------------------------------------
    * ���ܣ�ͨ�����ڷ����ַ������ݡ�
    * ������1.�������ַ�����ָ�롣
    * ���أ���
    * ��ע��OK.
-------------------------------------------------------------------------*/
void zl_printf_string(const uint8_t *pchStr)
{
    /* �ж������Ƿ���Ч */
    while (*pchStr)
    {

        if (*pchStr == '\r')                /* ����س��� */
        {
            zl_printf_byte(0x0d);
        }
        else if (*pchStr == '\n')           /* �����з� */
        {
            zl_printf_byte(0x0a);
        }
        else
        {
            zl_printf_byte(*pchStr);
        }

        /* ָ����һ���ֽ� */
        pchStr++;
    }
}


/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

