#ifndef _TEL_COMMS_SPEC_H_
	#define _TEL_COMMS_SPEC_H_

		// Remote Control Input Symbols
		#define S_THROTTLE 0b000
		#define S_YAW      0b001
		#define S_PITCH    0b010
		#define S_ROLL     0b011

		// Linear Acceleration
		#define S_LINX     0b1000
		#define S_LINY     0b1001
		#define S_LINZ     0b1010

		// Angular Acceleration
		#define S_ANGX     0b1011
		#define S_ANGY     0b1100
		#define S_ANGZ     0b1101

		// Start/Stop Signals
		#define S_STARTF   0b1110
		#define S_STOPF    0b1111

#endif