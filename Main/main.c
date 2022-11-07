#include "Init.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

int main(void) {

	// Booleans
	bool done = false;
	bool desenhar = true;

	// Player
	Player player;

	Allegro allegro = init();

	if (!allegro.deuCerto)
		return -1;

	initPlayer(&player, allegro.display);

	// inicio do jogo
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro.eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;

			// TODO: Uma sprite para quando o player ficar parado!
			if (player.acoes[UP] || player.acoes[DOWN] || player.acoes[LEFT] || player.acoes[RIGHT]) {
				if (player.acoes[LEFT])
					andarPlayerEsqueda(&player);

				if (player.acoes[RIGHT])
					andarPlayerDireita(&player);

				if (player.acoes[UP])
					andarPlayerCima(&player);

				if (player.acoes[DOWN])
					andarPlayerBaixo(&player);
			}
			else {
				player.tipoAnimacao = IDLE;
			}

			if (++player.ContFrame >= player.frameDelay) {
				player.FrameAtual++;
				if (player.FrameAtual >= player.maxFrame[player.tipoAnimacao])
					player.FrameAtual = 0;

				player.ContFrame = 0;
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

		if (desenhar && al_is_event_queue_empty(allegro.eventQueue)) { // desenhar somente quando tiver frames

			desenhar = false;

			desenharPlayer(&player);

			al_flip_display();

			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		
	}

	destroy(&allegro);

	return 0;
}