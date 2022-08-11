
#ifndef __DHT_H__
#define __DHT_H__

#include <stc12c5a60s2.h>

#define  uchar unsigned char
#define  uint  unsigned int

#define DHT11 0
#define DHT22 1

#define MODE DHT22

#define Data (P20)

void DHT11_receive(float* temp, float* humid);

#endif
