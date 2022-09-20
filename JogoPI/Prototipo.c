#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Objetos.h"

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

enum ACOES {UP, DOWN, LEFT, RIGHT, ATTACK, BLOCK};

int prototipo(void) {

	bool done = false;
	bool acoes[6] = { false, false, false, false, false, false };
	bool desenhar = true;

	Player player;
	Lanca lanca;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_BITMAP* imagePlayer = NULL;

	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if (!display)
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	initPlayer(&player, display);
	initLanca(&lanca, &player, display);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			desenhar = true;

			if (acoes[LEFT])
				andarPlayerEsqueda(&player);

			if (acoes[RIGHT])
				andarPlayerDireita(&player);

			if (acoes[UP])
				andarPlayerCima(&player);

			if (acoes[DOWN])
				andarPlayerBaixo(&player);

			if (acoes[ATTACK])
				atacarLanca(&lanca);
			else {
				lanca.pos[X] = lanca.player->pos[X] + 20;
				lanca.pos[Y] = lanca.player->pos[Y] - 10;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_W:
				case ALLEGRO_KEY_UP:
					acoes[UP] = true;
					break;
				case ALLEGRO_KEY_S:
				case ALLEGRO_KEY_DOWN:
					acoes[DOWN] = true;
					break;
				case ALLEGRO_KEY_A:
				case ALLEGRO_KEY_LEFT:
					acoes[LEFT] = true;
					break;
				case ALLEGRO_KEY_D:
				case ALLEGRO_KEY_RIGHT:
					acoes[RIGHT] = true;
					break;
				case ALLEGRO_KEY_K:
					acoes[ATTACK] = true;
					break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_W:
					acoes[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:
					acoes[DOWN] = false;
					break;
				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_A:
					acoes[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
				case ALLEGRO_KEY_D:
					acoes[RIGHT] = false;
					break;
				case ALLEGRO_KEY_K:
					acoes[ATTACK] = false;
					break;
			}
		}

		if (desenhar && al_event_queue_is_empty(event_queue)) {
			desenhar = false;

			desenharPlayer(&player);
			desenharLanca(&lanca);

			al_flip_display();

			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}

void initPlayer(Player *player, ALLEGRO_DISPLAY* display) {
	player->ID = PLAYER;
	player->pos[X] = WIDTH / 2;
	player->pos[Y] = HEIGHT / 2;
	player->dimensoes[W] = 20;
	player->dimensoes[H] = 30;
	player->velocidade = 3;
	player->vida = 3;
	player->imagem = criarBitmapPlayer(player, display);
}

ALLEGRO_BITMAP* criarBitmapPlayer(Player* player, ALLEGRO_DISPLAY* display) {
	ALLEGRO_BITMAP* image = al_create_bitmap(player->dimensoes[W], player->dimensoes[H]);

	al_set_target_bitmap(image);

	al_draw_filled_rectangle(0, 0, player->dimensoes[W], player->dimensoes[H], al_map_rgb(0, 255, 0));

	al_set_target_bitmap(al_get_backbuffer(display));

	return image;
}

void desenharPlayer(Player* player) {
	al_draw_bitmap(
		player->imagem, 
		player->pos[X], 
		player->pos[Y] , 
		0
	);
}

void andarPlayerCima(Player* player) {
	if (player->pos[Y] > 0) {
		player->pos[Y] -= player->velocidade;
	}
}
void andarPlayerBaixo(Player* player) {
	if (player->pos[Y] + 35 < HEIGHT) {
		player->pos[Y] += player->velocidade;
	}
}
void andarPlayerEsqueda(Player* player) {
	if (player->pos[X] > 0) {
		player->pos[X] -= player->velocidade;
	}
}
void andarPlayerDireita(Player* player) {
	if (player->pos[X] + 20 < WIDTH) {
		player->pos[X] += player->velocidade;
	}
}

void initLanca(Lanca* lanca, Player* player, ALLEGRO_DISPLAY* display) {
	lanca->ID = LANCA;
	lanca->dimensoes[W] = 3;
	lanca->dimensoes[H] = 40;
	lanca->pos[BX] = lanca->dimensoes[W] / 2;
	lanca->pos[BY] = lanca->dimensoes[H] / 2;
	lanca->dano = 2;
	lanca->player = player;
	lanca->imagem = criarBitmapLanca(lanca, display);
}

ALLEGRO_BITMAP* criarBitmapLanca(Lanca* lanca, ALLEGRO_DISPLAY* display) {
	ALLEGRO_BITMAP* image = al_create_bitmap(3, 40);

	al_set_target_bitmap(image);

	al_clear_to_color(al_map_rgb(50, 50, 50));

	al_draw_filled_rectangle(0, 0, lanca->dimensoes[W], lanca->dimensoes[H], al_map_rgb(0, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	return image;
}

void desenharLanca(Lanca* lanca) {
	al_draw_bitmap(
		lanca->imagem,
		lanca->pos[X],
		lanca->pos[Y],
		0
	);
}

void atacarLanca(Lanca* lanca) {
	lanca->pos[Y] = lanca->player->pos[Y] - lanca->dimensoes[Y] / 2;
	lanca->pos[X] = lanca->player->pos[X] + 20;
}