#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "Gra.h"
#include "Auto.h"
#include "Ramka.h"
#include "Kamien.h"
#include "DolnaRamka.h"
#include "lista.h"
#include <stdio.h>


Gra::Gra(const char tytul[], int wsp_X, int wsp_Y, int szer, int dl)
{
	window = SDL_CreateWindow(tytul, wsp_X, wsp_Y, szer, dl,Flags);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, Alpha);
	koniec = false;
	SDL_Surface* mapa = SDL_LoadBMP("./mapa.bmp");
	if (mapa == NULL)
	{
		koniec = true;
	}
	czcionka = SDL_LoadBMP("./czcionka.bmp");
	if (mapa == NULL)
	{
		koniec = true;
	}
	tex_mapa = SDL_CreateTextureFromSurface(renderer, mapa);
	SDL_FreeSurface(mapa);
	kamera.x = Poczatek_Obrazka;
	kamera.y = Dlugosc_Obrazka;
	kamera.w = Szerokosc_Ekranu;
	kamera.h = Dlugosc_Ekranu;
	samochod = new Auto((Szerokosc_Ekranu-Szer_Auta)/2, Dlugosc_Ekranu-(Wys_Auta*2), renderer);
	d_ramka = new DolnaRamka(renderer, czcionka);
	kamien2 = new Kamien(Kamien_X, Poczatek_Obrazka, renderer);
	lista_p = new Lista(renderer,czcionka,Sortuj_P-1);
	lista_t = new Lista(renderer, czcionka,Sortuj_T-1);
	pr = Pod_Opoznienie;
	pr = Pod_Opoznienie;
	czas_1 = SDL_GetTicks();
	timer = w = zniszczenie = czas_wybuchu = czas_respu = nowa = pauza = czas_potrzebny = koniec2 = zapis = dodawanie_zyc = sortuj = 0;
	licz_punkty = zycia = zapis_koniec = 1;
	niesm = Odliczanie;
	ramka = new Ramka(renderer,czcionka);
}
void Gra::obsluga_klawiszy(bool &wsk)
{
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				koniec = true;
				zakonczenie(wsk);
				zapis_koniec = 0;
			}
			else if (event.key.keysym.sym == SDLK_p)
			{
				if (pauza == 1)
					pauza = 0;
				else if (pauza == 0)
					pauza = 1;
			}
			else if (event.key.keysym.sym == SDLK_f)
			{
				koniec = true;
				zakonczenie(wsk);
			}
			else if (event.key.keysym.sym == SDLK_UP && zniszczenie == 0 && pauza == 0 && sortuj == 0)
			{
				pr = Mniejsze_Opoznienie;
			}
			else if (event.key.keysym.sym == SDLK_UP && zniszczenie == 0 && sortuj == Sortuj_P)
			{
				int skip = lista_p->skip;
				if (skip > 0)
					lista_p->skip -= 1;
			}
			else if (event.key.keysym.sym == SDLK_UP && zniszczenie == 0 && sortuj == Sortuj_T)
			{
				int skip = lista_t->skip;
				if (skip > 0)
					lista_t->skip -= 1;
			}
			else if (event.key.keysym.sym == SDLK_DOWN && zniszczenie == 0 && pauza == 0 && sortuj== 0)
			{
				pr = Wieksze_Opoznienie;
			}
			else if (event.key.keysym.sym == SDLK_DOWN && zniszczenie == 0 && sortuj == Sortuj_P)
			{
				int skip = lista_p->skip;
				if (skip < lista_p->ilosc_linii-lista_p->limit)
					lista_p->skip += 1;
			}
			else if (event.key.keysym.sym == SDLK_DOWN && zniszczenie == 0 && sortuj == Sortuj_T)
			{
				int skip = lista_t->skip;
				if (skip < lista_t->ilosc_linii- lista_t->limit)
					lista_t->skip += 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT && pauza == 0)
			{
				samochod->prawo();
			}
			else if (event.key.keysym.sym == SDLK_LEFT && pauza == 0)
			{
				samochod->lewo();
			}
			else if (event.key.keysym.sym == SDLK_n)
			{
				nowa = 1;
			}
			else if (event.key.keysym.sym == SDLK_t)
			{
				if (!sortuj)
				{
					sortuj = Sortuj_T;
				}
				else
					sortuj = 0;
			}
			else if (event.key.keysym.sym == SDLK_l)
			{
				if (!sortuj)
				{
					sortuj = Sortuj_P;
				}
				else
					sortuj = 0;
			}
			break;
		case SDL_KEYUP:
			pr = Pod_Opoznienie;
			break;
		case SDL_QUIT:
			koniec = true;
			zakonczenie(wsk);
			zapis_koniec = 0;
			break;
		};
	};

}
void Gra::czas()
{
	czas_2 = SDL_GetTicks();
	if (pauza == 0)
	{
		timer = timer + (czas_2 - czas_1);
		niesm = niesm - (czas_2 - czas_1);
	}
	if (niesm < 0)
		niesm = 0;
	czas_1 = czas_2;
	
}
void Gra::wynik()
{
	if (licz_punkty == 1 && zniszczenie == 0 && pauza == 0)
	{
		w += (Punkty / pr) * Mili;
		dodawanie_zyc += (Punkty / pr) * Mili;
		if (dodawanie_zyc >= Nowe_Zycie)
		{
			zycia++;
			dodawanie_zyc = 0;
		}
	}
}
void Gra::update()
{
	if (pauza == 0)
	{
		ramka->zycia = zycia;
		ramka->wynik = w;
		ramka->timer = timer;
		ramka->niesm = niesm;
		ramka->update(renderer,czcionka);
		kamera.y--;
		if (kamera.y < 0)
			kamera.y = Dlugosc_Obrazka - 1;
		int pozycja = kamera.y + samochod->auto_y();
		if (pozycja <= Mapa1 || pozycja>Mapa4)
		{
			pobocze = Pobocze1;
		}
		else if ((pozycja <= Mapa2 && pozycja > Mapa1) || (pozycja <= Mapa4 && pozycja > Mapa3))
		{
			pobocze = Pobocze2;
		}
		else if (pozycja <= Mapa3 && pozycja > Mapa2)
		{
			pobocze = Pobocze3;
		}
		kamien2->update();
	}
	if (sortuj == Sortuj_P)
	{
		lista_p->update(renderer, czcionka);
	}
	if (sortuj == Sortuj_T)
	{
		lista_t->update(renderer, czcionka);
	}
}
void Gra::kolizja()
{
	int poz = samochod->auto_x();
	if (poz<pobocze || poz>Szerokosc_Ekranu - pobocze - Szer_Auta)
	{
		licz_punkty = false;
	}
	else
	{
		licz_punkty = true;
	}
}
void Gra::wybuch(bool& wsk)
{
	int poz = samochod->auto_x();
	bool temp = zniszczenie;
	if (zniszczenie == false)
	{
		if (poz<pobocze - (Szer_Auta / 2) || poz>Szerokosc_Ekranu - pobocze - (Szer_Auta / 2))
		{
			zniszczenie = true;
		}
		if (samochod->kolizja(kamien2->obraz.x, kamien2->obraz.y, Szer_Kamienia, Wys_Kamienia) == true)
		{
			zniszczenie = true;
		}
		if (temp != zniszczenie)
		{
			czas_wybuchu = SDL_GetTicks();
			if (niesm == 0)
				zycia--;
			if (zycia == 0)
			{
				koniec = true;
				zakonczenie(wsk);
			}
				
		}
	}

}
void Gra::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex_mapa, &kamera, NULL);
	if (zniszczenie == false)
	{
		samochod->render(renderer);
	}
	kamien2->render(renderer);
	ramka->render(renderer);
	d_ramka->render(renderer);
	if (sortuj==Sortuj_P)
	{
		lista_p->render(renderer);
	}
	if (sortuj == Sortuj_T)
	{
		lista_t->render(renderer);
	}
	SDL_RenderPresent(renderer);
}
void Gra::szybkosc()
{
	SDL_Delay(pr);
}
void Gra::resp()
{
	if (zniszczenie == true)
	{
		czas_respu = SDL_GetTicks();
		if (pauza == 0)
		{
			czas_potrzebny += czas_respu - czas_wybuchu;
		}
		if (czas_potrzebny > Respawn)
		{
			zniszczenie = 0;
			czas_respu = 0;
			czas_wybuchu = 0;
			czas_potrzebny = 0;
			samochod->respawn((Szerokosc_Ekranu - Szer_Auta) / 2, Dlugosc_Ekranu - (Wys_Auta * 2));
		}
		czas_wybuchu = czas_respu;
	}
}
void Gra::ekran()
{
	ekranKonca = new EkranKonca(renderer, czcionka, timer, w);
}
void Gra::render_koniec()
{
	SDL_RenderClear(renderer);
	ekranKonca->render(renderer);
	SDL_RenderPresent(renderer);
}
void Gra::klawisze_koniec()
{
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				koniec2 = 1;
			}
			else if (event.key.keysym.sym == SDLK_1)
			{
				zapis = 1;
				koniec2 = 1;
			}
			else if (event.key.keysym.sym == SDLK_2)
			{
				koniec2 = 1;
			}
			break;
		case SDL_QUIT:
			koniec2 = 1;
			break;
		};
	}
}
void Gra::zapisywanie()
{
	if (zapis == 1)
	{
		FILE* plik = fopen("wyniki.txt", "a");
		if (plik)
		{
			char tekst[Bufor];
			timer = timer * Mili;
			sprintf(tekst,"%.1lf %.1lf\n", w,timer);
			fputs(tekst, plik);
			fclose(plik);
		}
	}
}
void Gra::czyszczenie()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(tex_mapa);
	samochod->czyszczenie();
	ramka->czyszczenie();
	d_ramka->czyszczenie();
	kamien2->czyszczenie();
	lista_p->czyszczenie();
	lista_t->czyszczenie();
	delete samochod;
	delete ramka;
	delete d_ramka;
	delete kamien2;
	delete lista_p;
	delete lista_t;
}
void::Gra::czyszczenie_koniec()
{
	ekranKonca->czyszczenie();
	delete ekranKonca;
}
void Gra::zakonczenie(bool &k)
{
	k = 1;
}