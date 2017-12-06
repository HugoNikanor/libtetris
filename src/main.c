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

void* draw_thread_func(void* args) {
	while (_g_board_live != true)
		usleep(100000);
	color (*board)[width] = (color (*)[width]) _g_board;
	while (true) {
		printboard(width, height, board);
		usleep(1000000/20);
	}
}

void print_help() {
	puts(
		"LibTetris Interactive Main\n"
		"==========================\n"
		"-a         | Sets autoplay\n"
		"-d <x>x<y> | Sets board size to\n"
		"           | width x and height y\n"
		"-h         | Show this help\n");
}

int main(int argc, char* argv[]) {

	// makes IO non-blocking
	fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

	// makes io don't wait for enter
	static struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	// Make the terminal not echo back,
	// along with enabling cononical mode
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	// Sets up the thread
	pthread_t cThread;
	pthread_create(&cThread, NULL, draw_thread_func, NULL);

	// Parses the arguments
	bool autoplay = false;
	int opt;
	while ((opt = getopt(argc, argv, "ad:h")) != -1) {
		switch (opt) {
			case 'a':
				autoplay = true;
				break;
			case 'd':
				sscanf(optarg, "%dx%d", &width, &height);
				break;
			case 'h':
			default:
				print_help();
				goto cleanup;
		}
	}

	// Creates a settings object
	tetris_settings settings = {
		.width = width,
		.height = height,
		.dropspeed = 7,
		.move_func = autoplay
		           ? &move_generator
		           : &move_manual
	};

	// Starts the game
	game_loop (&settings);

cleanup:
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
