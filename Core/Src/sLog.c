#include "sLog.h"
uint16_t Point;
char textTotransmit[128][256];
uint8_t textlen[128];
void sLogPrint(char* text,...){
	va_list (arg);
	va_start(arg, text);
		vsprintf(&textTotransmit[Point][0], text, arg);
		va_end(arg);
		textlen[Point] = strlen(&textTotransmit[Point][0]);
		Point++;
}

void sLogUpdate(){
	if(Point)
	for(uint8_t i = 0; i < Point + 1; i++){
	CDC_Transmit_FS(&textTotransmit[i][0],textlen[i]);
	}
	Point = 0;
}
