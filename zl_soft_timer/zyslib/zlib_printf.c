/**
  ******************************************************************************
  * @file    ZYSlib/zlib_printf.c
  * @author  ZYS
  * @version V1.0.0
  * @date    01/20/2015
  * @brief   这是一个简单的串口通讯处理模块，实现 C99 标准下，与 MCU 平台无关
             的打印输出函数。
  ******************************************************************************
  */


/* Debug log -----------------------------------------------------------------*/


/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>             /* 系统标准头文件，支持可变参数函数 */
#include <stdio.h>              /* 系统标准头文件，支持IO操作 */
#include ".\zlib_printf.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* 供用户注册串口发送函数的函数指针 */
static fnusart_send_byte_t s_fnusart_send_byte = NULL;

/* Global  variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/





/*   Z L _ P R I N T F _ I N I T   */
/*-------------------------------------------------------------------------
    * 功能：初始化 zl_printf 模块，由用户注册一个发送单字节的函数。
    * 参数：1.发送一个字节的串口函数的指针。
    * 返回：无
    * 备注：OK.
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
    * 功能：通过串口发送一个字节的数据
    * 参数：1.待发送的字节数据。
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_printf_byte(uint8_t chData)
{
    (*s_fnusart_send_byte)(chData);
}


/*   F P U T C   */
/*-------------------------------------------------------------------------
* 功能：重定向c库函数 printf 到 MCU 的 USART.
* 参数：1.待发送字符；
*       2.文件指针。
* 返回：发送字符。
* 备注：OK.
        该函数由系统 printf 调用，与用户无关。
-------------------------------------------------------------------------*/
int fputc(int ch, FILE *f)
{
    /* 将Printf内容发往串口 */
    zl_printf_byte((uint8_t)ch);
    return (ch);
}


/*   F G E T C   */
/*-------------------------------------------------------------------------
    * 功能：重定向c库函数。
    * 参数：1.文件指针。
    * 返回：读取到的字符。
    * 备注：未测试。
-------------------------------------------------------------------------*/
int fgetc(FILE *f)
{
    return 0;
}


/*   I T O A   */
/*-------------------------------------------------------------------------
    * 功能：将输入的数字转换成字符串。
    * 参数：1.待转换的数字；
    *       2.存放转换好的字符串的数组指针；
    *       3.数据进制，支持 2 、8 、 10 、16进制。
    * 返回：数组指针。
    * 备注：OK.
-------------------------------------------------------------------------*/
static char *itoa(int num, char *str, int radix)
{
    char string[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    char* ptr = str;
    int i;
    int j;


    /* 修复原来不能输出 0 值 */
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
    * 功能：格式化输出字符串。
    * 参数：1.待发送字符串的指针；
    *       2.变参列表。
    * 返回：无。
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_printf(uint8_t *Data,...)
{

    const char *s;
    int d;
    char buf[16];
    va_list ap;


    va_start(ap, Data);

    while ( *Data != 0)                         /* 判断字符串结束符 */
    {
        if ( *Data == 0x5c )                   /* '\' */
        {
            switch ( *++Data )
            {
                case 'r':                      /* 回车符 */
                    zl_printf_byte(0x0d);
                    Data ++;
                    break;

                case 'n':                      /* 换行符 */
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
    * 功能：通过串口发送字符串数据。
    * 参数：1.待发送字符串的指针。
    * 返回：无
    * 备注：OK.
-------------------------------------------------------------------------*/
void zl_printf_string(const uint8_t *pchStr)
{
    /* 判断数据是否有效 */
    while (*pchStr)
    {

        if (*pchStr == '\r')                /* 处理回车符 */
        {
            zl_printf_byte(0x0d);
        }
        else if (*pchStr == '\n')           /* 处理换行符 */
        {
            zl_printf_byte(0x0a);
        }
        else
        {
            zl_printf_byte(*pchStr);
        }

        /* 指向下一个字节 */
        pchStr++;
    }
}


/*************************** (C) COPYRIGHT 2015 ZYS ************END OF FILE****/

