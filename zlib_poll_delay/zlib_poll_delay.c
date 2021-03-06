/**
  ******************************************************************************
  * @file    ZYSlib/zlib_poll_delay.c
  * @author  ZYS
  * @version V1.0.0
  * @date    01/20/2017
  * @brief   这是一个简单好用的轮询延时器模块，支持多个延时实例。
  ******************************************************************************
  */


/* Debug log -----------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
/**
* 头文件的包含排规则采用稳定度排序。
* 经常变化的不稳定头文件放前面，稳定的如标准库的相关头文件放后面。
* 这样做的好处是可以提早发现编译错误，减少部分编译时间。
**/

#include ".\zlib_poll_delay.h"

/* Private define ------------------------------------------------------------*/
/* 定义可用的延时数量 */
#define ZL_POLL_DELAY_NUM   5

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct {
    uint32_t Time;
} zl_PollDelay_t;

/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static zl_PollDelay_t s_tPollBuf[ZL_POLL_DELAY_NUM];

/* Global  variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/






/*   Z L _ P O L L _ D E L A Y _ S E T   */
/*-------------------------------------------------------------------------
 功能描述  : 设定延时时间，同时启动延时。
 输入参数  : uint8_t chUserId  延时器ID
             uint16_t hwTime   延时时间
 输出参数  : 无
 返 回 值  : 
 
 修改历史      
  1.日    期   : 2017年2月6日
    作    者   : zys
    修改内容   : 新生成函数,OK。

-------------------------------------------------------------------------*/
bool zl_poll_delay_set(uint8_t chUserId, uint16_t hwTime)
{
    if (chUserId >= ZL_POLL_DELAY_NUM) {
        return false;
    }

    if (0 == hwTime) {
        return false;
    }

    s_tPollBuf[chUserId].Time = hwTime;

    return true;

}


/*   Z L _ P O L L _ D E L A Y _ T I M E O U T   */
/*-------------------------------------------------------------------------
 功能描述  : 查询给定ID的延时器是否超时。
 输入参数  : uint8_t chUserId  
 输出参数  : 无
 返 回 值  : true 超时；false 未超时。
 
 修改历史      
  1.日    期   : 2017年5月22日
    作    者   : zys
    修改内容   : 新生成函数。

-------------------------------------------------------------------------*/
bool zl_poll_delay_timeout(uint8_t chUserId)
{
    if (chUserId >= ZL_POLL_DELAY_NUM) {
        return false;
    }

    if ( !s_tPollBuf[chUserId].Time) {
        return true;
    }

    return false;
}


/*   Z L _ P O L L _ D E L A Y _ T I C K   */
/*-------------------------------------------------------------------------
 功能描述  : 延时模块的驱动任务，在心跳中断里运行。
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 
 修改历史      
  1.日    期   : 2017年5月22日
    作    者   : zys
    修改内容   : 新生成函数。

-------------------------------------------------------------------------*/
void zl_poll_delay_tick(void)
{
    uint8_t i;


    for ( i = 0 ; i < ZL_POLL_DELAY_NUM; i++ ) {
        if (s_tPollBuf[i].Time) {
            s_tPollBuf[i].Time--;
        }
    }
}



/*************************** (C) COPYRIGHT 2017 ZYS ************END OF FILE****/


