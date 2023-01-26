#include "sLog.h"
struct{
uint16_t Point;
char textTotransmit[128][256];
uint8_t textlen[128];
}sLog;
void sLogPrint(char* text,...){
	va_list (arg);
	va_start(arg, text);
		vsprintf(&sLog.textTotransmit[sLog.Point][0], text, arg);
		va_end(arg);
		sLog.textlen[sLog.Point] = strlen(&sLog.textTotransmit[sLog.Point][0]);
		sLog.Point++;
}

void sLogUpdate(){
	if(sLog.Point)
	for(uint8_t i = 0; i < sLog.Point + 1; i++){
	CDC_Transmit_FS(&sLog.textTotransmit[i][0],sLog.textlen[i]);
	}
	sLog.Point = 0;
}
