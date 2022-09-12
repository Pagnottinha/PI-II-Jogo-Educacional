#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5\allegro.h>
#include <allegro5/allegro_native_dialog.h>

int textos(void) {
	int width = 640;
	int height = 480;

	ALLEGRO_DISPLAY* display = NULL;

	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, "failed to initialize allegro!", NULL, NULL, NULL);
		return -1;
	}

	display = al_create_display(width, height);

	if (!display) {
		al_show_native_message_box(NULL, NULL, "failed to initialize display!", NULL, NULL, NULL);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font24 = al_load_font("./Fontes/Arial/ARIAL.TTF", 24, 0);
	ALLEGRO_FONT* font36 = al_load_font("./Fontes/Arial/ARIAL.TTF", 36, 0);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_text(font24, al_map_rgb(255, 0, 0), 50, 50, 0, "TESTEEEEEE");
	al_draw_text(font24, al_map_rgb(160, 20, 200), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "TESTEEEEEE 2");

	al_flip_display();

	al_rest(5.0);

	al_destroy_display(display);

	return 0;
}