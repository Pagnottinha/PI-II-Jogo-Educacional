#include "Batalha/Batalha.h"
#include <stdio.h>
#include <string.h>

int main(void) {

	Allegro allegro = init();

	if (!allegro.deuCerto)
		return -1;

	int resultado;

	do {
		resultado = batalha(allegro);
	} while (resultado);

	destroy(&allegro);

	return 0;
}