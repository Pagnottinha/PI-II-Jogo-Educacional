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
	int width;
	int height;

	ALLEGRO_BITMAP* backgroundMenu;
} BackgroundMenu;

void InitBackgroundMenu(BackgroundMenu* BG, float x, float y, int width, int height, char* imagePath);
void DrawnBackMenu(BackgroundMenu BG);