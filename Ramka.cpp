#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "Ramka.h"
#include "Gra.h"
#include <stdio.h>
#include "functions.h"

Ramka::Ramka(SDL_Renderer* renderer, SDL_Surface* czcionka)
{
	ramka = SDL_CreateRGBSurface(0, Szerokosc_Ekranu, Dlugosc_Ramki, Glebia,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	czarny = SDL_MapRGB(ramka->format, 0x00, 0x00, 0x00);
	czerwony = SDL_MapRGB(ramka->format, 0xFF, 0x00, 0x00);
	DrawRectangle(ramka, Poczatek_Obrazka, Poczatek_Obrazka, Szerokosc_Ekranu, Dlugosc_Ramki, czerwony, czarny);
	timer = timer * Mili;
	niesm = niesm * Mili;
	sprintf(text, "Czas gry: %.0lf s   Niesmiertelnosc: %.0lf s", timer, niesm);
	DrawString(ramka, Napisy_x, Czas_y, text, czcionka);
	if (niesm > 0)
	{
		sprintf(text2, "Wynik: %.0lf    Auta: nieograniczone", wynik);
	}
	else
	{
		sprintf(text2, "Wynik: %.0lf    Auta: %d", wynik, zycia);
	}
	DrawString(ramka, Napisy_x, Wynik_y, text2, czcionka);
	sprintf(text3, "Esc - koniec gry, n - nowa gra, strzalki - sterowanie, f - koniec");
	DrawString(ramka, Napisy_x, Opis_y, text3, czcionka);
	DrawString(ramka, Napisy_x, Opis_y+15, "l - lista wynikow (punkty)  t - lista wynikow (czas)", czcionka);
	ramka_tex = SDL_CreateTextureFromSurface(renderer, ramka);
	r.x = Poczatek_Obrazka;
	r.y = Poczatek_Obrazka;
	r.h = Dlugosc_Ramki;
	r.w = Szerokosc_Ekranu;
}
void Ramka::update(SDL_Renderer* renderer, SDL_Surface* czcionka)
{
	SDL_FillRect(ramka, NULL, czarny);
	DrawRectangle(ramka, Poczatek_Obrazka, Poczatek_Obrazka, Szerokosc_Ekranu, Dlugosc_Ramki, czerwony, czarny);
	timer = timer * Mili;
	niesm = niesm * Mili;
	sprintf(text, "Czas gry: %.0lf s   Niesmiertelnosc: %.0lf s", timer, niesm);
	DrawString(ramka, Napisy_x, Czas_y, text, czcionka);
	if (niesm > 0)
	{
		sprintf(text2, "Wynik: %.0lf    Auta: nieograniczone", wynik);
	}
	else
	{
		sprintf(text2, "Wynik: %.0lf    Auta: %d", wynik, zycia);
	}
	DrawString(ramka, Napisy_x, Wynik_y, text2, czcionka);
	sprintf(text3, "Esc - koniec gry, n - nowa gra, strzalki - sterowanie, f - koniec");
	DrawString(ramka, Napisy_x, Opis_y, text3, czcionka);
	DrawString(ramka, Napisy_x, Opis_y + 15, "l - lista wynikow (punkty)  t - lista wynikow (czas)", czcionka);
	SDL_UpdateTexture(ramka_tex, NULL, ramka->pixels, ramka->pitch);
}
void Ramka::render(SDL_Renderer* renderer)
{	
	SDL_RenderCopy(renderer, ramka_tex, NULL,&r);
}
void Ramka::czyszczenie()
{
	SDL_DestroyTexture(ramka_tex);
	SDL_FreeSurface(ramka);
}