/****************************************Copyright (c)****************************************************
**                                      
**                                 翼起飞
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               RTCTime.c
** Descriptions:            RTCTime.c 对实时时钟进行操作的库
**
**--------------------------------------------------------------------------------------------------------
** Created by:              黄东润
** Created date:            2013-08-19
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef __RTCTIME_H__
#define __RTCTIME_H__
#include "includes.h"
typedef struct {
    uint32_t RTC_Sec;     /* Second value - [0,59] */
    uint32_t RTC_Min;     /* Minute value - [0,59] */
    uint32_t RTC_Hour;    /* Hour value - [0,23] */
    uint32_t RTC_Mday;    /* Day of the month value - [1,31] */
    uint32_t RTC_Mon;     /* Month value - [1,12] */
    uint32_t RTC_Year;    /* Year value - [0,4095] */
    uint32_t RTC_Wday;    /* Day of week value - [0,6] */
    uint32_t RTC_Yday;    /* Day of year value - [1,365] */
} RTCTimeTypeDef;
/**
 **@name RTCTime_Init
 **@params void
 **@return void
 **@description 初始化实时时钟
 **@Calls 
 **@CalledBy 
 **/
void YF_RTCTime_Init(void);
/**
 **@name RTCTime_Start
 **@params void
 **@return void
 **@description 启动实时时钟
 **@Calls 
 **@CalledBy 
 **/
void YF_RTCTime_Start(void);
/**
 **@name RTCTime_SetTime
 **@params time  RTCTimeTypedef类型
 **@return void
 **@description 设置实时时钟时间
 **@Calls 
 **@CalledBy 
 **/
void YF_RTCTime_SetTime(RTCTimeTypeDef Time );
/**
 **@name RTCTime_SetTimeByYDMHMSW
 **@params year,mon,day,hour,min,sec,dow分别对应年，月，日，时，分，秒，周几
 **@return void
 **@description 设置实时时钟时间
 **@Calls 
 **@CalledBy 
 **/
void YF_RTCTime_SetTimeByYDMHMSW(uint32_t year,uint32_t mon,uint32_t day,uint32_t hour,uint32_t min,uint32_t sec,uint32_t dow);
/**
 **@name RTCTime_GetTime
 **@params void
 **@return RTCTimeTypeDef类型数据 包含年月日 时分秒周几的信息
 **@description 获取实时时钟的时间
 **@Calls 
 **@CalledBy 
 **/
RTCTimeTypeDef YF_RTCTime_GetTime(void);


#endif
