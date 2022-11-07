#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "constantes.h"

enum POS {X, Y};
enum TYPE_BITMAP {CORRENDO, ATACANDO, IDLE};
enum DIRECOES {UP, DOWN, LEFT, RIGHT};
enum ANIMACAO {DIREITA, ESQUERDA};

typedef struct {
	double POS[2];
	double velocidade;
	bool acoes[QNT_ACOES];

	int maxFrame[NUM_SPRITES];
	int FrameAtual;
	int ContFrame;
	int frameDelay;
	int dimensoesFrame[2];
	int dimensoesLanca[2];
	int linhaAnimacao;
	int tipoAnimacao;

	ALLEGRO_BITMAP* sheets[NUM_SPRITES];
} Player, Inimigo;

// SPRITES
void createSpriteSheet(char path[][NUM_PATH], char name[]);
void juntarSpriteSheets(char path[][NUM_PATH], char name[]);

// PLAYER
void initPlayer(Player* player, ALLEGRO_DISPLAY* display);
void desenharPlayer(Player* player);
void andarPlayerCima(Player* player);
void andarPlayerBaixo(Player* player);
void andarPlayerEsqueda(Player* player);
void andarPlayerDireita(Player* player);