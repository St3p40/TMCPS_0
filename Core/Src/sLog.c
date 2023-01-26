#include "sLog.h"
typedef struct{
      char textToTransmit[S_LOG_FIFO_SIZE];
      uint16_t size;
}FIFO;
struct{
  uint16_t startPoint;
  uint16_t endPoint;
  FIFO fifo[S_LOG_FIFO_AMOUNT];
}sLog;

void sLogPrint(char* text,...){
	va_list (arg);
	va_start(arg, text);
		vsprintf(sLog.fifo[sLog.endPoint].textToTransmit, text, arg);
		va_end(arg);
		sLog.fifo[sLog.endPoint].size = strlen(sLog.fifo[sLog.endPoint].textToTransmit);
	sLog.endPoint++;
}

void sLogUpdate(){
	if(sLog.startPoint != sLog.endPoint)
	for(uint16_t point = sLog.startPoint; point != (sLog.endPoint+1)%S_LOG_FIFO_AMOUNT; point = (point+1)%S_LOG_FIFO_AMOUNT){
	CDC_Transmit_FS(sLog.fifo[point].textToTransmit,sLog.fifo[point].size);}
	sLog.startPoint = sLog.endPoint;
}
