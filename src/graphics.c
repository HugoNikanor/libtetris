#include <stdio.h>

#include "graphics.h"

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
				case GREEN:
					printf(GRNSTR "█" DEFSTR);
					break;
				case RED:
					printf(REDSTR "█" DEFSTR);
					break;
				case ORANGE:
					printf(ORGSTR "█" DEFSTR);
					break;
				case YELLOW:
					printf(YELSTR "█" DEFSTR);
					break;
				case BLUE:
					printf(BLUSTR "█" DEFSTR);
					break;
				case MAGENTA:
					printf(MAGSTR "█" DEFSTR);
					break;
				case CYAN:
					printf(CYASTR "█" DEFSTR);
					break;
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
