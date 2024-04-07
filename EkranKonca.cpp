#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "EkranKonca.h"
#include "Gra.h"
#include <stdio.h>
#include "functions.h"

EkranKonca::EkranKonca(SDL_Renderer* renderer, SDL_Surface* czcionka, double timer, double wynik)
{
	SDL_Surface* ramka2;
	ramka2 = SDL_CreateRGBSurface(0, Szerokosc_Ekranu, Dlugosc_Ekranu, Glebia,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	int czarny = SDL_MapRGB(ramka2->format, 0x00, 0x00, 0x00);
	int czerwony = SDL_MapRGB(ramka2->format, 0xFF, 0x00, 0x00);
	char tekst[Bufor];
	timer = timer * Mili;
	sprintf(tekst, "Czas gry: %.0lf s   Wynik: %.0lf", timer, wynik);
	DrawString(ramka2, Napisy_X, Napisy_Y, "Koniec gry", czcionka);
	DrawString(ramka2, Napisy_X, Napisy_Y+10, tekst, czcionka);
	DrawString(ramka2, Napisy_X, Napisy_Y+20, "Czy chcesz zapisac wynik?", czcionka);
	DrawString(ramka2, Napisy_X, Napisy_Y+30, "1) Tak    2) Nie", czcionka);
	ekran_tex = SDL_CreateTextureFromSurface(renderer, ramka2);
	SDL_FreeSurface(ramka2);
}
void EkranKonca::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer,ekran_tex, NULL, NULL);
}
void EkranKonca::czyszczenie()
{
	SDL_DestroyTexture(ekran_tex);
}