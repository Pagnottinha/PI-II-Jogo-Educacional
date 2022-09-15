#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Objetos.h"

#define WIDTH 800
#define HEIGHT 600

enum ACOES {UP, DOWN, LEFT, RIGHT, ATTACK, BLOCK};

void initPlayer(Player *player);
void desenharPlayer(Player* player);

int prototipo(void) {

	bool done = false;
	bool acoes[6] = { false, false, false, false, false, false };

	Player player;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if (!display)
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();

	initPlayer(&player);

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);



		desenharPlayer(&player);

		al_flip_display();

		al_map_rgb(0, 0, 0);
	}

	return 0;
}

void initPlayer(Player *player) {
	player->ID = PLAYER;
	player->pos[X] = WIDTH / 2;
	player->pos[Y] = HEIGHT / 2;
	player->pos[BOUNDX] = 6;
	player->pos[BOUNDY] = 7;
	player->velocidade = 7;
	player->vida = 3;
}

void desenharPlayer(Player* player) {
	al_draw_filled_rectangle(player->pos[X], player->pos[Y], player->pos[X] + 20, player->pos[Y] + 35, al_map_rgb(255, 0, 0));
}