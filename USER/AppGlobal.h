/****************************************Copyright (c)*******************************************************
**                                      
**                                 翼起飞
**
**--------------File Info------------------------------------------------------------------------------------
** File name:               AppGlobal.h
** Descriptions:            AppGlobal.c 头文件，定义全局变量及全局接口
**
**---------------Created By ---------------------------------------------------------------------------------
** Created by:              黄东润
** Created date:            2013-08-19
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------Modify history-------------------------------------------------------------------------------
** 1、
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
 **@description 初始化全局变量
 **@Calls 
 **@CalledBy 
 **/
void YF_Global_Init(void);
/**
 **@name YF_Global_GetSerialMac
 **@params void
 **@return void
 **@description 初始化全局变量
 **@Calls 
 **@CalledBy emac.c #tapdev_init#;
 **/
const uint8_t* YF_Global_GetSerialMac(void);
#endif

