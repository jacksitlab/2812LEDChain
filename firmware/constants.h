/*
 * constants.h
 *
 *  Created on: 08.08.2016
 *      Author: Jack
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define NUMLEDSMAX 250

#define I2C_ADDRESS_DEFAULT 0x44

#define COMMAND_TESTRUN 0x01
#define COMMAND_OFFSET 0x02 			// param: [-127 <=x <= +127]
#define COMMAND_SETSENDINGMODE 0x03 // param: 0 send single, 1 send permanently
#define COMMAND_DEMO_KITT 0x04
#define COMMAND_RINGBUFFER 0x05
#define COMMAND_SETLENGTH 0x06
#define COMMAND_SETADDRESS 0x07
#define COMMAND_SETFACTORS 0x08
#define COMMAND_FADEOUT 0x09		// param: delay(unsigned int)
#define COMMAND_FADEIN 0x0A			// param: delay(unsigned int)
#define COMMAND_FADEOUT_LTR 0x0B	// param: delay(unsigned int)
#define COMMAND_FADEIN_LTR 0x0C		// param: delay(unsigned int)
#define COMMAND_FADEOUT_RTL 0x0D	// param: delay(unsigned int)
#define COMMAND_FADEIN_RTL 0x0E		// param: delay(unsigned int)

//#define COMPILE_MINIMAL

#endif /* CONSTANTS_H_ */
