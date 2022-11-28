#include "init.h"

Allegro init() {
	Allegro allegro;
	allegro.deuCerto = false;

	al_set_app_name("Ilíada");

	if (al_init()) {

		allegro.display = al_create_display(WIDTH, HEIGHT);
		allegro.eventQueue = al_create_event_queue();
		allegro.timer = al_create_timer(1.0 / FPS);

		if (deuCerto(&allegro)) {
			srand(time(NULL));

			allegro.deuCerto = true;
			allegro.close = false;
			al_set_window_title(allegro.display, "Iliada");

			al_init_font_addon();
			al_init_ttf_addon();

			allegro.font[r24] = al_load_font("./Fontes PI/Fonte Roman/Roman SD.ttf", 24, 0);
			allegro.font[r30] = al_load_font("./Fontes PI/Fonte Roman/Roman SD.ttf", 30, 0);
			allegro.font[r60] = al_load_font("./Fontes PI/Fonte Roman/Roman SD.ttf", 60, 0);
			allegro.font[r16] = al_load_font("./Fontes PI/Fonte Roman/Roman SD.ttf", 16, 0);
			allegro.font[r20] = al_load_font("./Fontes PI/Fonte Roman/Roman SD.ttf", 20, 0);


			al_install_keyboard();
			al_install_mouse();
			al_init_image_addon();
			al_init_primitives_addon();

			al_register_event_source(allegro.eventQueue, al_get_keyboard_event_source());
			al_register_event_source(allegro.eventQueue, al_get_mouse_event_source());
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