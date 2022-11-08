#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "constantes.h"
#include "stdlib.h"
#include "time.h"

typedef struct {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	bool deuCerto;
} Allegro;

Allegro init();
bool deuCerto(Allegro* allegro);
void destroy(Allegro* allegro);