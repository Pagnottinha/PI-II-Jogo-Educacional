#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

enum POS {X, Y};

typedef struct {
	double POS[2];
	double velocidade;
	int direcao[2];

	int maxFrame;
	int FrameAtual;
	int ContFrame;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int dirAnimacao;
	int colAnimacao;

	ALLEGRO_BITMAP* image;
} Player, Inimigo;

void createSpriteSheet(int arraySize, char path[][41], char name[]);