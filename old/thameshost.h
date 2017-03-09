// Compile with -lncurses

#ifndef _THAMESHOST_H_
	#define	_THAMESHOST_H_

		#include <ncurses.h>
		#include <stdio.h>
		#include <unistd.h>
		#include "tel-comms-spec.h"

		#define PORT_LOCATION "/dev/random"

		#define TEXT_OFFSET 1
	
		typedef struct {
			double p, i, d;
		} PID;

		enum {telemetry, tuning} mode;

		char input_byte, ui_input;
		int control_code;
		float input_data;

		void initialise_screen(void);
		int main(void);

#endif