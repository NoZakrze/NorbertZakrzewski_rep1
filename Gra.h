#pragma once
#include "SDL.h"
#include "Auto.h"
#include "Ramka.h"
#include "Kamien.h"
#include "DolnaRamka.h"
#include "EkranKonca.h"
#include "Lista.h"
#include <stdio.h>

#define Szerokosc_Ekranu 640
#define Dlugosc_Ekranu 480
#define Mapa1 480
#define Mapa2 960
#define Mapa3 1440
#define Mapa4 1920
#define Dlugosc_Obrazka 1920
#define Poczatek_Obrazka 0
#define Pod_Opoznienie 2
#define Mniejsze_Opoznienie 1
#define Wieksze_Opoznienie 4
#define Mili 0.001
#define Punkty 40
#define Pobocze1 150
#define Pobocze2 200
#define Pobocze3 250
#define Odliczanie 10000
#define Nowe_Zycie 200
#define Sortuj_P 1
#define Sortuj_T 2
#define Alpha 255
#define Flags 0
#define Kamien_X 350
#define Respawn 500

class Gra
{
	public:
		bool koniec,nowa,koniec2,zapis_koniec;
		Gra(const char tytul[], int wsp_X, int wsp_Y, int szer, int dl); // stworzenie ekranu, renderera, obietku Gra i pozostalych obietkow
		void obsluga_klawiszy(bool& wsk);
		void czas(); // Mierzenie czasu i czasu z nielimitowana licza aut
		void wynik(); // Liczenie wyniku gracza
		void update(); // zmiana mapy i obietkow na niej
		void kolizja(); // sprawdzanie czy auto wyjechalo poza droge
		void wybuch(bool& wsk); // sprawdzanie kolizji auta z mapa i innymi obiektami 
		void render(); // renderowanie tekstur
		void szybkosc(); // szybkosc poruszania sie auta
		void resp(); // ponowne pojawianie sie zniszczonego auta
		void ekran(); // inicjacja ekranu koncowego
		void render_koniec(); // renderowanie ekranu koncowego
		void klawisze_koniec(); // obsluga klawiszy na ekranie koncowym
		void zapisywanie(); // zapisywanie wyniku i czasu do pliku
		void czyszczenie(); // czyszczenie pamieci
		void czyszczenie_koniec();
		void zakonczenie(bool &k); // ustawianie zmiennej konczacej program

	private:
		SDL_Window* window{};
		SDL_Renderer* renderer{};
		SDL_Texture* tex_mapa{};
		SDL_Rect kamera;
		SDL_Event event;
		SDL_Surface* czcionka;
		int pr,czas_1,czas_2,czas_wybuchu,czas_respu,zycia,czas_potrzebny, pobocze, sortuj;
		double timer,w, niesm, dodawanie_zyc;
		bool licz_punkty,zniszczenie,pauza,zapis;
		Auto* samochod;
		Ramka* ramka;
		DolnaRamka* d_ramka;
		Kamien* kamien2;
		EkranKonca* ekranKonca;
		Lista* lista_p, *lista_t;

};