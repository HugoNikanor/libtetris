#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// termios, TCSANOW, ECHO, ICANON
#include <termios.h>

#include <fcntl.h>

typedef struct {
	int x;
	int y;
} point;

typedef enum
	{ EMPTY, GREEN, RED, ORANGE, YELLOW, BLUE, MAGENTA, CYAN }
tiles;

typedef unsigned char tile; 

typedef struct {
	tiles color;
	tile tile;
	point* shape; // list
} piece;

typedef enum { false, true } bool;

#define GRNSTR "\x1B[1;32m"
#define REDSTR "\x1B[1;31m"
#define ORGSTR "\x1B[0;33m"
#define YELSTR "\x1B[1;33m"
#define BLUSTR "\x1B[0;35m"
#define MAGSTR "\x1B[1;35m"
#define CYASTR "\x1B[0;36m"

#define DEFSTR "\x1B[m"

#define ROWS 20
#define COLUMNS 8

bool in_piece(point p, piece piece) {
	for (int i = 0; i < 4; i++) {
		point pp = piece.shape[i];
		if (p.x == pp.x && p.y == pp.y)
			return true;
	}
	return false;
}

void put_bar(int width) {
}
// ┌─┐
// │ │
// └─┘
void printboard(int width, int height, const tile board[][COLUMNS]) {
	puts("\x1B[H");

	putchar('+');
	for (int x = 0; x < width; x++)
		putchar('-');
	putchar('+');
	putchar(0xA);

	for (int y = 0; y < height; y++) {
		putchar('|');
		for (int x = 0; x < width; x++) {
			switch (board[y][x]) {
				case GREEN:
					fputs(GRNSTR "█" DEFSTR, stdout);
					break;
				case RED:
					fputs(REDSTR "█" DEFSTR, stdout);
					break;
				case ORANGE:
					fputs(ORGSTR "█" DEFSTR, stdout);
					break;
				case YELLOW:
					fputs(YELSTR "█" DEFSTR, stdout);
					break;
				case BLUE:
					fputs(BLUSTR "█" DEFSTR, stdout);
					break;
				case MAGENTA:
					fputs(MAGSTR "█" DEFSTR, stdout);
					break;
				case CYAN:
					fputs(CYASTR "█" DEFSTR, stdout);
					break;
				case EMPTY:
				default:
					putchar(' ');
					//putchar(board[y][x]);
			}
		}
		putchar('|');
		putchar(0xA);
	}
	putchar('+');
	for (int x = 0; x < width; x++)
		putchar('-');
	putchar('+');
	putchar(0xA);
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

	// I :: Cyan {{{2
	piece p_i = {
		.color = CYAN,
		.tile = 'I',
		.shape = malloc(sizeof(point) * 4)
	};
	point i_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 0, .y = 1},
		{.x = 0, .y = 2},
		{.x = 0, .y = 3},
	};
	p_i.shape = i_shape;

	// O :: Yellow {{{2
	piece p_o = {
		.color = YELLOW,
		.tile = 'O',
		.shape = malloc(sizeof(point) * 4)
	};
	point o_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 0, .y = 1},
		{.x = 1, .y = 0},
		{.x = 1, .y = 1},
	};
	p_o.shape = o_shape;

	// T :: Magenta {{{2
	piece p_t = {
		.color = MAGENTA,
		.tile = 'T',
		.shape = malloc(sizeof(point) * 4)
	};
	point t_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 1, .y = 0},
		{.x = 2, .y = 0},
		{.x = 1, .y = 1},
	};
	p_t.shape = t_shape;
	// S :: Green {{{2
	piece p_s = {
		.color = GREEN,
		.tile = 'S',
		.shape = malloc(sizeof(point) * 4)
	};
	point s_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 0, .y = 1},
		{.x = 1, .y = 1},
		{.x = 1, .y = 2},
	};
	p_s.shape = s_shape;
	// Z :: Red {{{2
	piece p_z = {
		.color = RED,
		.tile = 'Z',
		.shape = malloc(sizeof(point) * 4)
	};
	point z_shape[4] = {
		{.x = 1, .y = 0},
		{.x = 0, .y = 1},
		{.x = 1, .y = 1},
		{.x = 0, .y = 2},
	};
	p_z.shape = z_shape;
	// J :: Blue {{{2
	piece p_j = {
		.color = BLUE,
		.tile = 'J',
		.shape = malloc(sizeof(point) * 4)
	};
	point j_shape[4] = {
		{.x = 1, .y = 0},
		{.x = 1, .y = 1},
		{.x = 1, .y = 2},
		{.x = 0, .y = 2},
	};
	p_j.shape = j_shape;
	// L :: Orange {{{2
	piece p_l = {
		.color = ORANGE,
		.tile = 'L',
		.shape = malloc(sizeof(point) * 4)
	};
	point l_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 0, .y = 1},
		{.x = 0, .y = 2},
		{.x = 1, .y = 2},
	};
	p_l.shape = l_shape;

	///}}}2

	int width = COLUMNS;
	int height = ROWS;
	// is this safe?
	tile board[height][width];

	for (int y = 0; y < height; y++)
	for (int x = 0; x < width; x++)
	{
		board[y][x] = 0;
	}
	for (int x = 0; x < width; x++) {
		board[height][x] = 'X';
	}

	char c;
	int x = 1;

	int y = 0;
	//for (int y = 0; ; y = (y + 1) % height) {

	// TODO the quickdrop code makes the display
	// behave weird

	int dropspeed = 7;
	piece pieces[7] = {p_i, p_o, p_t, p_s, p_z, p_j, p_l};
	piece* pp = pieces;
	piece piece = *pp;
	bool quickdrop = false;
	for (int loop = 0;; loop++) {
		if (loop % dropspeed == 0) {
			y++;
		}

		if (!quickdrop) {
			c = getchar();

			if (c == 'l') ++x;
			if (c == 'h') --x;
			if (c == ' ') quickdrop = true;
		}
		//if (c == 'e') goto cleanup;

		for (int i = 0; i < 4; i++) {
			point p = piece.shape[i];
			board[y + p.y][x + p.x] = piece.color;
		}

		printboard(width, height, board);	
		if (!quickdrop)
			usleep(1000000 / dropspeed);
		//sleep(1);

		bool piece_stoped = false;
		for (int i = 0; i < 4; i++) {
			point p = {
				.x = piece.shape[i].x,
				.y = piece.shape[i].y + 1
			};

			if( board[y+p.y][x+p.x] != EMPTY
					&& !in_piece(p, piece))
				piece_stoped = true;
		}

		if (piece_stoped) {
			y = 0;
			x = 1;
			piece = *(++pp);
			quickdrop = false;
			continue;
		}

		// removes piece
		for (int i = 0; i < 4; i++) {
			point p = piece.shape[i];
			board[y + p.y][x + p.x] = EMPTY;
		}
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
