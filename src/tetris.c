#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // usleep
#include <string.h>

#include "tetris.h"

color* _g_board;
bool _g_board_live;

bool piece_invalid(piece* piece, point pos, int width, color board[][width]) {
	for (int i = 0; i < 4; i++) {
		point p = {
			.x = piece->shape[i].x + pos.x,
			.y = piece->shape[i].y + pos.y
		};
		if (board[p.y][p.x] != EMPTY)
			return true;
	}
	return false;
}
void reset_board(int width, int height, color board[][width]) {
	for (int y = 0; y < height; y++)
	for (int x = 0; x < width; x++) {
		board[y][x] = EMPTY;
	}
}

bool in_piece(point p, piece* piece) {
	for (int i = 0; i < 4; i++) {
		point pp = piece->shape[i];
		if (p.x == pp.x && p.y == pp.y)
			return true;
	}
	return false;
}

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

void safe_rotate(point* pos, piece* piece, int width, color board[][width]) {
	bool problems = false;
	rotate_piece(piece);
	for (int i = 0; i < 4; i++) {
		point p = {
			.x = pos->x + piece->shape[i].x,
			.y = pos->y + piece->shape[i].y
		};

		if (p.x < 0 || p.x >= width || board[p.y][p.x] != EMPTY) {
			problems = true;
			break;
		}
	}
	if (problems) {
		rotate_piece(piece);
		rotate_piece(piece);
		rotate_piece(piece);
	}
}

void move_piece(direction dir,
		int width,
		color board[][width],
		point* pos,
		piece* piece) {

	int d;
	if (dir == LEFT)
		d = -1;
	else
		d = 1;


	bool ok = true;
	for (int i = 0; i < 4; i++) {
		point p = {
			.x = piece->shape[i].x + pos->x + d,
			.y = piece->shape[i].y + pos->y
		};

		if (p.x < 0
				|| p.x >= width
				|| (board[p.y][p.x] != EMPTY && !in_piece(p, piece))) {
			ok = false;
			break;
		}
	}

	if (ok)
		pos->x += d;

}

move move_generator() {
	move moves[5] = { RSHIFT, RSHIFT, LSHIFT, LSHIFT, ROTATE };
	if (random() % 10 == 0) {
		return moves[random() % 5];
	} else return IDLE;
}

move move_manual() {
	switch (getchar()) {
		case 'h': return LSHIFT;
		case 'l': return RSHIFT;
		case 'r': return ROTATE;
		case ' ': return QUICKDROP;
		default:  return IDLE;
	}
}

void game_loop(const tetris_settings* settings) {
	int width = settings->width;
	int height = settings->height;
	int dropspeed = settings->dropspeed;

	// board setup {{{1

	// the extra height is for collision at the bottom
	//color board[height + 1][width];
	_g_board = malloc((height + 1) * width * sizeof(color));

	_g_board_live = true;

	//color board[height+1][width];
	color (*board)[width] = (color (*)[width]) _g_board;

	for (int y = 0; y < height; y++)
	for (int x = 0; x < width; x++)
	{
		board[y][x] = EMPTY;
	}

	for (int x = 0; x < width; x++) {
		board[height][x] = 'X';
	}

	// I :: Cyan {{{1
	piece p_i = {
		.color = CYAN,
		.bounds = 3,
		.rotation = 0,
		.shape = {
			{.x = 0, .y = 1},
			{.x = 1, .y = 1},
			{.x = 2, .y = 1},
			{.x = 3, .y = 1},
		}
	};

	// O :: Yellow {{{1
	piece p_o = {
		.color = YELLOW,
		.bounds = 1,
		.rotation = 0,
		.shape = {
			{.x = 0, .y = 0},
			{.x = 0, .y = 1},
			{.x = 1, .y = 0},
			{.x = 1, .y = 1},
		}
	};

	// T :: Magenta {{{1
	piece p_t = {
		.color = MAGENTA,
		.bounds = 2,
		.rotation = 0,
		.shape = {
			{.x = 0, .y = 0},
			{.x = 1, .y = 0},
			{.x = 2, .y = 0},
			{.x = 1, .y = 1},
		}
	};

	// S :: Green {{{1
	piece p_s = {
		.color = GREEN,
		.bounds = 2,
		.rotation = 0,
		.shape = {
			{.x = 0, .y = 0},
			{.x = 0, .y = 1},
			{.x = 1, .y = 1},
			{.x = 1, .y = 2},
		}
	};

	// Z :: Red {{{1
	piece p_z = {
		.color = RED,
		.bounds = 2,
		.rotation = 0,
		.shape = {
			{.x = 1, .y = 0},
			{.x = 0, .y = 1},
			{.x = 1, .y = 1},
			{.x = 0, .y = 2},
		}
	};

	// J :: Blue {{{1
	piece p_j = {
		.color = BLUE,
		.bounds = 2,
		.rotation = 0,
		.shape = {
			{.x = 2, .y = 0},
			{.x = 2, .y = 1},
			{.x = 2, .y = 2},
			{.x = 1, .y = 2},
		}
	};

	// L :: Orange {{{1
	piece p_l = {
		.color = ORANGE,
		.bounds = 2,
		.shape = {
			{.x = 0, .y = 0},
			{.x = 0, .y = 1},
			{.x = 0, .y = 2},
			{.x = 1, .y = 2},
		}
	};


	///}}}1

	move move;
	point pos = {.x = 1, .y = 0};

	// quickdrop disables board printing and sleeping
	// in the game loop
	bool quickdrop = false;

	piece pieces[7] = {p_i, p_o, p_t, p_s, p_z, p_j, p_l};
	//piece pieces[7] = {p_o, p_o, p_o, p_o, p_o, p_o, p_o};
	//piece pieces[10] = {p_i, p_i, p_i, p_i, p_i, p_i, p_i, p_i, p_i, p_i};
	piece* piece = pieces;
	for (int loop = 0;; loop++) {
		if (loop % dropspeed == 0) {
			pos.y++;
		}

		//input = getchar();
		move = settings->move_func();

		if (move == RSHIFT)    move_piece(RIGHT, width, board, &pos, piece);
		if (move == LSHIFT)    move_piece(LEFT,  width, board, &pos, piece);
		if (move == ROTATE)    safe_rotate(&pos, piece, width, board);
		if (move == QUICKDROP) quickdrop = true;




		for (int i = 0; i < 4; i++) {
			point p = piece->shape[i];
			board[pos.y + p.y][pos.x + p.x] = piece->color;
		}

		if (!quickdrop) {
			//printboard(width, height, board);

			// 20 ticks per secound
			usleep(1000000 / 50);
		}

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

			// this is needed since quickdrop disables
			// regular board printing
			if (quickdrop) {
				//printboard(width, height, board);
				quickdrop = false;
			}

			pos.x = 0;
			pos.y = 1;

			// since I reuse the same pieces I need to reset
			// the things on them that change
			while (piece->rotation != 0)
				rotate_piece(piece);

			// next piece
			//piece++;
			piece = &pieces[random() % 7];
			if (piece_invalid(piece, pos, width, board)) {
				reset_board(width, height, board);
			}

			continue;
		}

		// removes piece
		for (int i = 0; i < 4; i++) {
			point p = piece->shape[i];
			board[pos.y + p.y][pos.x + p.x] = EMPTY;
		}
	}
}
