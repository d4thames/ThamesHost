#include "thameshost.h"

void initialise_screen(void)
{
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
}

PID* write

void write_base_tun(void)
{
	clear();
	attron(A_BOLD);
	mvprintw( 0, TEXT_OFFSET, "Tuning System.");
	mvprintw( 1, TEXT_OFFSET, "Flight not available while tuning.");
	attroff(A_BOLD);
	mvprintw( 3, TEXT_OFFSET, "p - Edit Pitch System");
	mvprintw( 4, TEXT_OFFSET, "r - Edit Roll System");
	mvprintw( 5, TEXT_OFFSET, "y - Edit Yaw System");
}

void write_base_tel(void)
{
	clear();
	attron(A_BOLD);
	mvprintw( 0, TEXT_OFFSET, "Telemetry System");
	attroff(A_BOLD);
	attron(A_UNDERLINE);
	mvprintw( 2, TEXT_OFFSET, "Remote Control Inputs");
	attroff(A_UNDERLINE);
	mvprintw( 3, TEXT_OFFSET, "Throttle --------");
	mvprintw( 4, TEXT_OFFSET, "Yaw      --------");
	mvprintw( 5, TEXT_OFFSET, "Pitch    --------");
	mvprintw( 6, TEXT_OFFSET, "Roll     --------");
	attron(A_UNDERLINE);
	mvprintw( 8, TEXT_OFFSET, "Linear Acceleration");
	attroff(A_UNDERLINE);
	mvprintw( 9, TEXT_OFFSET, "lX --------");
	mvprintw(10, TEXT_OFFSET, "lY --------");
	mvprintw(11, TEXT_OFFSET, "lZ --------");
	attron(A_UNDERLINE);
	mvprintw(13, TEXT_OFFSET, "Angular Acceleration");
	attroff(A_UNDERLINE);
	mvprintw(14, TEXT_OFFSET, "aX --------");
	mvprintw(15, TEXT_OFFSET, "aY --------");
	mvprintw(16, TEXT_OFFSET, "aZ --------");
}

int main(void)
{
	// Open File, Initialise System
	FILE* serial_port = fopen(PORT_LOCATION, "r");
	mode = telemetry;

	// Initialise Screen
	initialise_screen();
	write_base_tel();

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
						mode = tuning;
						clrtoeol();
						write_base_tun();
						break;
					default:
						mvprintw(18, TEXT_OFFSET, "E Unexpected symbol received (%d).", input_byte);
						clrtoeol();
						break;
				}
				break;
			case tuning:
				ui_input = wgetch(stdscr);
				switch (ui_input) {
					case 'q':
						// Quit Tuning Mode
						// TODO Send End Symbol
						write_base_tel();
						mode = telemetry;
						break;
					case 'p':
						// Set p coefficient
						break;
					case 'r':
						// Set i coefficient
						break;
					case 'y':
						// Set i error threshold.
						break; 
					default:
						break;
				}
				break;
		}
		refresh();
		usleep(1000000);
	}
	return 0; // Unreachable
}
