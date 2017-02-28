// Compile with -lncurses

#ifndef _THAMESHOST_H_
	#define	_THAMESHOST_H_

		#include <ncurses.h>
		#include <stdio.h>
		#include <unistd.h>
		#include "tel-comms-spec.h"

		#define PORT_LOCATION "/dev/random"

		#define TEXT_OFFSET 1
	
		enum {telemetry, tuneing} mode;

		char input_byte;
		int control_code;
		float input_data;

		void initialise_screen(void);
		int main(void);

#endif