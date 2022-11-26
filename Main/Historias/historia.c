#include "../game.h"
#include "./Dialogos/dialogos.h"
#include "./Personagens/personagens.h"

enum ACOES {PROXIMO};

ALLEGRO_BITMAP* loadImage(char* path) {
	return strcmp(path, "/") == 0 ? NULL : al_load_bitmap(path);
}

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

	bool done = false;
	bool desenhar = true;
	bool acoes[1] = {false};
	int cont = 0;
	Dialogo dialogo = dialogos.array[cont];
	Personagem perso = personagens.array[dialogo.idPersonagem];

	ALLEGRO_BITMAP* image = loadImage(perso.imagem);

	while (!done && dialogos.size > cont) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro.eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;

			if (acoes[PROXIMO] && dialogos.size > ++cont) {
				dialogo = dialogos.array[cont];
				perso = personagens.array[dialogo.idPersonagem];
				image = loadImage(perso.imagem);
				acoes[PROXIMO] = false;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // quando clicar no X do display
			al_destroy_bitmap(image); 
			return 1;
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

		if (desenhar && al_is_event_queue_empty(allegro.eventQueue)) { // desenhar somente quando tiver frames

			desenhar = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			float height = HEIGHT / 3 * 2.15;

			if (image != NULL)
				al_draw_bitmap(
					image, 
					(WIDTH - strlen(perso.nome) - al_get_bitmap_width(image)) * dialogo.posicao,
					height - al_get_bitmap_height(image), 
					dialogo.posicao
				);

			// retangulo dialogo
			al_draw_filled_rectangle(0, height, WIDTH, HEIGHT, al_map_rgb(120, 120, 120));

			// retangulo nome
			al_draw_filled_rectangle(
				(WIDTH - strlen(perso.nome) * 30) * dialogo.posicao, 
				height, 
				dialogo.posicao ? WIDTH : strlen(perso.nome) * 30, 
				height + al_get_font_line_height(allegro.font[r30]) * 1.5 , 
				al_map_rgb(200, 0, 0)
			);

			// texto nome
			al_draw_multiline_text(
				allegro.font[r24], al_map_rgb(255, 255, 255), 
				dialogo.posicao ? WIDTH - strlen(perso.nome) * 30 + 25 : 50,
				height + 10, 
				WIDTH + 50 * (dialogo.posicao - 1),
				al_get_font_line_height(allegro.font[r30]) + 10, 
				0, 
				perso.nome
			);
			
			// texto fala
			al_draw_multiline_text(
				allegro.font[r24], al_map_rgb(255, 255, 255), 
				dialogo.posicao ? WIDTH - 50 : 50,
				height + al_get_font_line_height(allegro.font[r30]) * 2.5,
				WIDTH - 50,
				al_get_font_line_height(allegro.font[r24]) + 10, 
				dialogo.posicao ? ALLEGRO_ALIGN_RIGHT : ALLEGRO_ALIGN_LEFT, 
				dialogo.fala
			);

			al_flip_display();
		}
	}

	al_destroy_bitmap(image);

	return 0;
}