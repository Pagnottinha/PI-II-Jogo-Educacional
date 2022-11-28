#include "BackgroundDialogo.h"

int pegarBackgrounds(Backgrounds* back) {
	FILE* backgrounds = fopen("./Historias/Background/Backgrounds.txt", "r");

	if (backgrounds == NULL) {
		printf("Erro ao abrir os backgrounds\n");
		return 1;
	}

	back->size = 0;

	do {
		char path[50];

		int read = fscanf(backgrounds, "%s\n", path);

		if (read == 1) {
			strcpy(back->path[back->size], path);
			back->size++;
		}
		else if (!feof(backgrounds)) {
			printf("Arquivo backgrounds.txt incorreto!\n");
			return 1;
		}
		else if (ferror(backgrounds)) {
			printf("Erro ao ler backgrounds.txt\n");
			return 1;
		}
	} while (!feof(backgrounds));

	fclose(backgrounds);

	Background background = {0, 0, 0, 0, NULL};

	back->background = background;
	
	return 0;
}