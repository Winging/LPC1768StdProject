/*************************************************************************************
*@author:����
*@file:uip_app_conf.h
*@description:���ļ����ڶ���UIPЭ��ջ��صĽṹ���Լ���صĺ�����
*@time:2013-1-6
*/
#ifndef __APP_UIP_CONF_H
#define __APP_UIP_CONF_H
#include "lpc_types.h"
/**�ṹ�嶨��*/
struct CommandState
{
	//ΪTCPͨ��Ԥ����Ӧ�ýṹ�嶨��
	enum {CONNECTED,COMMAND_RECEIVED,RESPONSE_SEND,IDLE} state;
	uint32_t ptrToSend;//ָ��Ҫ���͵�����
	uint32_t leftDataLen;//��Ҫ�������ݵĳ���
} ;
typedef struct CommandState uip_tcp_appstate_t;
typedef struct 
{
	//ΪUDPͨ�Ŷ����Ӧ�ýṹ�壬ÿ��UDP����uip_udp_conn�������һ�������ڱ�ʾӦ��ͨ��״̬�ȣ��ڴ�Ӧ���в���Ҫ��
	char c;
} uip_udp_appstate_t;

/**UIP �궨��**/
//TCP �ص���������
#ifndef UIP_APPCALL
#define UIP_APPCALL YF_TcpApp
#endif
//UDP �ص������Ķ���
#ifndef UIP_UDP_APPCALL
#define UIP_UDP_APPCALL UDPNetApp
#endif
#endif

