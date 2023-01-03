#include "sLog.h"
void sLog(uint8_t* text){
	CDC_Transmit_FS(text, strlen(text));
}
