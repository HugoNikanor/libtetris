#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "types.h"

color** _g_board;
bool _g_board_live;

bool in_piece(point p, piece* piece);
void delete_row(int width, color board[][width], int row);
void rotate_piece(piece* p);
void safe_rotate(point* pos, piece* piece, int width, color board[][width]);
void move_right(direction dir, int width, color board[][width], point* pos, piece* piece);
void game_loop();

#endif // GAME_H
