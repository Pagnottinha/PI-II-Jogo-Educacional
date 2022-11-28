#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	int idPersonagem;
	char fala[150];
	int posicao;
	int idEscolha;
	int idBackground;
} Dialogo;

typedef struct {
	Dialogo array[20];
	int size;
} Dialogos;

int pegarDialogos(Dialogos* ds, char* path);