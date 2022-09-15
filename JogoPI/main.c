#include <stdio.h>

int main(void) {
	int resposta = 0;
	do {
		printf("Digite o que você deseja abrir:\n");
		printf("1- Texto\n");
		printf("2- Desenhos\n");
		printf("3- KeybordInput\n");
		printf("4- Mouse\n");
		printf("5- Timing\n");
		printf("6- KeyboardInputWithTimer\n");
		printf("7- Prototipo\n");
		printf("Resposta: ");
		scanf_s("%d", &resposta);

		system("cls");

		switch (resposta)
		{
			case 0:
				printf("Saindo...\n");
				break;
			case 1:
				textos();
				break;
			case 2:
				desenhos();
				break;
			case 3:
				keybordInput();
				break;
			case 4:
				mouse();
				break;
			case 5:
				timing();
				break;
			case 6:
				keybordInputWithTimer();
				break;
			case 7:
				prototipo();
				break;
			default:
				printf("Nao tem essa escolha!\n");
				break;
		}

	} while (resposta != 0);
	
	return 0;
}