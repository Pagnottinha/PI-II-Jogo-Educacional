#include "../game.h"
#include "./Dialogos/dialogos.h"
#include "./Personagens/personagens.h"
#include "./Escolhas/escolhas.h"
#include "./Background/BackgroundDialogo.h"

enum ACOES { PROXIMO, SELECIONAR, CIMA, BAIXO, CONFIRMAR };

ALLEGRO_BITMAP* loadImage(char* path);