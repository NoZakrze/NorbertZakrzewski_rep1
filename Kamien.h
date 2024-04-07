#pragma once
#include "SDL.h"
#include <stdlib.h>

#define Wys_Kamienia 20
#define Szer_Kamienia 30

class Kamien
{
public:
	SDL_Rect  obraz;
	Kamien(int x, int y, SDL_Renderer* renderer);
	void update();
	void render(SDL_Renderer* renderer);
	void czyszczenie();
private:
	SDL_Texture* kamien_tex;
};
