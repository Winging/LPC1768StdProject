/****************************************Copyright (c)****************************************************
**                                      
**                                 �����
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               RTCTime.c
** Descriptions:            RTCTime.c ��ʵʱʱ�ӽ��в����Ŀ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              �ƶ���
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
#include "RTCTime.h"
/**
 **@name RTCTime_Init
 **@params void
 **@return void
 **@description ��ʼ��ʵʱʱ��
 **@Calls 
 **@CalledBy 
 **/
void YF_RTCTime_Init(void)
{
	RTC_Init(LPC_RTC);
}
/**
 **@name RTCTime_Start
 **@params void
 **@return void
 **@description ����ʵʱʱ��
 **@Calls 
 **@CalledBy 
 **/
void YF_RTCTime_Start(void)
{
	/* Enable rtc (starts increase the tick counter and second counter register) */
	RTC_ResetClockTickCounter(LPC_RTC);
	RTC_Cmd(LPC_RTC, ENABLE);
}
/**
 **@name RTCTime_SetTime
 **@params time  RTCTimeTypedef����
 **@return void
 **@description ����ʵʱʱ��ʱ��
 **@Calls 
 **@CalledBy 
 **/
void YF_RTCTime_SetTime(RTCTimeTypeDef Time )
{
	LPC_RTC->SEC = Time.RTC_Sec;
	LPC_RTC->MIN = Time.RTC_Min;
	LPC_RTC->HOUR = Time.RTC_Hour;
	LPC_RTC->DOM = Time.RTC_Mday;
	LPC_RTC->DOW = Time.RTC_Wday;
	LPC_RTC->DOY = Time.RTC_Yday;
	LPC_RTC->MONTH = Time.RTC_Mon;
	LPC_RTC->YEAR = Time.RTC_Year;    
	return;
}
/**
 **@name RTCTime_GetTime
 **@params void
 **@return RTCTimeTypeDef�������� ���������� ʱ�����ܼ�����Ϣ
 **@description ��ȡʵʱʱ�ӵ�ʱ��
 **@Calls 
 **@CalledBy 
 **/
RTCTimeTypeDef YF_RTCTime_GetTime(void)
{
	RTCTimeTypeDef LocalTime;
    
	LocalTime.RTC_Sec = LPC_RTC->SEC;
	LocalTime.RTC_Min = LPC_RTC->MIN;
	LocalTime.RTC_Hour = LPC_RTC->HOUR;
	LocalTime.RTC_Mday = LPC_RTC->DOM;
	LocalTime.RTC_Wday = LPC_RTC->DOW;
	LocalTime.RTC_Yday = LPC_RTC->DOY;
	LocalTime.RTC_Mon = LPC_RTC->MONTH;
	LocalTime.RTC_Year = LPC_RTC->YEAR;
	return ( LocalTime );  
}
/**
 **@name RTCTime_SetTimeByYDMHMSW
 **@params year,mon,day,hour,min,sec,dow�ֱ��Ӧ�꣬�£��գ�ʱ���֣��룬�ܼ�
 **@return void
 **@description ����ʵʱʱ��ʱ��
 **@Calls 
 **@CalledBy 
 **/
void YF_RTCTime_SetTimeByYDMHMSW(uint32_t year,uint32_t mon,uint32_t day,uint32_t hour,uint32_t min,uint32_t sec,uint32_t dow)
{
	LPC_RTC->SEC = sec;
	LPC_RTC->MIN = min;
	LPC_RTC->HOUR = hour;
	LPC_RTC->DOM = day;
	LPC_RTC->MONTH = mon;
	LPC_RTC->YEAR = year+2000;
	LPC_RTC->DOW = dow;
	return;
}
