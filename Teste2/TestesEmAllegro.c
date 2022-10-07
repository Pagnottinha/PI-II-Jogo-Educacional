/*
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro.h>
#include <allegro5/allegro_primitives.h>


ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
int width = 640;
int height = 480;

enum KEYS { UP, DOWN, LEFT, RIGHT };

void Geometria()
{
	if (!al_init())
	{
		return -1;
	}

	display = al_create_display(width, height);

	if (!display)
	{
		return -1;
	}

	al_init_primitives_addon();

	al_draw_circle(100, 100, 50, al_map_rgb(255, 0, 255), 7);
	al_draw_filled_circle(400, 400, 70, al_map_rgb(255, 255, 255));
	al_draw_ellipse(150, 100, 100, 50, al_map_rgb(127, 3, 34), 6);
	al_draw_filled_ellipse(400, 250, 100, 200, al_map_rgb(0, 255, 255));

	float points[] = { 0, 0, 400, 100, 50, 200, width, height };
	al_draw_spline(points, al_map_rgb(255, 0, 255), 1);

	float points2[] = { 0, height, 200, 100, 400, 200, width, height };
	al_draw_spline(points2, al_map_rgb(0, 255, 0), 3);


	al_flip_display();

	al_rest(5.0);

	al_destroy_display(display);

}


void Start()
{
	if (!al_init())
		return -1;

	display = al_create_display(width, height);

	if (!display)
		return -1;


	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font24 = al_load_font("arial.ttf", 24, 0);
	ALLEGRO_FONT* font36 = al_load_font("arial.ttf", 36, 0);
	ALLEGRO_FONT* font18 = al_load_font("arial.ttf", 18, 0);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_text(font24, al_map_rgb(255, 0, 255), 50, 50, 0, "Hello World, this is 24 point");
	al_draw_text(font36, al_map_rgb(255, 127, 127), width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "This is Centered and 36 point");
	al_draw_text(font18, al_map_rgb(15, 240, 18), 620, 350, ALLEGRO_ALIGN_RIGHT, "This is right aligned and 18 point");

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	al_draw_textf(font18, al_map_rgb(255, 255, 255), screen_w / 2, 400, ALLEGRO_ALIGN_CENTER, "Text with variable output (textf): Screen width and height = %i / %i", screen_w, screen_h);

	al_flip_display();

	al_rest(5.0);

	al_destroy_display(display);

}

void Input()
{
	bool done = false;
	int pos_x = width / 2;
	int pos_y = height / 2;

	bool keys[4] = { false, false, false, false };

	if (!al_init())
		return -1;


	display = al_create_display(width, height);

	if (!display)
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		pos_y -= keys[UP] * 10;
		pos_y += keys[DOWN] * 10;
		pos_x -= keys[LEFT] * 10;
		pos_x += keys[RIGHT] * 10;

		al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(0, 0, 255));
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}


	al_destroy_display(display);
}

void MouseInput()
{

	bool done = false;
	bool draw = true;
	int pos_x = width / 2;
	int pos_y = height / 2;

	if (!al_init())
		return -1;

	display = al_create_display(width, height);

	if (!display)
		return -1;

	al_init_primitives_addon();
	al_install_mouse();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_hide_mouse_cursor(display);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 2)
				done = true;
			else if (ev.mouse.button & 1)
				draw = !draw;
		}

		if (draw)
			al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(0, 0, 255));

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_display(display);
}

void Timing()
{

	bool done = false;
	int count = 0;

	int FPS = 60;

	if (!al_init())
		return -1;

	display = al_create_display(width, height);

	if (!display)
		return -1;

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font18 = al_load_font("arial.ttf", 18, 0);

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		count++;

		al_draw_textf(font18, al_map_rgb(255, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "Frames: %d", count);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_display(display);
}
*/
