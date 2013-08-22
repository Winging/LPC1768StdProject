#ifndef __APPDEBUG_H__
#define __APPDEBUG_H__
#include "includes.h"
/* 代码调试相关声明***************************************************/
#define DB _DBG((uint8_t *)_db)
extern char _db[128];//该变量用于输出调试信息
void uip_log(char *m);

#endif
