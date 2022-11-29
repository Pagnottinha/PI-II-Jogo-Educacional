#include <allegro5/allegro.h>

typedef struct {
	int posX;
	int posY;
	bool hover;
	bool acao;

	ALLEGRO_BITMAP* botaoImage;
	ALLEGRO_BITMAP* botaoHover;
} Botao;