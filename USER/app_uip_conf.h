/*************************************************************************************
*@author:东润
*@file:uip_app_conf.h
*@description:该文件用于定义UIP协议栈相关的结构体以及相关的宏配置
*@time:2013-1-6
*/
#ifndef __APP_UIP_CONF_H
#define __APP_UIP_CONF_H
#include "lpc_types.h"
/**结构体定义*/
struct CommandState
{
	//为TCP通信预留的应用结构体定义
	enum {CONNECTED,COMMAND_RECEIVED,RESPONSE_SEND,IDLE} state;
	uint32_t ptrToSend;//指向要发送的数据
	uint32_t leftDataLen;//需要发送数据的长度
} ;
typedef struct CommandState uip_tcp_appstate_t;
typedef struct 
{
	//为UDP通信定义的应用结构体，每个UDP连接uip_udp_conn都会分配一个，用于表示应用通信状态等，在此应用中不需要；
	char c;
} uip_udp_appstate_t;

/**UIP 宏定义**/
//TCP 回调函数定义
#ifndef UIP_APPCALL
#define UIP_APPCALL YF_TcpApp
#endif
//UDP 回调函数的定义
#ifndef UIP_UDP_APPCALL
#define UIP_UDP_APPCALL UDPNetApp
#endif
#endif

