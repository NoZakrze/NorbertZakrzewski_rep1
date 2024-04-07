#include "SDL.h"
#include "Kamien.h"
#include "Gra.h"
#include <stdio.h>

Kamien::Kamien(int x, int y, SDL_Renderer* renderer)
{
	SDL_Surface* kamien = SDL_LoadBMP("./kamien.bmp");
	kamien_tex = SDL_CreateTextureFromSurface(renderer, kamien);
	SDL_FreeSurface(kamien);
	obraz.x = x;
	obraz.y = y;
	obraz.h = Wys_Kamienia;
	obraz.w = Szer_Kamienia;
}
void Kamien::update()
{
	obraz.y++;
	if (obraz.y > 1000)
		obraz.y = 0;
}
void Kamien::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, kamien_tex, NULL, &obraz);
}
void Kamien::czyszczenie()
{
	SDL_DestroyTexture(kamien_tex);
}