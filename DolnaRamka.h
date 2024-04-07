#pragma once
#include "SDL.h"
#include <stdio.h>

#define X 0
#define Y 430
#define  Glebia 32
#define Dlugosc 40
#define Szerokosc 120

class DolnaRamka
{
public:
	DolnaRamka(SDL_Renderer* renderer, SDL_Surface* czcionka);
	void render(SDL_Renderer* renderer);
	void czyszczenie();
private:
	SDL_Texture* ramka_tex1;
	SDL_Rect r2;
};