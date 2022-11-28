#include "Background.h"

void InitBackground(Background *back, float x, float y, char* imagePath)
{
	back->x = x;
	back->y = y;
	back->image = al_load_bitmap(imagePath);
	back->width = al_get_bitmap_width(back->image);
	back->height = al_get_bitmap_height(back->image);
}

void DrawBackground(Background back)
{
	al_draw_bitmap(back.image, back.x, back.y, 0);
}
