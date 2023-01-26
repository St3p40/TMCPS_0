#include "sLog.h"

struct{
  uint16_t startPoint;
  uint16_t endPoint;
  char textToTransmit[S_LOG_FIFO_AMOUNT][S_LOG_FIFO_SIZE];
  uint16_t size;

    struct{
      char textToTransmit[S_LOG_FIFO_SIZE];
      uint16_t size;
    }FIFO[S_LOG_FIFO_AMOUNT];

}sLog;

void sLogPrint(char* text,...){
	va_list (arg);
	va_start(arg, text);
		vsprintf(sLog.FIFO[sLog.endPoint].textToTransmit, text, arg);
		va_end(arg);
		sLog.FIFO[sLog.endPoint].size = strlen(sLog.FIFO[sLog.endPoint].textToTransmit);
	sLog.endPoint++;
}

void sLogUpdate(){
	if(sLog.startPoint != sLog.endPoint)
	for(uint16_t point = sLog.startPoint; point != sLog.endPoint+1; point = (point+1)%S_LOG_FIFO_AMOUNT){
	CDC_Transmit_FS(sLog.FIFO[point].textToTransmit,sLog.FIFO[point].size);}
	sLog.startPoint = sLog.endPoint;
}
