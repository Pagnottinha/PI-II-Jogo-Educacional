#include "allegro5/allegro.h"

enum ACOES {CLICOU};

typedef struct {
	int posX;
	int posY;
	bool hover;
	bool acao;

	ALLEGRO_BITMAP* botaoImage;
	ALLEGRO_BITMAP* botaoHover;
} Botao;

typedef struct {
	int X;
	int Y;

	ALLEGRO_BITMAP* backgroundMenu;
} BackgroundMenu;

void DrawnMenu(Botao* botao);