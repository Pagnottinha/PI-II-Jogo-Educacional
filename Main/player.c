#include "player.h"
#include <stdio.h>

/*
	Para criar sprites sheets (realizar os passos no main.c):
	- Mudar o NUM_PATH e NUM_SPRITES
	- Criar uma matriz com o path para os bitmaps
	- Chamar a função desejada

	char path[NUM_SPRITES][NUM_PATH] = {
		"Sprites/Player/walking1.bmp",
		"Sprites/Player/walking2.bmp",
		"Sprites/Player/walking3.bmp",
		"Sprites/Player/walking4.bmp"
	};

	juntarSpriteSheet(path, "walking.bmp");
*/

void createSpriteSheet(char path[][NUM_PATH], char name[]) { // CRIA SPRITES EM UMA LINHA
	
	ALLEGRO_BITMAP* image[NUM_CRIAR_SPRITES];
	ALLEGRO_BITMAP* outImage;

	int i;
	for (i = 0; i < NUM_CRIAR_SPRITES; i++) {
		printf("%s\n", path[i]);
		image[i] = al_load_bitmap(path[i]);
	}

	int imageWidth = al_get_bitmap_width(image[0]);
	int imageHeight = al_get_bitmap_height(image[0]);

	outImage = al_create_bitmap(imageWidth * NUM_CRIAR_SPRITES, imageHeight);

	al_set_target_bitmap(outImage);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (i = 0; i < NUM_CRIAR_SPRITES; i++) {
		al_draw_bitmap(image[i], i * imageWidth, 0, 0);
	}

	al_save_bitmap(name, outImage);
}

void juntarSpriteSheets(char path[][NUM_PATH], char name[]) { // JUNTA AS SPRITES DE UMA DIMENSÃO 
	ALLEGRO_BITMAP* image[NUM_CRIAR_SPRITES];
	ALLEGRO_BITMAP* outImage;

	int i;
	for (i = 0; i < NUM_CRIAR_SPRITES; i++) {
		printf("%s\n", path[i]);
		image[i] = al_load_bitmap(path[i]);
	}

	int imageWidth = al_get_bitmap_width(image[0]);
	int imageHeight = al_get_bitmap_height(image[0]);

	outImage = al_create_bitmap(imageWidth, imageHeight * NUM_CRIAR_SPRITES);

	al_set_target_bitmap(outImage);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (i = 0; i < NUM_CRIAR_SPRITES; i++) {
		al_draw_bitmap(image[i], 0, i * imageHeight, 0);
	}

	al_save_bitmap(name, outImage);
	
}

void initPlayer(Player* player, ALLEGRO_DISPLAY* display) {
	// deixar todos os estados de ação em false
	int i;
	for (i = 0; i < QNT_ACOES; i++) {
		player->acoes[i] = false;
	}

	// posição player
	player->POS[X] = al_get_display_width(display) / 2;
	player->POS[Y] = al_get_display_height(display) / 2;

	player->velocidade = 2;
	
	// frame
	player->framePOS[X] = 96;
	player->framePOS[Y] = 96;
	player->ContFrame = 0;
	player->FrameAtual = 0;
	player->linhaAnimacao = 1;
	player->frameDelay = 15;
	player->tipoAnimacao = WALKING; // bitmap inicial

	// walking
	player->maxFrame[WALKING] = 8;

	// declarar 
	player->sheets[WALKING] = al_load_bitmap("Sprites/Player/walking.bmp");
	
	for (i = 0; i < NUM_SPITES; i++) {
		al_convert_mask_to_alpha(player->sheets[i], al_map_rgb(94, 66, 41));
	}
}

void andarPlayerCima(Player* player) {
	player->linhaAnimacao = UP;
	player->tipoAnimacao = WALKING;
	if (player->POS[Y] > 0) {
		player->POS[Y] -= player->velocidade;
	}
}

void andarPlayerBaixo(Player* player) {
	player->linhaAnimacao = DOWN;
	player->tipoAnimacao = WALKING;
	if (player->POS[Y] < HEIGHT - player->framePOS[X]) {
		player->POS[Y] += player->velocidade;
	}
}

void andarPlayerEsqueda(Player* player) {
	player->linhaAnimacao = LEFT;
	player->tipoAnimacao = WALKING;
	if (player->POS[X] > 0) {
		player->POS[X] -= player->velocidade;
	}
}

void andarPlayerDireita(Player* player) {
	player->linhaAnimacao = RIGHT;
	player->tipoAnimacao = WALKING;
	if (player->POS[X] < WIDTH - player->framePOS[X]) {
		player->POS[X] += player->velocidade;
	}
}

void desenharPlayer(Player* player) {
	
	// pegar o frame no bitmap
	int fx = player->FrameAtual * player->framePOS[X];
	int fy = player->linhaAnimacao * player->framePOS[Y];

	al_draw_bitmap_region(player->sheets[player->tipoAnimacao], fx, fy, player->framePOS[X], player->framePOS[Y],
		player->POS[X], player->POS[Y], 0);
}