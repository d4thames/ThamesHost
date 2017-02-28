#include "thameshost.h"

void initialise_screen(void)
{
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
}

int main(void)
{
	// Open File, Initialise System
	FILE* serial_port = fopen(PORT_LOCATION, "r");
	mode = telemetry;

	// Initialise Screen
	initialise_screen();
	attron(A_BOLD);
	mvprintw( 0, TEXT_OFFSET, "D4 Thames Telemetry and Debugging System");
	attroff(A_BOLD);
	attron(A_UNDERLINE);
	mvprintw( 2, TEXT_OFFSET, "Remote Control Inputs");
	attroff(A_UNDERLINE);
	mvprintw( 3, TEXT_OFFSET, "Throttle NA");
	mvprintw( 4, TEXT_OFFSET, "Yaw      NA");
	mvprintw( 5, TEXT_OFFSET, "Pitch    NA");
	mvprintw( 6, TEXT_OFFSET, "Roll     NA");
	attron(A_UNDERLINE);
	mvprintw( 8, TEXT_OFFSET, "Linear Acceleration");
	attroff(A_UNDERLINE);
	mvprintw( 9, TEXT_OFFSET, "lX NA");
	mvprintw(10, TEXT_OFFSET, "lY NA");
	mvprintw(11, TEXT_OFFSET, "lZ NA");
	attron(A_UNDERLINE);
	mvprintw(13, TEXT_OFFSET, "Angular Acceleration");
	attroff(A_UNDERLINE);
	mvprintw(14, TEXT_OFFSET, "aX NA");
	mvprintw(15, TEXT_OFFSET, "aY NA");
	mvprintw(16, TEXT_OFFSET, "aZ NA");

	while (1) {
		// Read from file
		input_byte = fgetc(serial_port);

		// Deal with input
		switch (mode) {
			case telemetry:
				// Get control code and data from input
				if (!(input_byte & 0x80)) {
					control_code = (input_byte & 0xE0) >> 5;
					input_data = (input_byte & 0x1F);
				} else {
					control_code = (input_byte & 0xF0) >> 4;
					input_data = (input_byte & 0x0F);
				}
				switch (control_code) {
					// Remote Control Input					
					case S_THROTTLE:
						mvprintw( 3, TEXT_OFFSET, "Throttle %f", input_data/31);
						clrtoeol();
						break;
					case S_YAW:
						mvprintw( 4, TEXT_OFFSET, "Yaw      %f", input_data/31);
						clrtoeol();
						break;
					case S_PITCH:
						mvprintw( 5, TEXT_OFFSET, "Pitch    %f", input_data/31);
						clrtoeol();
						break;
					case S_ROLL:
						mvprintw( 6, TEXT_OFFSET, "Roll     %f", input_data/31);
						clrtoeol();
						break;
					// Linear Acceleration
					case S_LINX:
						mvprintw( 9, TEXT_OFFSET, "lX %f", input_data/15);
						clrtoeol();
						break;
					case S_LINY:
						mvprintw(10, TEXT_OFFSET, "lY %f", input_data/15);
						clrtoeol();
						break;
					case S_LINZ:
						mvprintw(11, TEXT_OFFSET, "lZ %f", input_data/15);
						clrtoeol();
						break; 
					// Angular Acceleration
					case S_ANGX:
						mvprintw(14, TEXT_OFFSET, "aX %f", input_data/15);
						clrtoeol();
						break;
					case S_ANGY:
						mvprintw(15, TEXT_OFFSET, "aY %f", input_data/15);
						clrtoeol();
						break;
					case S_ANGZ:
						mvprintw(16, TEXT_OFFSET, "aZ %f", input_data/15);
						clrtoeol();
						break; 					
					// Start/Stop Signals
					case S_STARTF:
						// Unexpected Start Signal
						mvprintw(18, TEXT_OFFSET, "E Unexpected start signal received (%d).", input_byte);
						clrtoeol();
						break;
					case S_STOPF:
						// Flight has stopped
						// Change to tuning mode
						mvprintw(18, TEXT_OFFSET, "M Flight Stopped, changing to tuning mode.");
						mode = tuneing;
						clrtoeol();
						break;
					default:
						mvprintw(18, TEXT_OFFSET, "E Unexpected symbol received (%d).", input_byte);
						clrtoeol();
						break;
				}
				break;
			case tuneing:
				mvprintw(18, TEXT_OFFSET, "E Tuning not yet implemented.");
				clrtoeol();
				mode = telemetry;
				break;
		}
		refresh();
		usleep(1000000);
		// sleep(0.5);
	}

	return 0; // Unreachable
}
