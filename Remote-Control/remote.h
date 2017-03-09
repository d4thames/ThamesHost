#ifndef _REMOTE_H_
	#define _REMOTE_H_

		#include <curses.h>
		#include <stdio.h>
		#include <stdint.h>

		#include "spec.h"
	
		#define FILENAME "output.hex"

		#define WTH 80
		#define HGT 24
		#define PAD 3
		#define EMT (WTH-(5*PAD))/4

		char inchar;
		uint8_t thrust, pitch, roll, yaw;

#endif