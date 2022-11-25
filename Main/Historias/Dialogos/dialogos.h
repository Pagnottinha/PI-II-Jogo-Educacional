#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	int idPersonagem;
	char fala[100];
	int posicao;
	int idEscolha;
} Dialogo;

typedef struct {
	Dialogo array[100];
	int size;
} Dialogos;

void lerDialogos(Dialogos ds);
int pegarDialogos(Dialogos* ds, char* path);