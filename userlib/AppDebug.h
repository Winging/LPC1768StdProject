#ifndef __APPDEBUG_H__
#define __APPDEBUG_H__
#include "includes.h"
/* ��������������***************************************************/
#define DB _DBG((uint8_t *)_db)
extern char _db[128];//�ñ����������������Ϣ
void uip_log(char *m);

#endif
