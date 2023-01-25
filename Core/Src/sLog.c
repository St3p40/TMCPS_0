#include "sLog.h"
uint8_t sLog(char* text,...){
	char textTotransmit[128] = {0};
	va_list (arg);
	va_start(arg, text);
		vsprintf(textTotransmit, text, arg);
		va_end(arg);
	return CDC_Transmit_FS(textTotransmit,strlen(textTotransmit));
}
