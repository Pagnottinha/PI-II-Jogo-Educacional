#include "game.h"

int main(void) {

	Allegro allegro = init();

	if (!allegro.deuCerto)
		return -1;

	int resultado;

	resultado = loadMenu(allegro);

	if (resultado)
		return resultado;

	if (resultado == 2)
		Tutorial(allegro);


	resultado = historia(allegro, "./Historias/Dialogos/dialogo1.txt");

	if (resultado)
		return resultado;

	resultado = historia(allegro, "./Historias/Dialogos/dialogo2.txt");

	if (resultado)
		return resultado;

	do {
		resultado = batalha(allegro);
	} while (resultado);

	destroy(&allegro);

	return 0;
}