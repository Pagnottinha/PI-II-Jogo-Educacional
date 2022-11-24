#include "Background.h"

void InitBackground(Background *back, float x, float y, int width, int height)
{
	back->x = x;
	back->y = y;;
	back->width = width;
	back->height = height;
	back->image = al_load_bitmap("BackgroundNovo.png");
}

void DrawBackground(Background back)
{
	al_draw_bitmap(back.image, back.x, back.y, 0);
}
