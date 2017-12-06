#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "types.h"

typedef enum { IDLE, LSHIFT, RSHIFT, ROTATE, QUICKDROP } move;

typedef struct {
	int width;
	int height;
	int dropspeed;
	move (*move_func)(void);
} tetris_settings;


// These are for drawing the board
color** _g_board;
bool _g_board_live;

bool piece_invalid(piece* piece, point pos, int width, color board[][width]);
void reset_board(int width, int height, color board[][width]);
bool in_piece(point p, piece* piece);
void delete_row(int width, color board[][width], int row);
void rotate_piece(piece* p);
void safe_rotate(point* pos, piece* piece, int width, color board[][width]);
void move_piece(direction dir, int width, color board[][width], point* pos, piece* piece);

move move_generator();
move move_manual();
void game_loop(const tetris_settings*);


#endif // GAME_H
