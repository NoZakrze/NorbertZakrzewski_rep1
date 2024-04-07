#pragma once
#include "SDL.h"
#include <stdio.h>

#define Poczatek_Ekranu 0
#define Pomin 0
#define Wyswietl 8
#define Napis_X 10
#define Napis_Y 10
#define Lista_Y 20
#define Odstep 10

class Lista
{
public:
	Lista(SDL_Renderer* renderer, SDL_Surface* czcionka, int sort);
	void update(SDL_Renderer* renderer, SDL_Surface* czcionka);
	void render(SDL_Renderer* renderer);
	void czyszczenie();
	int skip, limit, ilosc_linii;
private:
	SDL_Texture* lista_tex;
	SDL_Surface* ramka;
	int czarny, czerwony;
	double** tab;
	bool p;
};