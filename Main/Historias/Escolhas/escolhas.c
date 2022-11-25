#include "escolhas.h"
#include <stdio.h>

void lerEscolhas(Escolhas es) {
	for (int i = 0; i < es.size; i++) {
		Escolha e = es.array[i];
		printf("%d:\n", i);
		printf("%d - %s\n", 1, e.escolha[0]);
		printf("%d - %s\n", 2, e.escolha[1]);
		printf("%d - %s\n", 3, e.escolha[2]);
		printf("Certa: %d\n\n", e.certa);
	}
}

int pegarEscolhas(Escolhas* es) {
	FILE *escolhas = fopen("./Historias/Escolhas/escolhas.txt", "r");

	if (escolhas == NULL) {
		printf("Erro ao abrir as escolhas\n");
		return 1;
	}
	
	es->size = 0;
	
	do {
		Escolha e;
		
		int read = fscanf(escolhas,"%50[^|]| %50[^|]| %50[^|]| %d\n", e.escolha[0], e.escolha[1], e.escolha[2], &e.certa);
		
		if (read == 4) {
			es->array[es->size] = e;
			es->size++;	
		}
		else if (!feof(escolhas)) {
			printf("Arquivo escolhas.txt incorreto!\n");
			return 1;
		}
		else if (ferror(escolhas)) {
			printf("Erro ao ler escolhas.txt\n");
			return 1;
		}
	} while(!feof(escolhas));

	fclose(escolhas);

	return 0;
}