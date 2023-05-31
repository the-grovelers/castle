#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_TITLE "Hello World!"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_FULLSCREEN 0
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 96

void load_img(const char * image_path);

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Texture* screenTexture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RaiseWindow(window);

    SDL_Surface *image = SDL_LoadBMP("src/test.bmp");

    	/* Let the user know if the file failed to load */
    	if (!image) {
    	    printf("Failed to load image at %s: %s\n", "src/test.bmp", SDL_GetError());
    	}else{
    		printf("Loaded image");
    	}
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void load_img(const char * image_path){
	SDL_Surface *image = SDL_LoadBMP(image_path);

	/* Let the user know if the file failed to load */
	if (!image) {
	    printf("Failed to load image at %s: %s\n", image_path, SDL_GetError());
	}else{
		printf("Loaded image");
	}

	/* Do something with image here. */

	/* Make sure to eventually release the surface resource */
	SDL_FreeSurface(image);
}
