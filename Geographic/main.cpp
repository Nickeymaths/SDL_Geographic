#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#undef main

const int ScreenWidth = 640;
const int ScreenHeight = 480;

SDL_Window* gwindow = nullptr;
SDL_Renderer* gscreen = nullptr;

bool init();
void close();
SDL_Texture* loadTexture(const std::string& path);

int main() {
	int control = 1;
	bool quit = false;
	SDL_Event e;
	if (init()) {
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}
			SDL_SetRenderDrawColor(gscreen, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gscreen);

			SDL_SetRenderDrawColor(gscreen, 0xFF, 0x00, 0x00, 0xFF);
			SDL_Rect fillRect = {
				ScreenWidth/4,
				ScreenHeight/4,
				ScreenWidth/2,
				ScreenHeight/2
			};
			SDL_RenderFillRect(gscreen, &fillRect);
			SDL_SetRenderDrawColor(gscreen, 0x00, 0xFF, 0x00, 0xFF);
			SDL_Rect outline = {
				ScreenWidth / 6,
				ScreenHeight / 6,
				ScreenWidth * 2 / 3,
				ScreenHeight * 2 / 3
			};
			SDL_RenderDrawRect(gscreen, &outline);
			SDL_SetRenderDrawColor(gscreen, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawLine(gscreen, 0, ScreenHeight / 2, ScreenWidth, ScreenHeight / 2);
			SDL_SetRenderDrawColor(gscreen, 0xFF, 0xFF, 0x00, 0xFF);
			for (int i = 0; i < ScreenHeight; i += 4) {
				SDL_RenderDrawPoint(gscreen, ScreenWidth / 2, i);
			}
			/*
			SDL_Rect viewport;
			control %= 4;
			if (control == 1) {
				viewport.x = 0;
				viewport.y = 0;
				viewport.w = ScreenWidth / 2;
				viewport.h = ScreenHeight / 2;
				SDL_RenderSetViewport(gscreen, &viewport);
				control++;
			}
			else if (control == 2) {
				viewport.x = ScreenWidth / 2;
				viewport.y = 0;
				viewport.w = ScreenWidth / 2;
				viewport.h = ScreenHeight / 2;
				SDL_RenderSetViewport(gscreen, &viewport);
				control++;
			}

			else if (control == 3) {
				viewport.x = 0;
				viewport.y = ScreenHeight / 2;
				viewport.w = ScreenWidth / 2;
				viewport.h = ScreenHeight / 2;
				SDL_RenderSetViewport(gscreen, &viewport);
				control++;
			}

			else {
				viewport.x = ScreenWidth / 2;
				viewport.y = ScreenHeight / 2;
				viewport.w = ScreenWidth / 2;
				viewport.h = ScreenHeight / 2;
				SDL_RenderSetViewport(gscreen, &viewport);
				control++;
			}*/
			SDL_RenderPresent(gscreen);
		}
	}
	return 0;
}

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error init vieo" << std::endl;
		success = false;
	}
	else {
		gwindow = SDL_CreateWindow("Pham Thanh Vinh",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
		if (gwindow == nullptr) {
			std::cerr << "Error create window" << std::endl;
			success = false;
		}
		else {
			gscreen = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
			if (gscreen == nullptr) {
				std::cerr << "Error create Render" << std::endl;
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gscreen, 0xFF, 0xFF, 0xFF, 0xFF);
				if (!IMG_Init(IMG_INIT_PNG)) {
					std::cerr << "Error init IMG PNG" << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}

SDL_Texture* loadTexture(const std::string& path) {
	SDL_Texture* loadTexture = nullptr;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == nullptr) {
		std::cerr << "Error load Surface Image" << std::endl;
	}
	else {
		loadTexture = SDL_CreateTextureFromSurface(gscreen, loadSurface);
		if (loadTexture == nullptr) {
			std::cerr << "Error load Texture" << std::endl;
		}
	}
	return loadTexture;
}

void close() {
	SDL_DestroyRenderer(gscreen);
	gscreen = nullptr;
	SDL_DestroyWindow(gwindow);
	gwindow = nullptr;
	IMG_Quit();
	SDL_Quit();
}