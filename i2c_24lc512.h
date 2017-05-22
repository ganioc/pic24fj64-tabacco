#include "p24FJ64GA006.h"
#include "Pin_Definitions.h"
#include "i2c.h"
#include "stdio.h"

#define I2C_BRG 37 //400k

void i2c_init(void);
uchar Read_24lc512(uint16 address);
void Write_24lc512(uint16 address,uchar val);

