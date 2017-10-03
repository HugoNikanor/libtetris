#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "types.h"

bool in_piece(point p, piece* piece);
void delete_row(int width, color board[][width], int row);
void rotate_piece(piece* p);
void move_right(point* pos, piece* piece);
void game_loop();

#endif // GAME_H
