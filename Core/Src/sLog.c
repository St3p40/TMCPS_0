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
  vsprintf(sLog.fifo[sLog.endPoint].msgBuff, text, arg);
  va_end(arg);
  sLog.fifo[sLog.endPoint].msgSize = strlen(sLog.fifo[sLog.endPoint].msgBuff);
  sLog.endPoint=sLog.endPoint%S_LOG_FIFO_OBJ_AMOUNT;
}

void sLogUpdate(){
  if(sLog.startPoint != sLog.endPoint)
  for(uint16_t point = sLog.startPoint; point != sLog.endPoint; point = (point+1)%S_LOG_FIFO_OBJ_AMOUNT){
    CDC_Transmit_FS(sLog.fifo[point].msgBuff,sLog.fifo[point].msgSize);
  }
  sLog.startPoint = sLog.endPoint;
}
