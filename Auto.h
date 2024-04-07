#pragma once
#include "SDL.h"
#include <stdlib.h>

#define Wys_Auta 40
#define Szer_Auta 30
#define Ruch 10

class Auto
{
	public:
		Auto(int x, int y, SDL_Renderer* renderer);
		void lewo();
		void prawo();
		void render(SDL_Renderer* renderer);
		int auto_x();
		int auto_y();
		void respawn(int x, int y);
		void czyszczenie();
		bool kolizja(int x, int y, int szer, int dl);
	private:
		SDL_Texture* auto_tex;
		SDL_Rect  obraz;
};
