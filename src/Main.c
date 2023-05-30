#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *win;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(600, 400, 0, win, renderer);

	// Delay for testing (the window should show up, but be frozen, for 2.5 seconds).
	SDL_Delay(2500);

	SDL_Quit();
	return 0;
}
