#include <allegro5\allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

enum KEYS { UP, DOWN, LEFT, RIGHT };
enum POS {X, Y};

int keybordInput(void) {
	int width = 640;
	int height = 480;

	int moviment = 5;
	bool done = false;
	int pos[2] = { width / 2 -30, height / 2 -30 };

	bool keys[4] = {false, false, false, false};

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
	al_install_keyboard();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	while (!done) {
		ALLEGRO_EVENT ev;

		al_draw_filled_rectangle(pos[X], pos[Y], pos[X] + 30, pos[Y] + 30, al_map_rgb(255, 0, 0));

		al_flip_display();

		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_W:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_A:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
				case ALLEGRO_KEY_D:
					keys[RIGHT] = true;
					break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_W:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_A:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
				case ALLEGRO_KEY_D:
					keys[RIGHT] = false;
					break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}

		if (pos[X] < 0 || pos[X] + 30> width || pos[Y] < 0 || pos[Y] + 30 > height) {
			done = true;
		}

		pos[Y] -= keys[UP] * moviment;
		pos[Y] += keys[DOWN] * moviment;
		pos[X] -= keys[LEFT] * moviment;
		pos[X] += keys[RIGHT] * moviment;

	}

	al_destroy_display(display);

	return 0;
}