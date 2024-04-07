#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "DolnaRamka.h"
#include "Gra.h"
#include <stdio.h>
#include "functions.h"

DolnaRamka::DolnaRamka(SDL_Renderer* renderer, SDL_Surface* czcionka)
{
	SDL_Surface* ramka1;
	ramka1 = SDL_CreateRGBSurface(0,Szerokosc, Dlugosc, Glebia,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	int czarny = SDL_MapRGB(ramka1->format, 0x00, 0x00, 0x00);
	int czerwony = SDL_MapRGB(ramka1->format, 0xFF, 0x00, 0x00);
	DrawRectangle(ramka1, 0, 0, Szerokosc, Dlugosc, czerwony, czarny);
	DrawString(ramka1, 10, 10, "podstawowe,", czcionka);
	DrawString(ramka1, 10, 20, "h,i,m,o", czcionka);
	ramka_tex1 = SDL_CreateTextureFromSurface(renderer, ramka1);
	SDL_FreeSurface(ramka1);
	r2.x = Szerokosc_Ekranu - Szerokosc;
	r2.y = Dlugosc_Ekranu - Dlugosc;
	r2.h = Dlugosc;
	r2.w = Szerokosc;
}
void DolnaRamka::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, ramka_tex1, NULL, &r2);
}
void DolnaRamka::czyszczenie()
{
	SDL_DestroyTexture(ramka_tex1);
}