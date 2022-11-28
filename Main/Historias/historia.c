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
	bool acoes[5] = {false, false, false, false, false};
	bool escolher = false;
	bool acertou = false;
	int opcao = -1;
	int cont = 0;

	Dialogo dialogo = dialogos.array[cont];
	Personagem perso = personagens.array[dialogo.idPersonagem];
	Escolha escolhas;

	Background BG;
	BG.image = al_load_bitmap(bgs.path[dialogo.idBackground]);
	InitBackground(&BG, 0, 0, bgs.path[dialogo.idBackground]);

	ALLEGRO_BITMAP* image = loadImage(perso.imagem);

	while (!done && dialogos.size > cont) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro->eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;

			if (acoes[PROXIMO]) {
				if (dialogo.idEscolha != 0 && !escolher && !acertou) {
					escolher = true;
					escolhas = escolhasTxt.array[dialogo.idEscolha - 1];
					opcao = -1;
					resetEscolhas(&escolhasTxt);
				}
				else if (dialogos.size > ++cont) {
					dialogo = dialogos.array[cont];
					perso = personagens.array[dialogo.idPersonagem];

					if (image != NULL)
						al_destroy_bitmap(image);
					image = loadImage(perso.imagem);

					InitBackground(&BG, 0, 0, bgs.path[dialogo.idBackground]);
					acoes[PROXIMO] = false;
					acertou = false;
				}
			}
			else if (acoes[CONFIRMAR]) {
				acoes[CONFIRMAR] = false;

				if (opcao == escolhas.certa - 1) {
					escolher = false;
					acertou = true;
					al_set_system_mouse_cursor(allegro->display, 1);
					acoes[SELECIONAR] = false;
				}
				else if (acoes[SELECIONAR]) {
					escolhasTxt.desabilitado[opcao] = 1;
					escolhasTxt.color[opcao] = al_map_rgb(200, 0, 0);
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

				if (!escolhasTxt.desabilitado[opcao]) {
					resetEscolhas(&escolhasTxt);
					escolhasTxt.color[opcao] = al_map_rgb(150, 150, 150);
				}
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // quando clicar no X do display
			done = true;
			allegro->close = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (!escolher) {
				switch (ev.keyboard.keycode) {
					case ALLEGRO_KEY_ENTER:
						acoes[PROXIMO] = true;
					break;
				}
			}
			else {
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
			
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES && escolher) {

			opcao = verificarHover(escolhasTxt, ev.mouse);

			if (opcao >= 0) {
				acoes[SELECIONAR] = true;
				if (!escolhasTxt.desabilitado[opcao]) {
					al_set_system_mouse_cursor(allegro->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				}
			}
			else {
				acoes[SELECIONAR] = false;
				resetEscolhas(&escolhasTxt);
				al_set_system_mouse_cursor(allegro->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
			}


		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.button & 1) {
				if (!escolher) {
					acoes[PROXIMO] = true;
				}
				else {
					acoes[CONFIRMAR] = true;
				}
			}
		}

		if (desenhar && al_is_event_queue_empty(allegro->eventQueue)) { // desenhar somente quando tiver frames

			desenhar = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			DrawBackground(BG);

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
			}
			else {

				for (int i = 0; i < 3; i++) {
					float* box = escolhasTxt.caixas[i];

					al_draw_filled_rectangle(box[0], box[1], box[2], box[3], escolhasTxt.color[i]);

					al_draw_multiline_text(
						allegro->font[r24], al_map_rgb(255, 255, 255),
						WIDTH / 2, (box[1] + box[3]) / 2, box[2] - 20,
						al_get_font_line_height(allegro->font[r24]) + 10,
						ALLEGRO_ALIGN_CENTRE, escolhas.escolha[i]
					);
				}
			}

			al_flip_display();
		}
	}

	al_destroy_bitmap(image);
	al_destroy_bitmap(BG.image);

	return 0;
}


ALLEGRO_BITMAP* loadImage(char* path) {
	return strcmp(path, "/") == 0 ? NULL : al_load_bitmap(path);
}

