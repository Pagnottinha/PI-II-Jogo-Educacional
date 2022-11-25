#include "Background.h"

void InitBackground(Background *back, float x, float y, int width, int height, char* imagePath)
{
	back->x = x;
	back->y = y;;
	back->width = width;
	back->height = height;
	back->image = al_load_bitmap(imagePath);
}

void DrawBackground(Background back)
{
	al_draw_bitmap(back.image, back.x, back.y, 0);
}
