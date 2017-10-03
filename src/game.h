#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "types.h"

bool in_piece(point p, piece* piece);
void delete_row(int width, color board[][width], int row);
void rotate_piece(piece* p);
void setup_pieces();
void setup_game();
void game_loop();

#endif // GAME_H