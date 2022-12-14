#include "personagens.h"
#include <stdio.h>


int pegarPersonagens(Personagens* ps) {
	FILE *personagens = fopen("./Historias/Personagens/personagens.txt", "r");

	if(personagens == NULL) {
		printf("Erro ao abrir os personagens!\n");
		return -1;
	}

	ps->size = 0;

	do {
		Personagem p;
		
		int read = fscanf(personagens,"%s %[^\n]s", p.nome, p.imagem);

		if (read == 2) {
			ps->array[ps->size] = p;
			ps->size++;	
		}
		else if (!feof(personagens)) {
			printf("Arquivo personagens.txt incorreto!\n");
			return 1;
		}
		else if (ferror(personagens)) {
			printf("Erro ao ler personagens.txt\n");
			return 1;
		}
	} while (!feof(personagens));

	fclose(personagens);
	
	return 0;
}