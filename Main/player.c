#include "player.h"
#include <stdio.h>


/*
	Para criar sprites sheets basta fazer o seguinte na função main e mudar na função o número de caracteres:

	char path[8][41] = {
		"Sprites/Player/Walking/walking e0000.bmp",
		"Sprites/Player/Walking/walking e0001.bmp",
		"Sprites/Player/Walking/walking e0002.bmp",
		"Sprites/Player/Walking/walking e0003.bmp",
		"Sprites/Player/Walking/walking e0004.bmp",
		"Sprites/Player/Walking/walking e0005.bmp",
		"Sprites/Player/Walking/walking e0006.bmp",
		"Sprites/Player/Walking/walking e0007.bmp"
	};

	createSpriteSheet(8, path, "direita.bmp");
*/

void createSpriteSheet(int arraySize, char path[][41], char name[]) {
	
	ALLEGRO_BITMAP* image[8];
	ALLEGRO_BITMAP* outImage;

	int i;
	for (i = 0; i < arraySize; i++) {
		printf("%s\n", path[i]);
		image[i] = al_load_bitmap(path[i]);
	}

	int imageWidth = al_get_bitmap_width(image[0]);
	int imageHeight = al_get_bitmap_height(image[0]);

	outImage = al_create_bitmap(imageWidth * arraySize, imageHeight);

	al_set_target_bitmap(outImage);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (i = 0; i < arraySize; i++) {
		al_draw_bitmap(image[i], i * imageWidth, 0, 0);
	}

	al_save_bitmap(name, outImage);
}