#include "Tutorial.h"

int tutorial(Allegro* allegro) {
	// Booleans
	bool done = false;
	bool desenhar = true;

	int niveis = 0;
	char mensagem[3][40] = { 
		"Para andar use WASD ou setinhas.", 
		"Para atacar aperte a barra de espaço.", 
		"Mate os inimigos." 
	};
	bool nivelAndar[4] = { false, false, false, false };

	Background fundoMensagem;
	InitBackground(&fundoMensagem, WIDTH / 2, 50, "Sprites/Tutorial/MadeiraParaTutorial.png");

	// Player
	Player player;
	Enemies enemies;

	//BAckground
	Background BG;

	InitBackground(&BG, 0, 0, "Sprites/Background/BackgroundFloresta.png");

	initPlayer(&player, allegro->display);
	InitEnemie(&enemies, 0);

	// inicio do jogo
	while (!done && player.vivo) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro->eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;

			if (player.acoes[ATAQUE]) {
				ataquePlayer(&player, &enemies);
				if (niveis == 1) {
					InitEnemie(&enemies, 3);
					niveis++;
				}
					
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

			if (niveis == 0) {
				if (nivelAndar[UP] && nivelAndar[DOWN] && nivelAndar[LEFT] && nivelAndar[RIGHT]) {
					niveis++;
				}
			}
			else if (niveis == 2) {
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

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // quando clicar no X do display
			done = true;
			allegro->close = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				player.acoes[UP] = true;
				if (niveis == 0)
					nivelAndar[UP] = true;
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				player.acoes[DOWN] = true;
				if (niveis == 0)
					nivelAndar[DOWN] = true;
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				player.acoes[LEFT] = true;
				if (niveis == 0)
					nivelAndar[LEFT] = true;
				break;
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				player.acoes[RIGHT] = true;
				if (niveis == 0)
					nivelAndar[RIGHT] = true;
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

		if (desenhar && al_is_event_queue_empty(allegro->eventQueue)) { // desenhar somente quando tiver frames

			desenhar = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			DrawBackground(BG);
			DrawEnemie(enemies);
			desenharPlayer(&player);

			al_draw_text(allegro->font[r24], al_map_rgb(255, 255, 255), 20, 20, 0, "Vida: ");
			al_draw_textf(allegro->font[r24], al_map_rgb(255, 255, 255), WIDTH - 150, 20, 0, "Onda %d", enemies.waves[QNT]);
			al_draw_textf(allegro->font[r24], al_map_rgb(255, 255, 255), 20, HEIGHT - 40, 0, "Inimigos Restantes %d", enemies.countEnemies - enemies.enemieDeath);

			al_draw_rectangle(100, 20, 220, 40, al_map_rgb(0, 255, 0), 2);

			al_draw_filled_rectangle(100, 20, player.vida[ATUAL] + 100, 40, al_map_rgb(0, 255, 0));

			al_draw_bitmap(fundoMensagem.image, fundoMensagem.x - fundoMensagem.width / 2.0, fundoMensagem.y, 0);
			al_draw_multiline_text(
				allegro->font[r20],
				al_map_rgb(255, 255, 255),
				fundoMensagem.x,
				fundoMensagem.y + fundoMensagem.height / 2.0 - al_get_font_line_height(allegro->font[r16]),
				fundoMensagem.width,
				al_get_font_line_height(allegro->font[r20]) + 10,
				ALLEGRO_ALIGN_CENTRE,
				mensagem[niveis]
			);

			al_flip_display();
		}

	}

	destroyBitmapsEnemie(&enemies);
	destroyBitmapsPlayer(&player);
	al_destroy_bitmap(BG.image);

	return !player.vivo;
}