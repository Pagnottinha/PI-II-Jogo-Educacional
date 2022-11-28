#include "dialogos.h"
#include <stdio.h>

int pegarDialogos(Dialogos* ds, char* path) {
	FILE *dialogos = fopen(path, "r");
	
	if (dialogos == NULL) {
		printf("Erro ao abrir o dialogos!\n");
		return -1;
	}

	ds->size = 0;

	do {
		Dialogo d;	
		
		int read = fscanf(dialogos,"%d %d %d %d %[^\n]s", &d.idPersonagem, &d.posicao, &d.idEscolha, &d.idBackground, d.fala);

		if (read == 5) {
			ds->array[ds->size] = d;
			ds->size++;	
		}
		else if (!feof(dialogos)) {
			printf("Arquivo dialogos.txt incorreto!\n");
			return 1;
		}
		else if (ferror(dialogos)) {
			printf("Erro ao ler dialogos.txt\n");
			return 1;
		}
	} while (!feof(dialogos));
	
	fclose(dialogos);
	
	return 0;
}