#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "constantes.h"

typedef struct Allegro {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
} Allegro;

Allegro* init();
bool deuCerto(Allegro* allegro);
void destroy(Allegro* allegro);