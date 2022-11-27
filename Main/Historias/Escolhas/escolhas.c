#include "escolhas.h"
#include <stdio.h>
#include "../../constantes.h"

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

	float height = HEIGHT / 3;

	for (int i = 0; i < 3; i++) {
		es->caixas[i][0] = 100; //{100, height 50, WIDTH - 100, height - 50};
		es->caixas[i][1] = height * i + 50;
		es->caixas[i][2] = WIDTH - 100;
		es->caixas[i][3] = height * (i + 1) - 50;
	}

	return 0;
}