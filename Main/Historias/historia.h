#include "../game.h"
#include "./Dialogos/dialogos.h"
#include "./Personagens/personagens.h"
#include "./Escolhas/escolhas.h"

enum ACOES { PROXIMO, CLICOU};

ALLEGRO_BITMAP* loadImage(char* path);