#ifndef __S_LOG_H
#define __S_LOG_H
#include "stdint.h"
#include "stdarg.h"
#include "stdio.h"

#define S_LOG_FIFO_SIZE 128
#define S_LOG_FIFO_AMOUNT 256

void sLogPrint(char* text,...);
void sLogUpdate();
#endif
