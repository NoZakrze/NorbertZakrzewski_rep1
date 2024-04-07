#pragma once
#include "SDL.h"
#include <stdio.h>

#define Poczatek_Ekranu 0
#define Napisy_X 10
#define Napisy_Y 10

class EkranKonca
{
public:
	EkranKonca(SDL_Renderer* renderer, SDL_Surface* czcionka, double timer, double wynik);
	void render(SDL_Renderer* renderer);
	void czyszczenie();
private:
	SDL_Texture* ekran_tex;
};
