#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

// for direct input
// termios, TCSANOW, ECHO, ICANON
#include <termios.h>

// for non blocking input
#include <fcntl.h>

typedef struct {
	int x;
	int y;
} point;

typedef enum
	{ EMPTY, GREEN, RED, ORANGE, YELLOW, BLUE, MAGENTA, CYAN }
color;

typedef struct {
	color color;
	unsigned rotation : 2;
	// the size of the bounding box of the piece - 1
	int bounds;
	point* shape; // list
} piece;

/*
 * You could add an ASCII mode by instetad setting the
 * background color. And then printing spaces.
 */

#define GRNSTR "\x1B[1;32m"
#define REDSTR "\x1B[1;31m"
#define ORGSTR "\x1B[0;33m"
#define YELSTR "\x1B[1;33m"
#define BLUSTR "\x1B[0;34m"
#define MAGSTR "\x1B[1;35m"
#define CYASTR "\x1B[0;36m"

#define DEFSTR "\x1B[m"

bool in_piece(point p, piece* piece) {
	for (int i = 0; i < 4; i++) {
		point pp = piece->shape[i];
		if (p.x == pp.x && p.y == pp.y)
			return true;
	}
	return false;
}

// board not modified, but gcc complains if I put const there
void printboard(int width, int height, color board[][width]) { //{{{
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
} //}}}

void delete_row(int width, color board[][width], int row) {
	for (int y = row; y > 0; y--) {
		for (int x = 0; x < width; x++) {
			board[y][x] = board[y - 1][x];
		}
	}
	for (int x = 0; x < width; x++) {
		board[0][x] = EMPTY;
	}
}

void rotate_piece(piece* p) {
	p->rotation++;
	for (int i = 0; i < 4; i++) {
		int x = p->shape[i].x;
		p->shape[i].x = p->shape[i].y;
		p->shape[i].y = x;

		p->shape[i].x = p->bounds - p->shape[i].x;
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

	// I :: Cyan {{{1
	piece p_i = {
		.color = CYAN,
		.bounds = 3,
		.rotation = 0,
		.shape = malloc(sizeof(point) * 4)
	};
	point i_shape[4] = {
		{.x = 0, .y = 1},
		{.x = 1, .y = 1},
		{.x = 2, .y = 1},
		{.x = 3, .y = 1},
	};
	p_i.shape = i_shape;

	// O :: Yellow {{{1
	piece p_o = {
		.color = YELLOW,
		.bounds = 1,
		.rotation = 0,
		.shape = malloc(sizeof(point) * 4)
	};
	point o_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 0, .y = 1},
		{.x = 1, .y = 0},
		{.x = 1, .y = 1},
	};
	p_o.shape = o_shape;

	// T :: Magenta {{{1
	piece p_t = {
		.color = MAGENTA,
		.bounds = 2,
		.rotation = 0,
		.shape = malloc(sizeof(point) * 4)
	};
	point t_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 1, .y = 0},
		{.x = 2, .y = 0},
		{.x = 1, .y = 1},
	};
	p_t.shape = t_shape;
	// S :: Green {{{1
	piece p_s = {
		.color = GREEN,
		.bounds = 2,
		.rotation = 0,
		.shape = malloc(sizeof(point) * 4)
	};
	point s_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 0, .y = 1},
		{.x = 1, .y = 1},
		{.x = 1, .y = 2},
	};
	p_s.shape = s_shape;
	// Z :: Red {{{1
	piece p_z = {
		.color = RED,
		.bounds = 2,
		.rotation = 0,
		.shape = malloc(sizeof(point) * 4)
	};
	point z_shape[4] = {
		{.x = 1, .y = 0},
		{.x = 0, .y = 1},
		{.x = 1, .y = 1},
		{.x = 0, .y = 2},
	};
	p_z.shape = z_shape;
	// J :: Blue {{{1
	piece p_j = {
		.color = BLUE,
		.bounds = 2,
		.rotation = 0,
		.shape = malloc(sizeof(point) * 4)
	};
	point j_shape[4] = {
		{.x = 2, .y = 0},
		{.x = 2, .y = 1},
		{.x = 2, .y = 2},
		{.x = 1, .y = 2},
	};
	p_j.shape = j_shape;
	// L :: Orange {{{1
	piece p_l = {
		.color = ORANGE,
		.bounds = 2,
		.shape = malloc(sizeof(point) * 4)
	};
	point l_shape[4] = {
		{.x = 0, .y = 0},
		{.x = 0, .y = 1},
		{.x = 0, .y = 2},
		{.x = 1, .y = 2},
	};
	p_l.shape = l_shape;

	///}}}1

	const int width = 8;
	const int height = 20;

	// the extra height is for collision at the bottom
	color board[height + 1][width];

	for (int y = 0; y < height; y++)
	for (int x = 0; x < width; x++)
	{
		board[y][x] = EMPTY;
	}

	for (int x = 0; x < width; x++) {
		board[height][x] = 'X';
	}

	char input;
	point pos = {.x = 1, .y = 0};

	// TODO the quickdrop code makes the display
	// behave weird

	// how often the piece should drop, in ticks
	int dropspeed = 10;
	piece pieces[7] = {p_i, p_o, p_t, p_s, p_z, p_j, p_l};
	//piece pieces[7] = {p_o, p_o, p_o, p_o, p_o, p_o, p_o};
	//piece pieces[10] = {p_i, p_i, p_i, p_i, p_i, p_i, p_i, p_i, p_i, p_i};
	piece* piece = pieces;
	bool quickdrop = false;
	for (int loop = 0;; loop++) {
		if (loop % dropspeed == 0) {
			pos.y++;
		}

		if (!quickdrop) {
			input = getchar();

			if (input == 'l') ++pos.x;
			if (input == 'h') --pos.x;
			if (input == ' ') quickdrop = true;
			if (input == 'r') rotate_piece(piece);
		}

		for (int i = 0; i < 4; i++) {
			point p = piece->shape[i];
			board[pos.y + p.y][pos.x + p.x] = piece->color;
		}

		printboard(width, height, board);	
		// 20 ticks per secound
		if (!quickdrop)
			usleep(1000000 / 20);

		bool piece_stoped = false;
		for (int i = 0; i < 4; i++) {
			point p = {
				.x = piece->shape[i].x,
				.y = piece->shape[i].y + 1
			};

			if (board[pos.y+p.y][pos.x+p.x] != EMPTY
					&& !in_piece(p, piece))
				piece_stoped = true;
		}

		if (piece_stoped) {
			// This is kindof a stack
			int rows_removed[4];
			int ptr = 0;

			for (int line = pos.y;
			     line < height && line <= pos.y + piece->bounds;
			     line++)
			{
				int all_filled = true;
				for (int x = 0; x < width; x++) {
					all_filled &= !(board[line][x] == EMPTY);
				}
				if (all_filled) {
					rows_removed[ptr++] = line;
				}
			}

			for (int i = 0; i < ptr; i++) {
				delete_row(width, board, rows_removed[i]);
			}

			pos.x = 0;
			pos.y = 1;
			quickdrop = false;

			// since I reuse the same pieces I need to reset
			// the things on them that change
			while (piece->rotation != 0)
				rotate_piece(piece);

			// next piece
			piece++;

			continue;
		}

		// removes piece
		for (int i = 0; i < 4; i++) {
			point p = piece->shape[i];
			board[pos.y + p.y][pos.x + p.x] = EMPTY;
		}
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
