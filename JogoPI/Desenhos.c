#include <allegro5\allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

int desenhos(void) {
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

	al_init_primitives_addon();

	al_draw_filled_circle(width - 90, 90, 75, al_map_rgb(0, 255, 255), 2);
	al_draw_circle(width - 90, 90, 75, al_map_rgb(0, 0, 255), 5);

	al_draw_line(0, height - 150, width, height - 150, al_map_rgb(255, 255, 255), 5);
	al_draw_filled_rectangle(0, height - 150, width, height, al_map_rgb(20, 20, 20));

	al_flip_display();

	al_rest(5.0);

	al_destroy_display(display);

	return 0;
}