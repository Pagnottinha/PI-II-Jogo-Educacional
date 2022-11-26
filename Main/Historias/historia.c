#include "historia.h"

int historia(Allegro allegro, char* pathDialogo) {
	int flag;

	Personagens personagens;
	flag = pegarPersonagens(&personagens);

	if (flag != 0)
		return flag;

	Dialogos dialogos;
	flag = pegarDialogos(&dialogos, pathDialogo);

	if (flag != 0)
		return flag;

	Escolhas escolhasTxt;
	flag = pegarEscolhas(&escolhasTxt);

	if (flag != 0)
		return flag;

	bool done = false;
	bool desenhar = true;
	bool acoes[2] = {false, false};
	bool escolher = false;
	int escolha;
	int cont = 0;
	Dialogo dialogo = dialogos.array[cont];
	Personagem perso = personagens.array[dialogo.idPersonagem];
	Escolha escolhas;

	// para escolhas
	float height = HEIGHT / 3;

	float escolha1[4] = { 100, 50, WIDTH - 100, height - 50 };
	float escolha2[4] = { 100, height + 50, WIDTH - 100, height * 2 - 50 };
	float escolha3[4] = { 100, height * 2 + 50, WIDTH - 100, height * 3 - 50 };

	ALLEGRO_BITMAP* image = loadImage(perso.imagem);

	while (!done && dialogos.size > cont) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro.eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;

			if (escolher && acoes[CLICOU]) {
				if (escolha == escolhas.certa) {
					escolher = false;
				}

				acoes[CLICOU] = false;
			}
			else if (acoes[PROXIMO] && dialogos.size > ++cont) {
				if (dialogo.idEscolha != 0 && !escolher) {
					escolher = true;
					escolhas = escolhasTxt.array[dialogo.idEscolha - 1];
				}
				else {
					dialogo = dialogos.array[cont];
					perso = personagens.array[dialogo.idPersonagem];
					image = loadImage(perso.imagem);
					acoes[PROXIMO] = false;
				}
			}

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // quando clicar no X do display
			al_destroy_bitmap(image); 
			return 1;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
			case ALLEGRO_KEY_ENTER:
				if (!escolher)
					acoes[PROXIMO] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.button & 1) {
				if (!escolher) {
					acoes[PROXIMO] = true;
				}
				else {
					if (
						ev.mouse.x > escolha1[0] && ev.mouse.x < escolha1[2] &&
						ev.mouse.y > escolha1[1] && ev.mouse.y < escolha1[3]
					) {
						escolha = 1;
					}
					else if (
						ev.mouse.x > escolha2[0] && ev.mouse.x < escolha2[2] &&
						ev.mouse.y > escolha2[1] && ev.mouse.y < escolha2[3]
					) {
						escolha = 2;
					}
					else if (
						ev.mouse.x > escolha3[0] && ev.mouse.x < escolha3[2] &&
						ev.mouse.y > escolha3[1] && ev.mouse.y < escolha3[3]
					) {
						escolha = 3;
					}

					acoes[CLICOU] = true;
				}
			}
		}

		if (desenhar && al_is_event_queue_empty(allegro.eventQueue)) { // desenhar somente quando tiver frames

			desenhar = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (!escolher) {
				float heightMenu = HEIGHT / 3 * 2.15;

				if (image != NULL)
					al_draw_bitmap(
						image,
						(WIDTH - strlen(perso.nome) - al_get_bitmap_width(image)) * dialogo.posicao,
						heightMenu - al_get_bitmap_height(image),
						dialogo.posicao
					);

				// retangulo dialogo
				al_draw_filled_rectangle(0, heightMenu, WIDTH, HEIGHT, al_map_rgb(120, 120, 120));

				// retangulo nome
				al_draw_filled_rectangle(
					(WIDTH - strlen(perso.nome) * 30) * dialogo.posicao,
					heightMenu,
					dialogo.posicao ? WIDTH : strlen(perso.nome) * 30,
					heightMenu + al_get_font_line_height(allegro.font[r30]) * 1.5,
					al_map_rgb(200, 0, 0)
				);

				// texto nome
				al_draw_multiline_text(
					allegro.font[r24], al_map_rgb(255, 255, 255),
					dialogo.posicao ? WIDTH - strlen(perso.nome) * 30 + 25 : 50,
					heightMenu + 10,
					WIDTH + 50 * (dialogo.posicao - 1),
					al_get_font_line_height(allegro.font[r30]) + 10,
					0,
					perso.nome
				);

				// texto fala
				al_draw_multiline_text(
					allegro.font[r24], al_map_rgb(255, 255, 255),
					dialogo.posicao ? WIDTH - 50 : 50,
					heightMenu + al_get_font_line_height(allegro.font[r30]) * 2.5,
					WIDTH - 50,
					al_get_font_line_height(allegro.font[r24]) + 10,
					dialogo.posicao ? ALLEGRO_ALIGN_RIGHT : ALLEGRO_ALIGN_LEFT,
					dialogo.fala
				);
			}
			else {

				al_draw_filled_rectangle(escolha1[0], escolha1[1], escolha1[2], escolha1[3], al_map_rgb(120, 120, 120));
				al_draw_filled_rectangle(escolha2[0], escolha2[1], escolha2[2], escolha2[3], al_map_rgb(120, 120, 120));
				al_draw_filled_rectangle(escolha3[0], escolha3[1], escolha3[2], escolha3[3], al_map_rgb(120, 120, 120));

				al_draw_multiline_text(
					allegro.font[r24], al_map_rgb(255, 255, 255),
					WIDTH / 2, (escolha1[1] + escolha1[3]) / 2, escolha1[2] - 20,
					al_get_font_line_height(allegro.font[r24]) + 10,
					ALLEGRO_ALIGN_CENTRE, escolhas.escolha[0]
				);

				al_draw_multiline_text(
					allegro.font[r24], al_map_rgb(255, 255, 255),
					WIDTH / 2, (escolha2[1] + escolha2[3]) / 2, escolha2[2] - 20,
					al_get_font_line_height(allegro.font[r24]) + 10,
					ALLEGRO_ALIGN_CENTRE, escolhas.escolha[1]
				);

				al_draw_multiline_text(
					allegro.font[r24], al_map_rgb(255, 255, 255),
					WIDTH / 2, (escolha3[1] + escolha3[3]) / 2, escolha3[2] - 20,
					al_get_font_line_height(allegro.font[r24]) + 10,
					ALLEGRO_ALIGN_CENTRE, escolhas.escolha[2]
				);
			}

			al_flip_display();
		}
	}

	al_destroy_bitmap(image);

	return 0;
}


ALLEGRO_BITMAP* loadImage(char* path) {
	return strcmp(path, "/") == 0 ? NULL : al_load_bitmap(path);
}

