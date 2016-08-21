/*
 * i2c.h
 *
 *  Created on: 08.08.2016
 *      Author: Jack
 */

#ifndef I2C_H_
#define I2C_H_

#include "constants.h"

#define SHIFTDIR_FORWARD 0
#define SHIFTDIR_BACKWARD 1

extern unsigned char rgbmem[];//for RGB-Values
extern unsigned char parammem[];//for Program Parameters
void i2c_init(void);

extern unsigned int rgb_numleds;

void  rgb_initdemo(void);
#define rgb_getnumleds() rgb_numleds
//returns length memory used for rgb values
#define rgb_getlength() (3*rgb_numleds)
#ifndef COMPILE_MINIMAL
void rgb_addoffset(signed char);
void rgb_shift(unsigned char dir);
#endif

extern void i2c_onwritecomplete(unsigned char* ptr,unsigned int len);
extern void i2c_oncommand(unsigned int command,unsigned char* params);


#endif /* I2C_H_ */
