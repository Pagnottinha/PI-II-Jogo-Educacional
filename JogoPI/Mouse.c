#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

int mouse(void) {
	int width = 640;
	int height = 480;

	bool done = false;
	bool draw = true;

	int pos_x = width / 2;
	int pos_y = height / 2;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

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
	al_install_mouse();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_hide_mouse_cursor(display);

	while (!done) {
		ALLEGRO_EVENT ev;

		if (draw) {
			al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 0));
		}
		
		al_flip_display();

		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.button & 2) {
				done = true;
			}
			else if (ev.mouse.button & 1) {
				draw = !draw;
			}
		}
	}

	al_destroy_display(display);

	return 0;
}