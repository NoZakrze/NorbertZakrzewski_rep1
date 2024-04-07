#pragma once
#include "SDL.h"
#include <stdio.h>

#define Dlugosc_Ramki 70
#define Glebia 32
#define Napisy_x 20
#define Czas_y 5
#define Wynik_y 20
#define Opis_y 35
#define Bufor 256
#define Poczatek_Obrazka 0

class Ramka
{
	public:
		Ramka(SDL_Renderer* renderer, SDL_Surface* czcionka);
		void render(SDL_Renderer* renderer);
		void update(SDL_Renderer* renderer, SDL_Surface* czcionka);
		void czyszczenie();
		double timer, wynik, niesm;
		int zycia;
	private:
		SDL_Texture* ramka_tex;
		SDL_Surface* ramka;
		SDL_Rect r;
		char text[Bufor], text2[Bufor], text3[Bufor];
		int czarny, czerwony;
};
