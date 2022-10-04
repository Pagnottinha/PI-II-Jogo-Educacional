#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "player.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	// Declaração de variáveis para funcionar o Allegro
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* eventQueue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	// Booleans
	bool done = false;
	bool desenhar = true;

	// Player
	Player player;

	// INIT ALLEGRO
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

	// inicio do jogo
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;
			
			if (player.acoes[LEFT])
				andarPlayerEsqueda(&player);

			if (player.acoes[RIGHT])
				andarPlayerDireita(&player);

			if (player.acoes[UP])
				andarPlayerCima(&player);

			if (player.acoes[DOWN])
				andarPlayerBaixo(&player);

			// TODO: Uma sprite para quando o player ficar parado!
			if (player.acoes[UP] || player.acoes[DOWN] || player.acoes[LEFT] || player.acoes[RIGHT]) {
				if (++player.ContFrame >= player.frameDelay) {
					player.FrameAtual++;
					if (player.FrameAtual >= player.maxFrame[player.tipoAnimacao])
						player.FrameAtual = 0;

					player.ContFrame = 0;
				}
			}


		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // quando clicar no X do display
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

		if (desenhar && al_event_queue_is_empty(eventQueue)) { // desenhar somente quando tiver frames

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