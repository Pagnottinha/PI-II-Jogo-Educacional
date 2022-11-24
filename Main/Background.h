#include "Init.h"

typedef struct 
{
	float x;
	float y;
	int width;
	int height;

	ALLEGRO_BITMAP* image;
}Background;

void InitBackground(Background back, float x, float y, int width, int height, ALLEGRO_BITMAP* image);
void DrawBackground(Background back);