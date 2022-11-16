#include "Batalha.h"

int batalha(Allegro allegro) {
	// Booleans
	bool done = false;
	bool desenhar = true;

	// Player
	Player player;
	Enemies enemies;

	initPlayer(&player, allegro.display);
	InitEnemie(&enemies);

	// inicio do jogo
	while (!done && player.vivo) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro.eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;

			if (player.acoes[ATAQUE]) {
				ataquePlayer(&player, &enemies);
			}
			else if (player.acoes[UP] || player.acoes[DOWN] || player.acoes[LEFT] || player.acoes[RIGHT]) {
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

			UpdateEnemie(&enemies, &player);

			if (enemies.enemieDeath == enemies.countEnemies) {
				enemies.waves[QNT]++;
				enemies.countEnemies++;
				enemies.enemieDeath = 0;

				if (enemies.waves[QNT] <= enemies.waves[MAX])
					NewWave(&enemies);
				else {
					done = true;
					desenhar = false;
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
			case ALLEGRO_KEY_SPACE:
				player.acoes[ATAQUE] = true;
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

			DrawEnemie(enemies);
			desenharPlayer(&player);

			al_draw_text(allegro.font[a24], al_map_rgb(255, 255, 255), 20, 20, 0, "Vida: ");
			al_draw_textf(allegro.font[a24], al_map_rgb(255, 255, 255), WIDTH - 150, 20, 0, "Onda %d", enemies.waves[QNT]);
			al_draw_textf(allegro.font[a24], al_map_rgb(255, 255, 255), 20, HEIGHT - 40, 0, "Inimigos Restantes %d", enemies.countEnemies - enemies.enemieDeath);

			al_draw_rectangle(80, 25, 200, 45, al_map_rgb(0, 255, 0), 2);

			al_draw_filled_rectangle(80, 25, player.vida[ATUAL] + 80, 45, al_map_rgb(0, 255, 0));

			al_flip_display();

			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

	destroyBitmapsEnemie(&enemies);
	destroyBitmapsPlayer(&player);

	return !player.vivo;
}