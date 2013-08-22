#include "AppDebug.h"

/* 调试相关定义***********************************************/
void uip_log(char *m)
{
    _DBG("uIP log message: ");
    _DBG(m);
    _DBG_("");
}

/* nxp lib 调试选项***********************************/
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line)
{
	
}
#endif
