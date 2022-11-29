#include "historia.h"

int historia(Allegro* allegro, char* pathDialogo) {
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

	Backgrounds bgs;
	flag = pegarBackgrounds(&bgs);

	if (flag != 0)
		return flag;

	bool done = false;
	bool desenhar = true;
	bool acoes[1] = {false};
	bool flagEscolher = false;
	int cont = 0;

	Dialogo dialogo = dialogos.array[cont];
	Personagem perso = personagens.array[dialogo.idPersonagem];

	Background BG;
	InitBackground(&BG, 0, 0, bgs.path[dialogo.idBackground]);

	ALLEGRO_BITMAP* image = loadImage(perso.imagem);

	while (!done && dialogos.size > cont && !allegro->close) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro->eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			if (acoes[PROXIMO]) {
				if (flagEscolher) {
					escolher(allegro, escolhasTxt, dialogo.idEscolha - 1, BG.image);
					flagEscolher = false;
				}
				else if (dialogos.size > ++cont) {
					dialogo = dialogos.array[cont];
					perso = personagens.array[dialogo.idPersonagem];

					if (image != NULL)
						al_destroy_bitmap(image);
					image = loadImage(perso.imagem);

					al_destroy_bitmap(BG.image);
					InitBackground(&BG, 0, 0, bgs.path[dialogo.idBackground]);

					if (dialogo.idEscolha != 0)
						flagEscolher = true;

					acoes[PROXIMO] = false;
				}
			}
			else {
				desenhar = true;
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // quando clicar no X do display
			allegro->close = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					acoes[PROXIMO] = true;
				break;
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.button & 1) {
				acoes[PROXIMO] = true;
			}
		}

		if (desenhar && al_is_event_queue_empty(allegro->eventQueue)) { // desenhar somente quando tiver frames

			desenhar = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			DrawBackground(BG);

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
				heightMenu + al_get_font_line_height(allegro->font[r30]) * 1.5,
				al_map_rgb(200, 0, 0)
			);

			// texto nome
			al_draw_multiline_text(
				allegro->font[r24], al_map_rgb(255, 255, 255),
				dialogo.posicao ? WIDTH - strlen(perso.nome) * 30 + 25 : 50,
				heightMenu + 10,
				WIDTH + 50 * (dialogo.posicao - 1),
				al_get_font_line_height(allegro->font[r30]) + 10,
				0,
				perso.nome
			);

			// texto fala
			al_draw_multiline_text(
				allegro->font[r24], al_map_rgb(255, 255, 255),
				dialogo.posicao ? WIDTH - 50 : 50,
				heightMenu + al_get_font_line_height(allegro->font[r30]) * 2.5,
				WIDTH - 50,
				al_get_font_line_height(allegro->font[r24]) + 10,
				dialogo.posicao ? ALLEGRO_ALIGN_RIGHT : ALLEGRO_ALIGN_LEFT,
				dialogo.fala
			);

			al_draw_text(allegro->font[r16], al_map_rgb(255, 255, 255), 1000, 690, 0, "APERTE ENTER PARA PULAR");
		

			al_flip_display();
		}
	}

	al_destroy_bitmap(image);
	al_destroy_bitmap(BG.image);

	return 0;
}

void escolher(Allegro* allegro, Escolhas escolhas, int id, ALLEGRO_BITMAP* background) {

	bool done = false;
	bool desenhar = true;
	bool acoes[4] = { false, false, false, false };
	int opcao = -1;
	int cont = 0;

	while (!done && !allegro->close) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro->eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;

			if (acoes[CONFIRMAR]) {
				acoes[CONFIRMAR] = false;

				if (opcao == escolhas.array[id].certa - 1) {
					al_set_system_mouse_cursor(allegro->display, 1);
					done = true;
				}
				else if (acoes[SELECIONAR]) {
					escolhas.desabilitado[opcao] = 1;
					escolhas.color[opcao] = al_map_rgb(200, 0, 0);
					al_set_system_mouse_cursor(allegro->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_UNAVAILABLE);
				}
			}
			else if (acoes[CIMA]) {
				acoes[CIMA] = false;
				acoes[SELECIONAR] = true;

				if (opcao < 0) {
					opcao = 0;
				}
				else if (opcao == 0) {
					opcao = 2;
				}
				else {
					opcao--;
				}
			}
			else if (acoes[BAIXO]) {
				acoes[BAIXO] = false;
				acoes[SELECIONAR] = true;

				if (opcao < 0) {
					opcao = 2;
				}
				else if (opcao == 2) {
					opcao = 0;
				}
				else {
					opcao++;
				}
			}
			else if (acoes[SELECIONAR]) {

				if (!escolhas.desabilitado[opcao]) {
					resetEscolhas(&escolhas);
					escolhas.color[opcao] = al_map_rgb(150, 150, 150);
				}
			}

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // quando clicar no X do display
			allegro->close = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ENTER:
				acoes[CONFIRMAR] = true;
				break;
			case ALLEGRO_KEY_UP:
				acoes[CIMA] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				acoes[BAIXO] = true;
				break;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES && escolher) {

			opcao = verificarHover(escolhas, ev.mouse);

			if (opcao >= 0) {
				acoes[SELECIONAR] = true;
				if (!escolhas.desabilitado[opcao]) {
					al_set_system_mouse_cursor(allegro->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				}
			}
			else {
				acoes[SELECIONAR] = false;
				resetEscolhas(&escolhas);
				al_set_system_mouse_cursor(allegro->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
			}


		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.button & 1) {
				acoes[CONFIRMAR] = true;
			}
		}

		if (desenhar && al_is_event_queue_empty(allegro->eventQueue)) { // desenhar somente quando tiver frames

			desenhar = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(background, 0, 0, 0);

			for (int i = 0; i < 3; i++) {
				float* box = escolhas.caixas[i];

				al_draw_filled_rectangle(box[0], box[1], box[2], box[3], escolhas.color[i]);

				al_draw_multiline_text(
					allegro->font[r24], al_map_rgb(255, 255, 255),
					WIDTH / 2, (box[1] + box[3]) / 2, box[2] - 20,
					al_get_font_line_height(allegro->font[r24]) + 10,
					ALLEGRO_ALIGN_CENTRE, escolhas.array[id].escolha[i]
				);
			}

			al_flip_display();

		}
	}

	return 0;
}

ALLEGRO_BITMAP* loadImage(char* path) {
	return strcmp(path, "/") == 0 ? NULL : al_load_bitmap(path);
}
