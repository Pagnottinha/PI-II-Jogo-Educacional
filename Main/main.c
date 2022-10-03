#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "player.h"
#include "constantes.h"

int main(void) {
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* eventQueue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	bool done = false;
	bool desenhar = true;
	Player player;

	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if (!display)
		return 0;

	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_install_keyboard();
	al_init_image_addon();

	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	initPlayer(&player, display);

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			desenhar = true;
			

			if (player.acoes[LEFT])
				andarPlayerEsqueda(&player);

			if (player.acoes[RIGHT])
				andarPlayerDireita(&player);

			if (player.acoes[UP])
				andarPlayerCima(&player);

			if (player.acoes[DOWN])
				andarPlayerBaixo(&player);

			if (player.acoes[UP] || player.acoes[DOWN] || player.acoes[LEFT] || player.acoes[RIGHT]) {
				if (++player.ContFrame >= player.frameDelay) {
					player.FrameAtual++;
					if (player.FrameAtual >= player.maxFrame)
						player.FrameAtual = 0;

					player.ContFrame = 0;
				}
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
					player.acoes[UP] = true;
					break;
				case ALLEGRO_KEY_S:
				case ALLEGRO_KEY_DOWN:
					player.acoes[DOWN] = true;
					break;
				case ALLEGRO_KEY_A:
				case ALLEGRO_KEY_LEFT:
					player.acoes[LEFT] = true;
					break;
				case ALLEGRO_KEY_D:
				case ALLEGRO_KEY_RIGHT:
					player.acoes[RIGHT] = true;
					break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_W:
					player.acoes[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:
					player.acoes[DOWN] = false;
					break;
				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_A:
					player.acoes[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
				case ALLEGRO_KEY_D:
					player.acoes[RIGHT] = false;
					break;
			}
		}

		if (desenhar && al_event_queue_is_empty(eventQueue)) {

			desenhar = false;

			desenharPlayer(&player);

			al_flip_display();

			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		
	}

	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);

	return 0;
}