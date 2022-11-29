#include "../game.h"
#include "./Dialogos/dialogos.h"
#include "./Personagens/personagens.h"
#include "./Escolhas/escolhas.h"
#include "./Background/BackgroundDialogo.h"

enum ACOES { PROXIMO };

ALLEGRO_BITMAP* loadImage(char* path);
void escolher(Allegro* allegro, Escolhas escolhas, int id, ALLEGRO_BITMAP* background);