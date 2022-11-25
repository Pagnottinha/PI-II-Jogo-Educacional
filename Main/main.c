#include "game.h"

int main(void) {

	Allegro allegro = init();

	if (!allegro.deuCerto)
		return -1;

	int resultado;

	resultado = historia(allegro, "./Historias/Dialogos/dialogo1.txt");

	if (resultado)
		return resultado;

	do {
		resultado = batalha(allegro);
	} while (resultado);

	destroy(&allegro);

	return 0;
}