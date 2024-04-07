#include "SDL.h"
#include "Auto.h"
#include "Gra.h"
#include <stdio.h>

Auto::Auto(int x, int y, SDL_Renderer* renderer)
{
	SDL_Surface* samochod = SDL_LoadBMP("./auto.bmp");
	auto_tex = SDL_CreateTextureFromSurface(renderer, samochod);
	SDL_FreeSurface(samochod);
	obraz.x = x;
	obraz.y = y;
	obraz.h = Wys_Auta;
	obraz.w = Szer_Auta;
}
void Auto::lewo()
{
	obraz.x-=Ruch;
}
void Auto::prawo()
{
	obraz.x+=Ruch;
}
void Auto::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, auto_tex, NULL ,&obraz);
}
int Auto::auto_x()
{
	return obraz.x;
}
int Auto::auto_y()
{
	return obraz.y;
}
void Auto::respawn(int x, int y)
{
	obraz.x = x;
	obraz.y = y;
}
bool Auto::kolizja(int x, int y, int szer, int dl)
{
	if (obraz.x <= x + szer && obraz.x >= x - Szer_Auta
		&& obraz.y <= y + Wys_Auta && obraz.y >= y - dl)
		return true;
	else
		return false;
}
void Auto::czyszczenie()
{
	SDL_DestroyTexture(auto_tex);
}