#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char escolha[3][50];
	int certa;
} Escolha;

typedef struct {
	Escolha array[50];
	int size;
} Escolhas;

void lerEscolhas(Escolhas es);
int pegarEscolhas(Escolhas* es);