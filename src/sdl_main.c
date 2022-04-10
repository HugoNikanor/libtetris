#include <pthread.h>

#include <SDL.h>

#include "tetris.h"

int board_width = 10;
int board_height = 20;

int tile_side = 10;

void* run_tetris(void* data) {
	tetris_settings settings = {
		.width = board_width,
		.height = board_height,
		.dropspeed = 60,
		.move_func = &move_generator
	};
	game_loop(&settings);
	return NULL;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, run_tetris, NULL);

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Hello World", 0, 0, board_width * tile_side, board_height * tile_side, 0);
	SDL_Renderer* rend = SDL_CreateRenderer(window, -1, 0);

	color (*board)[board_width] = (color (*)[board_width]) _g_board;


	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		SDL_RenderClear(rend);

		SDL_Rect rect = {
			.w = tile_side,
			.h = tile_side,
		};
		for (int y = 0; y < board_height; y++) {
			for (int x = 0; x < board_width; x++) {
				rect.x = x * tile_side;
				rect.y = y * tile_side;
				switch(board[y][x]) {
					case EMPTY:    SDL_SetRenderDrawColor(rend , 0    , 0    , 0    , 0xFF); break;
					case GREEN:    SDL_SetRenderDrawColor(rend , 0    , 0xFF , 0    , 0xFF); break;
					case RED:      SDL_SetRenderDrawColor(rend , 0xFF , 0    , 0    , 0xFF); break;
					case ORANGE:   SDL_SetRenderDrawColor(rend , 0xFF , 0xA5 , 0    , 0xFF); break;
					case YELLOW:   SDL_SetRenderDrawColor(rend , 0xFF , 0xFF , 0    , 0xFF); break;
					case BLUE:     SDL_SetRenderDrawColor(rend , 0    , 0    , 0xFF , 0xFF); break;
					case MAGENTA:  SDL_SetRenderDrawColor(rend , 0xFF , 0    , 0xFF , 0xFF); break;
					case CYAN:     SDL_SetRenderDrawColor(rend , 0    , 0xFF , 0xFF , 0xFF); break;
				}
				SDL_RenderFillRect(rend, &rect);
			}
		}

		SDL_RenderPresent(rend);
	}

	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
