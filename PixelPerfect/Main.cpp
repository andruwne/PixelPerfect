#include "include.h"

#define LANGUAGE CPP

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;
const int FLAGS = SDL_WINDOW_SHOWN;

void print_header(const char* header);
void pixel_test();
int start(int argc, char* argv[]);

int start(int argc, char* argv[]) {
	int width = 0;
	int height = 0;
	int bpp = 0;
	int flags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Video initialization failed: %s\n",
			SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window* win = SDL_CreateWindow("PixelPerfect", 100, 100, WIDTH, HEIGHT, flags);
	if (win == nullptr) {
		fprintf(stderr, "Video mode set failed: %s\n",
			SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::string imagePath = "image.bmp";
	SDL_Surface* bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 3; ++i) {
		//First clear the renderer
		SDL_RenderClear(ren);
		//Draw the texture
		SDL_RenderCopy(ren, tex, NULL, NULL);
		//Update the screen
		SDL_RenderPresent(ren);
		//Take a quick break after all that hard work
		SDL_Delay(1000);
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

void print_header(const char* header) {
	std::cout << "\n" << header << std::endl;
}

void pixel_test() {
	pixel p1;
	p1.init(0, 0, 0, 255);
	print_header("INIT");
	printf("red: %u\n", p1.r);
	printf("green: %u\n", p1.g);
	printf("blue: %u\n", p1.b);
	printf("alpha: %u\n", p1.a);

	pixel p2;
	p2.init(0, 0, 0, 255);
	p2.set(0xFF0000FF);
	print_header("SET RED");
	printf("red: %u\n", p2.r);
	printf("green: %u\n", p2.g);
	printf("blue: %u\n", p2.b);
	printf("alpha: %u\n", p2.a);

	BYTE* byte_arr = p1.pack();
	print_header("PACKED");
	printf("red: %u\n", byte_arr[2]);
	printf("green: %u\n", byte_arr[1]);
	printf("blue: %u\n", byte_arr[0]);
	printf("alpha: %u\n", byte_arr[3]);

	print_header("SHIFT");
	int hex_value = 0xFFFFFF;
	printf("%d >> 8 = %d", hex_value, hex_value >> 8);
}