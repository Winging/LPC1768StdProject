/****************************************Copyright (c)*******************************************************
**                                      
**                                 �����
**
**--------------File Info------------------------------------------------------------------------------------
** File name:               AppGlobal.h
** Descriptions:            AppGlobal.c ͷ�ļ�������ȫ�ֱ�����ȫ�ֽӿ�
**
**---------------Created By ---------------------------------------------------------------------------------
** Created by:              �ƶ���
** Created date:            2013-08-19
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------Modify history-------------------------------------------------------------------------------
** 1��
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
************************************************************************************************************/

#ifndef __APP_GLOABL_H__
#define __APP_GLOBAL_H__
#include "includes.h"
/**
 **@name YF_Global_Init
 **@params void
 **@return void
 **@description ��ʼ��ȫ�ֱ���
 **@Calls 
 **@CalledBy 
 **/
void YF_Global_Init(void);
/**
 **@name YF_Global_GetSerialMac
 **@params void
 **@return void
 **@description ��ʼ��ȫ�ֱ���
 **@Calls 
 **@CalledBy emac.c #tapdev_init#;
 **/
const uint8_t* YF_Global_GetSerialMac(void);
#endif

