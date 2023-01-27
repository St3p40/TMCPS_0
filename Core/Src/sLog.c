#include "sLog.h"

typedef struct{
  char msgBuff[S_LOG_FIFO_MSG_BUF_SIZE];
  int16_t msgSize;
}FIFO;

struct{
  uint16_t startPoint;
  uint16_t endPoint;
  FIFO fifo[S_LOG_FIFO_OBJ_AMOUNT];
}sLog;

void sLogPrint(char* text,...){
  va_list (arg);
  va_start(arg, text);
  sLog.fifo[sLog.endPoint].msgSize = vsnprintf(sLog.fifo[sLog.endPoint].msgBuff, S_LOG_FIFO_MSG_BUF_SIZE, text, arg);
  va_end(arg);
  sLog.endPoint=sLog.endPoint%S_LOG_FIFO_OBJ_AMOUNT;
}

void sLogUpdate(){
  if(sLog.startPoint != sLog.endPoint)
    for(uint16_t point = sLog.startPoint; point != sLog.endPoint; point = (point+1)%S_LOG_FIFO_OBJ_AMOUNT){
      if(sLog.fifo[point].msgSize > 0)
        CDC_Transmit_FS(sLog.fifo[point].msgBuff,sLog.fifo[point].msgSize);
    }
  sLog.startPoint = sLog.endPoint;
}
