#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char escolha[3][50];
	int certa;
} Escolha;

typedef struct {
	Escolha array[50];
	int size;
	float caixas[3][4];
} Escolhas;

int pegarEscolhas(Escolhas* es);