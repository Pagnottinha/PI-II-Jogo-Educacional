#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "constantes.h"

enum POS {X, Y};
enum TYPE_BITMAP {WALKING};
enum WALKING {UP, DOWN, LEFT, RIGHT};

typedef struct {
	double POS[2];
	double velocidade;
	bool acoes[4];

	int maxFrame;
	int FrameAtual;
	int ContFrame;
	int frameDelay;
	int framePOS[2];
	int linhaAnimacao;
	int tipoAnimacao;

	ALLEGRO_BITMAP* sheets[1][4];
} Player, Inimigo;

void createSpriteSheet(int arraySize, char path[][41], char name[]);
void initPlayer(Player* player, ALLEGRO_DISPLAY* display);
void desenharPlayer(Player* player);
void andarPlayerCima(Player* player);
void andarPlayerBaixo(Player* player);
void andarPlayerEsqueda(Player* player);
void andarPlayerDireita(Player* player);