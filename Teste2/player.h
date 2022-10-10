#include <allegro5/allegro.h>
#include <stdbool.h>

enum IDS{PLAYER, ENEMY};

struct Enemie
{
	bool vida;

	int pos_x;
	int pos_y;
	int ID;
	int limiteX;
	int limiteY;
	int velocidade;
};

struct Player
{
	bool vida;

	int ID;
	int pos_x;
	int pos_y;
	int limiteX;
	int limiteY;
	int areaX;
	int areaY;
	int velocidade;
	double pontuacao;
};
