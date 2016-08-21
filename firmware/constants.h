/*
 * constants.h
 *
 *  Created on: 08.08.2016
 *      Author: Jack
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define NUMLEDSMAX 120


#define COMMAND_TESTRUN 0x01
#define COMMAND_OFFSET 0x02 			// param: [-127 <=x <= +127]
#define COMMAND_SETSENDINGMODE 0x03 // param: 0 send single, 1 send permanently
#define COMMAND_DEMO_KITT 0x04
#define COMMAND_RINGBUFFER 0x05

// #define COMPILE_MINIMAL

#endif /* CONSTANTS_H_ */
