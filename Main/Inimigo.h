#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "constantes.h"
#include "player.h"

typedef struct {
	bool vida;

	double POS[2];
	double velocidade;

	int maxFrame[NUM_SPRITES_ENEMIE];
	int FrameAtual;
	int ContFrame;
	int frameDelay;
	int dimensoesFrame[2];
	int linhaAnimacao;
	int tipoAnimacao;
	int hitboxEspada;
	int dimensoesEspada[2];
	int dano;

	ALLEGRO_BITMAP* sheets[NUM_SPRITES_ENEMIE];
} Enemie;

enum WAVES {MAX, QNT};

typedef struct {
	Enemie enemie[NUM_ENEMIES];
	int countEnemies;
	int enemieDeath;
	int waves[2];
} Enemies;

// Inimigo
void InitEnemie(Enemies* enemies);
void DrawEnemie(Enemies enemies);
void NewWave(Enemies* enemies);
void UpdateEnemie(Enemies* enemies, Player* player);
void ataqueEnemie(Enemie* enemie, Player* player);
bool enemieAtaca(Enemie* enemie, Player* player);
bool enemieAcertou(Enemie* enemie, Player* player);

void destroyBitmapsEnemie(Enemies* enemies);

// player ataque
void ataquePlayer(Player* player, Enemie* enemie);
bool playerAcertou(Player* player, Enemies* enemies);