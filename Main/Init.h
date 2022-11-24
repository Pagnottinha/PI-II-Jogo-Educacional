#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include "constantes.h"
#include "stdlib.h"
#include "time.h"

enum FONTSIZE {a24};

typedef struct {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font[1];
	bool deuCerto;
} Allegro;

Allegro init();
bool deuCerto(Allegro* allegro);
void destroy(Allegro* allegro);