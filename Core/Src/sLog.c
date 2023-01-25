#include "sLog.h"
uint8_t sLog(char* text,...){
	char textTotransmit[128] = {0};
		sprintf(textTotransmit, text);
	return CDC_Transmit_FS(textTotransmit,strlen(textTotransmit));
}
