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
	ALLEGRO_BITMAP* image = loadImage(personagens.array[dialogos.array[cont].idPersonagem].imagem);

	while (!done && dialogos.size - 1 >= cont) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro.eventQueue, &ev); // esperar evento

		if (ev.type == ALLEGRO_EVENT_TIMER) { // quando der um frame do jogo

			desenhar = true;

			if (acoes[PROXIMO]) {
				cont++;
				if (dialogos.size - 1 >= cont)
					image = loadImage(personagens.array[dialogos.array[cont].idPersonagem].imagem);
				acoes[PROXIMO] = false;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // quando clicar no X do display
			return -1;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ENTER:
				acoes[PROXIMO] = true;
				break;
			}
		}

		if (desenhar && al_is_event_queue_empty(allegro.eventQueue)) { // desenhar somente quando tiver frames

			desenhar = false;

			if (image != NULL)
				al_draw_bitmap(image, 0, 0, 0);

			al_draw_text(allegro.font[a24], al_map_rgb(255, 255, 255), 0, 0, 0, dialogos.array[cont].fala);

			al_flip_display();

			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_bitmap(image);

	return 0;
}