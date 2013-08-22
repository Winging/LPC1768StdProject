/****************************************Copyright (c)****************************************************
**                                        �����
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The UCOSII application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              �ƶ���
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

/* uc/os-ii�����������******************************************************************/
//��ջ����
static  OS_STK  App_TaskStartStk[APP_TASK_START_STK_SIZE];  //��ʼ�������ջ����

//������������
static void AppTaskStart(void * pdata);

//����֮��ͨ���������


/* uc/os-ii ������ض��� ******************************************/
//��ʼ������
static void AppTaskStart(void * pdata)
{
    INT8U os_err;
	os_err = os_err;
	/*
	 �˴���������
	 */
    OSTaskDel(OS_PRIO_SELF);//���������񴴽����ɾ��������
}
int c_entry()
{
    INT8U  os_err;
    os_err = os_err;
	
    OSInit();//��ʼ��uc-os/ii
    
    os_err = OSTaskCreate(AppTaskStart,
                            (void*)0,
                            &App_TaskStartStk[APP_TASK_START_STK_SIZE-1],
                            APP_TASK_START_PRIO);
    
    OSStart();//����uc-os/ii
	return 0;
}

int main()
{
    return c_entry();
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
