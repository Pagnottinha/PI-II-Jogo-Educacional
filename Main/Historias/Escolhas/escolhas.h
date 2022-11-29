#define _CRT_SECURE_NO_WARNINGS
#include <allegro5/allegro.h>

enum ACOES_ESCOLHAS { SELECIONAR, CIMA, BAIXO, CONFIRMAR, CLICOU };

typedef struct {
	char escolha[3][50];
	int certa;
} Escolha;

typedef struct {
	Escolha array[50];
	int size;
	float caixas[3][4];
	ALLEGRO_COLOR color[3];
	int desabilitado[3];
} Escolhas;

int pegarEscolhas(Escolhas* es);
void resetEscolhas(Escolhas* escolhas);
int verificarHover(Escolhas escolhas, ALLEGRO_MOUSE_EVENT mouse);