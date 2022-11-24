#include "Background.h"

void InitBackground(Background back, float x, float y, int width, int height, ALLEGRO_BITMAP* image)
{
	back.x = x;
	back.y = y;;
	back.width = width;
	back.height = height;
	back.image = image;
}

void DrawBackground(Background back)
{
	al_draw_bitmap(back.image, back.x, back.y, 0);
}
