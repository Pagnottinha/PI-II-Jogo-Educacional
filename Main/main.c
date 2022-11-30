#include "game.h"

int main(void) {

	Allegro allegro = init();

	if (!allegro.deuCerto)
		return -1;

	int resultado;
	int cont = 0;

	//GameOver(&allegro);

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
			do {
				resultado = tutorial(&allegro);
			} while (resultado && !allegro.close);
			break;
		case 3:
			resultado = historia(&allegro, "./Historias/Dialogos/dialogo2.txt");
			break;
		case 4:
			do {
				resultado = batalha(&allegro);

				if (resultado) {
					GameOver(&allegro);
					resultado = 1;
				}

			} while (resultado && !allegro.close && !allegro.menu);
			break;
		case 5:
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

		if (allegro.menu) {
			allegro.menu = false;
			cont = 0;
		}

	} while (!allegro.close && resultado == 0);
	
	destroy(&allegro);

	return resultado;
}