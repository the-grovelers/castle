#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_TITLE "Hello World!"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_FULLSCREEN 0
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 96

typedef struct point {
	int y;
	int x;
} point;

typedef struct entity {
	point pos;
} entity;

struct InitializationResults {
	SDL_Window *window;
	SDL_Renderer *renderer;
};

struct InitializationResults init_sdl();

int main(int argc, char *argv[]) {
	//Placeholder variables
	int c = 0;

	//Initializing SDL
	SDL_Window *window;
	SDL_Renderer *renderer;

	struct InitializationResults results = init_sdl();

	window = results.window;
	renderer = results.renderer;

	printf("%p", window);

	SDL_RaiseWindow(window);

	//Main loop
	int running = 1;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_WINDOWEVENT:
				//DRAW GAME ON ANY WINDOW EVENT
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_w:
					printf("%d\n", ++c);
					break;
				case SDLK_s:
					printf("%d\n", --c);
					break;
				}
				break;
			case SDL_QUIT:
				running = 0;
				break;
			}
		}
	}

	//Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

struct InitializationResults init_sdl() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	struct InitializationResults res;

	res.window = SDL_CreateWindow(WINDOW_TITLE,
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	WINDOW_WIDTH, WINDOW_HEIGHT,
	WINDOW_FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	if (res.window == NULL) {
		fprintf(stderr, "Window couldn't be created\n");
		exit(1);
	}

	res.renderer = SDL_CreateRenderer(res.window, -1,
			SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
					| SDL_RENDERER_TARGETTEXTURE);
	if (res.renderer == NULL) {
		fprintf(stderr, "Renderer couldn't be created\n");
		exit(1);
	}

	SDL_RenderSetLogicalSize(res.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	return res;
}
