#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char nome[20];
	char imagem[50];
} Personagem;

typedef struct {
	Personagem array[7];
	int size;
} Personagens;

int pegarPersonagens(Personagens* ps);