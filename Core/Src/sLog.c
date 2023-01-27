#include "sLog.h"

typedef struct{
  char msgBuff[S_LOG_FIFO_MSG_BUF_SIZE];
  uint16_t msgSize;
}FIFO;

struct{
  uint16_t startPoint;
  uint16_t endPoint;
  FIFO fifo[S_LOG_FIFO_OBJ_AMOUNT];
}sLog;

void sLogPrint(char* text,...){
  va_list (arg);
  va_start(arg, text);
  int16_t messageSize = vsnprintf(sLog.fifo[sLog.endPoint].msgBuff, S_LOG_FIFO_MSG_BUF_SIZE, text, arg);
  va_end(arg);
  if(messageSize > S_LOG_FIFO_MSG_BUF_SIZE - 1){
    sLog.fifo[sLog.endPoint].msgBuff[S_LOG_FIFO_MSG_BUF_SIZE - 2] = '\n';
  	sLog.fifo[sLog.endPoint].msgSize = S_LOG_FIFO_MSG_BUF_SIZE;
  }
  else{
	sLog.fifo[sLog.endPoint].msgSize = messageSize;
  }
  if(messageSize < 1){
	sLog.fifo[sLog.endPoint].msgSize = sprintf(sLog.fifo[sLog.endPoint].msgBuff,"sLogErr%d",messageSize);
  }
  sLog.endPoint = (sLog.endPoint + 1) % S_LOG_FIFO_OBJ_AMOUNT;
}

void sLogUpdate(){
  if(sLog.startPoint != sLog.endPoint)
    for(uint16_t point = sLog.startPoint; point != sLog.endPoint; point = (point+1)%S_LOG_FIFO_OBJ_AMOUNT){
      if(sLog.fifo[point].msgSize)
        CDC_Transmit_FS(sLog.fifo[point].msgBuff,sLog.fifo[point].msgSize);
    }
  sLog.startPoint = sLog.endPoint;
}
