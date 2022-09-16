#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Objetos.h"

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

enum ACOES {UP, DOWN, LEFT, RIGHT, ATTACK, BLOCK};

void initPlayer(Player *player);
void desenharPlayer(Player* player);
void andarPlayerCima(Player* player);
void andarPlayerBaixo(Player* player);
void andarPlayerEsqueda(Player* player);
void andarPlayerDireita(Player* player);

int prototipo(void) {

	bool done = false;
	bool acoes[6] = { false, false, false, false, false, false };
	bool desenhar = true;

	Player player;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if (!display)
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	initPlayer(&player);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			desenhar = true;

			if (acoes[UP])
				andarPlayerCima(&player);

			if (acoes[DOWN])
				andarPlayerBaixo(&player);

			if (acoes[LEFT])
				andarPlayerEsqueda(&player);

			if (acoes[RIGHT])
				andarPlayerDireita(&player);
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
			}
		}

		if (desenhar && al_event_queue_is_empty(event_queue)) {
			desenhar = false;

			desenharPlayer(&player);

			al_flip_display();

			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_display(display);

	return 0;
}

void initPlayer(Player *player) {
	player->ID = PLAYER;
	player->pos[X] = WIDTH / 2;
	player->pos[Y] = HEIGHT / 2;
	player->pos[BOUNDX] = 6;
	player->pos[BOUNDY] = 7;
	player->velocidade = 3;
	player->vida = 3;
}

void desenharPlayer(Player* player) {
	al_draw_filled_rectangle(player->pos[X], player->pos[Y], player->pos[X] + 20, player->pos[Y] + 35, al_map_rgb(255, 0, 0));
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