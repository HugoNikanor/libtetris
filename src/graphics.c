#include <stdio.h>

#include "graphics.h"

#define STMT(color) case color: \
	printf(color ## STR "█" DEFSTR);\
	break;

void printboard(int width, int height, color board[][width]) {
	puts("\x1B[H");

	printf("┌");
	for (int x = 0; x < width; x++)
		printf("─");
	printf("┐");
	putchar(0xA);

	for (int y = 0; y < height; y++) {
		printf("│");
		for (int x = 0; x < width; x++) {
			switch (board[y][x]) {
				STMT(GREEN);
				STMT(RED);
				STMT(ORANGE);
				STMT(YELLOW);
				STMT(BLUE);
				STMT(MAGENTA);
				STMT(CYAN);

				case EMPTY:
				default:
					putchar(' ');
			}
		}
		printf("│");
		putchar(0xA);
	}

	printf("└");
	for (int x = 0; x < width; x++)
		printf("─");
	printf("┘");
	putchar(0xA);
}
