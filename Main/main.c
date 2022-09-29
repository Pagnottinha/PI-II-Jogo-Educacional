#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#define FPS 60
#define WIDTH 800
#define HEIGHT 800


int main(void) {
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* eventQueue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if (!display)
		return 0;

	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_install_keyboard();
	al_init_image_addon();

	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);

	return 0;
}