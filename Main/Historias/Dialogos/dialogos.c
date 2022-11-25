#include "dialogos.h"
#include <stdio.h>

void lerDialogos(Dialogos ds) {
	for (int i =0; i < ds.size; i++) {
		Dialogo d = ds.array[i];
		printf("%d:\n", i);
		printf("Id: %d\n", d.idPersonagem);
		printf("Fala: %s\n\n", d.fala);
	}
}

int pegarDialogos(Dialogos* ds, char* path) {
	FILE *dialogos = fopen(path, "r");
	
	if (dialogos == NULL) {
		printf("Erro ao abrir o dialogos!\n");
		return -1;
	}

	ds->size = 0;

	do {
		Dialogo d;	
		
		int read = fscanf(dialogos,"%d %d %d %[^\n]s", &d.idPersonagem, &d.posicao, &d.idEscolha, d.fala);

		if (read == 4) {
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