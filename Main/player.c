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

void initPlayer(Player* player, ALLEGRO_DISPLAY* display) {
	player->acoes[UP] = false;
	player->acoes[DOWN] = false;
	player->acoes[LEFT] = false;
	player->acoes[RIGHT] = false;

	player->POS[X] = al_get_display_width(display) / 2;
	player->POS[Y] = al_get_display_height(display) / 2;

	player->velocidade = 2;
	
	player->framePOS[X] = 96;
	player->framePOS[Y] = 96;
	player->ContFrame = 0;
	player->FrameAtual = 0;
	player->maxFrame = 8;
	player->linhaAnimacao = 1;
	player->tipoAnimacao = WALKING;
	player->frameDelay = 15;


	player->sheets[WALKING][UP] = al_load_bitmap("Sprites/Player/Walking/cima.bmp");
	player->sheets[WALKING][DOWN] = al_load_bitmap("Sprites/Player/Walking/baixo.bmp");
	player->sheets[WALKING][LEFT] = al_load_bitmap("Sprites/Player/Walking/esquerda.bmp");
	player->sheets[WALKING][RIGHT] = al_load_bitmap("Sprites/Player/Walking/direita.bmp");
	
	int i;
	for (i = 0; i < 4; i++) {
		al_convert_mask_to_alpha(player->sheets[WALKING][i], al_map_rgb(94, 66, 41));
	}
}

void andarPlayerCima(Player* player) {
	player->linhaAnimacao = UP;
	if (player->POS[Y] > 0) {
		player->POS[Y] -= player->velocidade;
	}
}

void andarPlayerBaixo(Player* player) {
	player->linhaAnimacao = DOWN;
	if (player->POS[Y] + 35 < HEIGHT) {
		player->POS[Y] += player->velocidade;
	}
}

void andarPlayerEsqueda(Player* player) {
	player->linhaAnimacao = LEFT;
	if (player->POS[X] > 0) {
		player->POS[X] -= player->velocidade;
	}
}

void andarPlayerDireita(Player* player) {
	player->linhaAnimacao = RIGHT;
	if (player->POS[X] + 20 < WIDTH) {
		player->POS[X] += player->velocidade;
	}
}

void desenharPlayer(Player* player) {
	
	int fx = player->FrameAtual * player->framePOS[X];

	al_draw_bitmap_region(player->sheets[player->tipoAnimacao][player->linhaAnimacao], fx, player->linhaAnimacao, player->framePOS[X], player->framePOS[Y],
		player->POS[X], player->POS[Y], 0);
}