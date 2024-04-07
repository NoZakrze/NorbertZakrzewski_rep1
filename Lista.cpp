#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "Lista.h"
#include "Gra.h"
#include <stdio.h>
#include "functions.h"

Lista::Lista(SDL_Renderer* renderer, SDL_Surface* czcionka, int sort)
{
	p = 0;
	skip = Pomin;
	limit = Wyswietl;
	ramka = SDL_CreateRGBSurface(0, Szerokosc_Ekranu, Dlugosc_Ekranu, Glebia,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	czarny = SDL_MapRGB(ramka->format, 0x00, 0x00, 0x00);
	czerwony = SDL_MapRGB(ramka->format, 0xFF, 0x00, 0x00);
	char tekst[Bufor];
	sprintf(tekst, "Miejsce    Wynik:     Czas:");
	DrawRectangle(ramka, Poczatek_Ekranu, Poczatek_Ekranu, Szerokosc_Ekranu, Dlugosc_Ekranu, czerwony, czarny);
	DrawString(ramka, Napis_X, Napis_Y, tekst, czcionka);
	FILE* plik = fopen("wyniki.txt", "r");
	ilosc_linii = 0;
	char znak;
	if (plik)
	{
		p = 1;
		while ((znak = getc(plik)) != EOF)
		{
			if (znak == '\n')
				++ilosc_linii;
		}
		fclose(plik);
		tab = new double* [ilosc_linii];
		for (int i = 0; i < ilosc_linii; i++)\
		{
			tab[i] = new double[2];
		}
		FILE* plik1 = fopen("wyniki.txt", "r");
		for (int i = 0; i < ilosc_linii; i++)
		{
			fscanf(plik1, "%lf %lf", &tab[i][0], &tab[i][1]);
		}
		fclose(plik1);

		for (int i = 0; i < ilosc_linii; i++)
		{
			for (int j = 1; j < ilosc_linii - i; j++)
			{
				if (tab[j - 1][sort] < tab[j][sort])
				{
					double b = tab[j - 1][0];
					tab[j - 1][0] = tab[j][0];
					tab[j][0] = b;
					b = tab[j - 1][1];
					tab[j - 1][1] = tab[j][1];
					tab[j][1] = b;
				}
			}
		}
		int i;
		if (ilosc_linii <= limit)
		{
			i = 0;
		}
		else
		{
			i = skip;
		}
		int y = Lista_Y;
		for (; i < limit + skip && i < ilosc_linii; i++, y += Odstep)
		{
			char t[Bufor];
			sprintf(t, "%d          %.0lf        %.0lf", i + 1, tab[i][0], tab[i][1]);
			DrawString(ramka, Napis_X, y, t, czcionka);
		}
		lista_tex = SDL_CreateTextureFromSurface(renderer, ramka);
	}
}
void Lista::update(SDL_Renderer* renderer, SDL_Surface* czcionka)
{
	if (p == 1)
	{
		SDL_FillRect(ramka, NULL, czarny);
		char tekst[Bufor];
		sprintf(tekst, "Miejsce    Wynik:     Czas:");
		DrawRectangle(ramka, 0, 0, Szerokosc_Ekranu, Dlugosc_Ekranu, czerwony, czarny);
		DrawString(ramka, Napis_X, Napis_Y, tekst, czcionka);
		int i;
		if (ilosc_linii <= limit)
		{
			i = 0;
		}
		else
		{
			i = skip;
		}
		int y = Lista_Y;
		for (; i < limit + skip && i < ilosc_linii; i++, y += Odstep)
		{
			char t[Bufor];
			sprintf(t, "%d          %.0lf        %.0lf", i + 1, tab[i][0], tab[i][1]);
			DrawString(ramka, Napis_X, y, t, czcionka);
		}
		SDL_UpdateTexture(lista_tex, NULL, ramka->pixels, ramka->pitch);
	}
}
void Lista::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, lista_tex, NULL, NULL);
}
void Lista::czyszczenie()
{
	SDL_DestroyTexture(lista_tex);
	SDL_FreeSurface(ramka);
	for (int i = 0; i < ilosc_linii; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;
}