// for direct input
// termios, TCSANOW, ECHO, ICANON
#include <termios.h>
#include <unistd.h>

// for non blocking input
#include <fcntl.h>

#include <stdio.h> 
#include <stdlib.h>

#include <pthread.h>
#include <string.h>

#include "tetris.h"
#include "graphics.h"

int width = 8;
int height = 20;


void* f(void* args) {
	while (_g_board_live != true)
		usleep(100000);
	color (*board)[width] = (color (*)[width]) _g_board;
	while (true) {
		printboard(width, height, board);
		usleep(1000000/20);
	}
}

int main() {

	// makes IO non-blocking
	fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

	// makes io don't wait for enter
	static struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	//

	pthread_t cThread;
	pthread_create(&cThread, NULL, f, NULL);
#ifdef AUTOPLAY
	game_loop(width, height, 7, &move_generator);
#else
	game_loop(width, height, 7, &move_manual);
#endif

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
