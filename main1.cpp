#include "SDL.h"
#include <stdio.h>
#include "Gra.h"
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	bool end = 0;
	bool* wsk_end = &end;
	while (!end)
	{
		Gra* gra = new Gra("Norbert Zakrzewski 193391", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Szerokosc_Ekranu, Dlugosc_Ekranu);
		while (!(gra->koniec) && !(gra->nowa))
		{
			gra->obsluga_klawiszy(*wsk_end);
			gra->czas();
			gra->kolizja();
			gra->wybuch(*wsk_end);
			gra->wynik();
			gra->update();
			gra->render();
			gra->szybkosc();
			gra->resp();
		}
		if (gra->zapis_koniec)
		{
			gra->ekran();
			while (!(gra->koniec2))
			{
				gra->klawisze_koniec();
				gra->render_koniec();
			}
			gra->zapisywanie();
			gra->czyszczenie_koniec();
		}
		gra->czyszczenie();
		delete gra;
	}
	SDL_Quit();
	return 0;
}