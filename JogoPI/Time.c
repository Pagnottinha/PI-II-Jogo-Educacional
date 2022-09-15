#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>

int timing(void) {
	int width = 640;
	int height = 480;

	int counter = 0;
	bool done = false;
	int FPS = 60;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, "failed to initialize allegro!", NULL, NULL, NULL);
		return -1;
	}

	display = al_create_display(width, height);

	if (!display) {
		al_show_native_message_box(NULL, NULL, "failed to initialize display!", NULL, NULL, NULL);
		return -1;
	}

	al_init_ttf_addon();
	al_init_font_addon();
	event_queue = al_create_event_queue();

	ALLEGRO_FONT* font24 = al_load_font("./Fontes/Arial/ARIAL.TTF", 24, 0);

	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		counter++;

		al_draw_textf(font24, al_map_rgb(255, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "Frames: %i", counter);

		al_flip_display();

		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_display(display);

	return 0;
}