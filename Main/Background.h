#include "allegro5/allegro.h"
#include "allegro5/bitmap.h"

typedef struct
{
	float x;
	float y;
	int width;
	int height;

	ALLEGRO_BITMAP* image;

}Background;

void InitBackground(Background* back, float x, float y, int width, int height, char* imagePath);
void DrawBackground(Background back);