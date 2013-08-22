/****************************************Copyright (c)****************************************************
**                                        翼起飞
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The UCOSII application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              黄东润
** Created date:            2013-8-19
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
/* Includes ********************************************************************************************/
#include "includes.h"
#include "RingBuffer.h"
#include "App.h"
#include "RTCTime.h"

/* uc/os-ii任务相关声明******************************************************************/
//堆栈声明
static  OS_STK  App_TaskStartStk[APP_TASK_START_STK_SIZE];  //初始化任务堆栈定义

//启动任务声明
static void AppTaskStart(void * pdata);

//任务之间通信相关声明


/* uc/os-ii 任务相关定义 ******************************************/
//初始化任务
static void AppTaskStart(void * pdata)
{
    INT8U os_err;
	os_err = os_err;
	/*
	 此处创建任务
	 */
    OSTaskDel(OS_PRIO_SELF);//当所有任务创建完成删除本任务
}
int c_entry()
{
    INT8U  os_err;
    os_err = os_err;
	
    OSInit();//初始化uc-os/ii
    
    os_err = OSTaskCreate(AppTaskStart,
                            (void*)0,
                            &App_TaskStartStk[APP_TASK_START_STK_SIZE-1],
                            APP_TASK_START_PRIO);
    
    OSStart();//启动uc-os/ii
	return 0;
}

int main()
{
    return c_entry();
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
