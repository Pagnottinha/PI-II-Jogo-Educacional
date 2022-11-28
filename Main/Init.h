#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include "constantes.h"
#include "stdlib.h"
#include "time.h"
#include <stdio.h>
#include <string.h>

enum FONTSIZE {r24, r30, r60, r16, r20};

typedef struct {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font[NUM_FONTS];
	bool close;
	bool deuCerto;
	bool creditos;
} Allegro;

Allegro init();
bool deuCerto(Allegro* allegro);
void destroy(Allegro* allegro);