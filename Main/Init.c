#include "init.h"

Allegro init() {
	Allegro allegro;
	allegro.deuCerto = false;

	if (al_init()) {

		allegro.display = al_create_display(WIDTH, HEIGHT);
		allegro.eventQueue = al_create_event_queue();
		allegro.timer = al_create_timer(1.0 / FPS);

		if (deuCerto(&allegro)) {
			srand(time(NULL));

			allegro.deuCerto = true;

			al_init_font_addon();
			al_init_ttf_addon();

			allegro.font[a24] = al_load_font("arial.ttf", 24, 0);

			al_install_keyboard();
			al_init_image_addon();
			al_init_primitives_addon();

			al_register_event_source(allegro.eventQueue, al_get_keyboard_event_source());
			al_register_event_source(allegro.eventQueue, al_get_display_event_source(allegro.display));
			al_register_event_source(allegro.eventQueue, al_get_timer_event_source(allegro.timer));

			al_start_timer(allegro.timer);
		}
	}

	return allegro;
}
bool deuCerto(Allegro* allegro) {
	return allegro->display != NULL && allegro->eventQueue != NULL && allegro->timer != NULL;
}

void destroy(Allegro* allegro) {
	al_destroy_display(allegro->display);
	al_destroy_event_queue(allegro->eventQueue);
	al_destroy_timer(allegro->timer);
	for (int i = 0; i < NUM_FONTS; i++)
		al_destroy_font(allegro->font[i]);
}