#include "init.h"

Allegro* init() {

	if (!al_init()) {
		return NULL;
	}

	Allegro allegro;
	allegro.display = al_create_display(WIDTH, HEIGHT);
	allegro.eventQueue = al_create_event_queue();
	allegro.timer = al_create_timer(1.0 / FPS);

	if (deuCerto(&allegro)) {
		al_install_keyboard();
		al_init_image_addon();

		al_register_event_source(allegro.eventQueue, al_get_keyboard_event_source());
		al_register_event_source(allegro.eventQueue, al_get_display_event_source(allegro.display));
		al_register_event_source(allegro.eventQueue, al_get_timer_event_source(allegro.timer));

		al_start_timer(allegro.timer);

		return &allegro;
	}
	else {
		return NULL;
	}
}
bool deuCerto(Allegro* allegro) {
	return allegro->display != NULL && allegro->eventQueue != NULL && allegro->timer != NULL;
}

void destroy(Allegro* allegro) {
	al_destroy_display(allegro->display);
	al_destroy_event_queue(allegro->eventQueue);
	al_destroy_timer(allegro->timer);
}