/*

Harry Beadle
D4 Thames
Bluetooth (serial) Remote Control (remote.c)

Backup remote for if the Spektrum remote doesn't arrive in time.

*/

#include "remote.h"

int main(void)
{
	// Initalise the Screen
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);

	// Open the serial port
	FILE* port = fopen(FILENAME, "w");

	// Draw the Basic Screen
	// mvprintw(0, PAD, "Thrust 0x00");
	// mvprintw(0, PAD*2 + EMT, "Yaw 0x00");
	// mvprintw(0, PAD*3 + EMT*2, "Pitch 0x00");
	// mvprintw(0, PAD*4 + EMT*3, "Roll 0x00");
	mvprintw(1, PAD-1, "Drone Remote Control");
	mvprintw(3, PAD, "Thrust 0x00");
	mvprintw(4, PAD, "Yaw    0x00");
	mvprintw(5, PAD, "Pitch  0x00");
	mvprintw(6, PAD, "Roll   0x00");

	do {
		inchar = getch();
		switch (inchar) {
			case 'w':
				// Increace Thrust
				if (thrust != 31) {
					thrust++;
					fputc(S_THROTTLE & thrust, port);
					mvprintw(3, PAD, "Thrust 0x%02X", thrust);
				}
				break;
			case 's':
				// Decreace Thrust
				if (thrust != 0) {
					thrust--;
					fputc(S_THROTTLE & thrust, port);
					mvprintw(3, PAD, "Thrust 0x%02X", thrust);
				}
				break;
			case 'a':
				// Yaw right
				if (yaw != 0) {
					yaw--;
					fputc(S_YAW & yaw, port);
					mvprintw(4, PAD, "Yaw    0x%02X", yaw);
				}
				break;
			case 'd':
				// Yaw left
				if (yaw != 31) {
					yaw++;
					fputc(S_YAW & yaw, port);
					mvprintw(4, PAD, "Yaw    0x%02X", yaw);
				}
				break;
			case 'i':
				// Pitch forward
				if (pitch != 32) {
					pitch++;
					fputc(S_PITCH & pitch, port);
					mvprintw(5, PAD, "Pitch  0x%02X", pitch);
				}
				break;
			case 'k':
				// Pitch back
				if (pitch != 0) {
					pitch--;
					fputc(S_PITCH & pitch, port);
					mvprintw(5, PAD, "Pitch  0x%02X", pitch);
				}
				break;
			case 'j':
				// Roll left
				if (roll != 0) {
					roll--;
					fputc(S_ROLL & roll, port);
					mvprintw(6, PAD, "Roll   0x%02X", roll);
				}
				break;
			case 'l':
				// Roll right
				if (roll != 32) {
					roll++;
					fputc(S_ROLL & roll, port);
					mvprintw(6, PAD, "Roll   0x%02X", roll);
				}
				break;
			case 'c':
				// Cut thrust (safety measure)
				thrust = 0;
				fputc(S_THROTTLE & thrust, port);
				mvprintw(3, PAD, "Thrust cut!", thrust);
				break;
			default:
				break;
		}
	} while (inchar != 'q');

	return 0;
}