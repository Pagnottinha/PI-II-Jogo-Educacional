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

	juntarSpriteSheets(path, "walking.bmp");
*/

void createSpriteSheet(char path[NUM_CRIAR_SPRITES][NUM_PATH], char name[]) { // CRIA SPRITES EM UMA LINHA
	
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

void juntarSpriteSheets(char path[NUM_CRIAR_SPRITES][NUM_PATH], char name[]) { // JUNTA AS SPRITES DE UMA DIMENSÃO 
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
	player->dimensoesFrame[X] = 286;
	player->dimensoesFrame[Y] = 130;
	player->ContFrame = 0;
	player->FrameAtual = 0;
	player->linhaAnimacao = DIREITA;
	player->frameDelay = 15;
	player->dimensoesLanca[X] = 102;
	player->dimensoesLanca[Y] = 5;

	player->maxFrame[CORRENDO] = 6;
	player->maxFrame[IDLE] = 6;
	player->maxFrame[ATACANDO] = 6;

	// declarar 
	player->sheets[CORRENDO] = al_load_bitmap("Sprites/Player/correr.png");
	player->sheets[ATACANDO] = al_load_bitmap("Sprites/Player/ataque.png");
	player->sheets[IDLE] = al_load_bitmap("Sprites/Player/idle.png");
	
	for (i = 0; i < NUM_SPRITES; i++) {
		al_convert_mask_to_alpha(player->sheets[i], al_map_rgb(0, 0, 0));
	}
}

void andarPlayerCima(Player* player) {
	player->tipoAnimacao = CORRENDO;
	if (player->POS[Y] > 0) {
		player->POS[Y] -= player->velocidade;
	}
}

void andarPlayerBaixo(Player* player) {
	player->tipoAnimacao = CORRENDO;
	if (player->POS[Y] < HEIGHT - player->dimensoesFrame[Y]) {
		player->POS[Y] += player->velocidade;
	}
}

void andarPlayerEsqueda(Player* player) {
	player->linhaAnimacao = ESQUERDA;
	player->tipoAnimacao = CORRENDO;
	if (player->POS[X] > 0 - (player->dimensoesLanca[X] - 50)) {
		player->POS[X] -= player->velocidade;
	}
}

void andarPlayerDireita(Player* player) {
	player->linhaAnimacao = DIREITA;
	player->tipoAnimacao = CORRENDO;
	if (player->POS[X] < WIDTH - (50 + player->dimensoesLanca[X] + 82)) {
		player->POS[X] += player->velocidade;
	}
}

void desenharPlayer(Player* player) {
	
	// pegar o frame no bitmap
	int fx = player->FrameAtual * player->dimensoesFrame[X];
	int fy = player->linhaAnimacao * player->dimensoesFrame[Y];

	al_draw_bitmap_region(player->sheets[player->tipoAnimacao], fx, fy, player->dimensoesFrame[X], player->dimensoesFrame[Y],
		player->POS[X], player->POS[Y], 0);
}