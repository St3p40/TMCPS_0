#ifndef __S_LOG_H
#define __S_LOG_H
void sLog(uint8_t* text){
  CDC_Transmit_FS(text, strlen(text));
}
#endif
