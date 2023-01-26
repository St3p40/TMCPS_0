#include "sLog.h"

struct{
  uint16_t startPoint;
  uint16_t endPoint;
}sLog;

struct{
  char textToTransmit[S_LOG_FIFO_SIZE];
  uint16_t size;
}FIFO[S_LOG_FIFO_AMOUNT];
void sLogPrint(char* text,...){
	va_list (arg);
	va_start(arg, text);
		vsprintf(FIFO[sLog.endPoint].textToTransmit, text, arg);
		va_end(arg);
		FIFO[sLog.endPoint].size = strlen(FIFO[sLog.endPoint].textToTransmit);
	sLog.endPoint++;
}

void sLogUpdate(){
	if(sLog.startPoint != sLog.endPoint)
	for(uint16_t point = sLog.startPoint; (point)%S_LOG_FIFO_AMOUNT != sLog.endPoint+1; point = (point+1)%S_LOG_FIFO_AMOUNT){
	CDC_Transmit_FS(FIFO[point].textToTransmit,FIFO[point].size);}
	sLog.startPoint = sLog.endPoint;
}
