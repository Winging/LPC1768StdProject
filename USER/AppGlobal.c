/****************************************Copyright (c)****************************************************
**                                      
**                                 �����
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               AppTcpIP.h
** Descriptions:            AppTcpIP.c ͷ�ļ�������TCPͨ����ؽӿ�
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
#include "AppGlobal.h"
extern uint8_t serialMac[6];
/**
 **@name YF_Global_Init
 **@params void
 **@return void
 **@description ��ʼ��ȫ�ֱ���
 **@Calls 
 **@CalledBy 
 **/
void YF_Global_Init(void)
{
	
}
/**
 **@name YF_Global_GetSerialMac
 **@params void
 **@return void
 **@description ��ʼ��ȫ�ֱ���
 **@Calls 
 **@CalledBy emac.c #tapdev_init#;
 **/
const uint8_t* YF_Global_GetSerialMac(void)
{
	return serialMac;
}
