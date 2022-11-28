#include "game.h"

int main(void) {

	Allegro allegro = init();

	if (!allegro.deuCerto)
		return -1;

	int resultado;
	int cont = 0;

	allegro.creditos = false;

	do {
		switch (cont) {
		case 0:
			resultado = loadMenu(&allegro);
			if (allegro.creditos)
				cont = 5;
			break;
		case 1:
			resultado = historia(&allegro, "./Historias/Dialogos/dialogo1.txt");
			break;
		case 2:
			resultado = historia(&allegro, "./Historias/Dialogos/dialogo2.txt");
			break;
		case 3:
			do {
				resultado = batalha(&allegro);
			} while (resultado && !allegro.close);
			break;
		case 4:
			resultado = historia(&allegro, "./Historias/Dialogos/dialogoFinal.txt");
			break;
		case 6:
			resultado = InitCreditos(&allegro);
			allegro.creditos = false;
			break;
		default:
			cont = -1;
			break;
		}

		cont++;

	} while (!allegro.close && resultado == 0);
	
	destroy(&allegro);

	return resultado;
}