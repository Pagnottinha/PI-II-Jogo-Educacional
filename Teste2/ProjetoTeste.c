#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#define NUM_ENEMIE 10

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
int width = 1000;
int height = 750;
int cont = 2;

enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};

void InitPlayer(struct Player *player);
void DrawnPlayer(struct Player *player);
void MovePlayerUp(struct Player *player);
void MovePlayerDown(struct Player *player);
void MovePlayerRight(struct Player *player);
void MovePlayerLeft(struct Player *player);

void InitEnemie(struct Enemie enemie[], int size);
void DrawEnemie(struct Enemie enemie[], int size);
void StartEnemie(struct Enemie enemie[], struct Player *player ,int size);
void UpdateEnemie(struct Enemie enemie[], struct Player *player, int size);


//void LookAtack(enum KEYS direcao, struct Player *player);

void InputTimer()
{
	bool done = false;
	bool redraw = true;

	int FPS = 60;

	struct Player player;
	struct Enemie enemie[NUM_ENEMIE];

	bool keys[5] = { false, false, false, false, false};

	if (!al_init())
		return -1;

	display = al_create_display(width, height);

	if (!display)
		return -1;


	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	
	srand(time(NULL));
	InitPlayer(&player);
	InitEnemie(enemie, cont);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	StartEnemie(enemie, &player ,cont);
	
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;

			if (keys[UP])
				MovePlayerUp(&player);
			if (keys[DOWN])
				MovePlayerDown(&player);
			if (keys[LEFT])
				MovePlayerLeft(&player);
			if (keys[RIGHT])
				MovePlayerRight(&player);

			UpdateEnemie(enemie, &player, cont);

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
			case ALLEGRO_KEY_W:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_S:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
			case ALLEGRO_KEY_D:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
			case ALLEGRO_KEY_A:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
			case ALLEGRO_KEY_W:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_S:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
			case ALLEGRO_KEY_D:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
			case ALLEGRO_KEY_A:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			DrawnPlayer(&player);
			DrawEnemie(enemie, cont);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));	
		}

	}

	al_destroy_display(display);
}

void InitPlayer(struct Player *player)
{
	player->ID = PLAYER;
	player->pos_x = width / 2;
	player->pos_y = height / 2;
	player->areaSpawnX = player->pos_x + 190;
	player->areaSpawnY = player->pos_y + 190;
	player->areaAtaqX = player->pos_x + 150;
	player->areaAtaqY = player->pos_y + 150;
	player->atackX = player->pos_x + 15;
	player->atackY = player->pos_y + 15;
	player->vida = true;
	player->velocidade = 5;
	player->limiteX = 6;
	player->limiteY = 7;
	player->pontuacao = 0;
}

void DrawnPlayer(struct Player *player)
{
	al_draw_filled_rectangle(player->pos_x, player->pos_y, player->pos_x + 30, player->pos_y + 30, al_map_rgb(0, 0, 255));
	//al_draw_line(player->atackX, player->areaAtaqY, player->atackX, player->atackY - 45, al_map_rgb(253, 239, 144), 2);
	al_draw_circle(player->pos_x + 15, player->pos_y + 15, 80, al_map_rgb(0, 255, 0), 2);
	al_draw_circle(player->pos_x + 15, player->pos_y + 15, 60, al_map_rgb(255, 255, 0), 2);
}

void MovePlayerUp(struct Player *player)
{
	player->pos_y -= player->velocidade;
	player->atackY -= 45;
	
	if (player->pos_y < 0)
		player->pos_y = 0;
	
	if (player->areaSpawnY < -95)
		player->areaSpawnY = -95;

	if (player->areaAtaqY < -75)
		player->areaAtaqY = -75;

	//LookAtack(UP, &player);
}

void MovePlayerDown(struct Player *player)
{
	player->pos_y += player->velocidade;
	player->atackY += 45;

	if (player->pos_y > height - 30)
		player->pos_y = height - 30;
	
	if (player->areaSpawnY > height - 95)
		player->areaSpawnY = height - 95;
	
	if (player->areaAtaqY > height - 75)
		player->areaAtaqY = height - 75;
	
	//LookAtack(DOWN, &player);
}

void MovePlayerRight(struct Player *player)
{
	player->pos_x += player->velocidade;
	player->atackX += 45;

	if (player->pos_x > width - 30)
		player->pos_x = width - 30;

	if (player->areaSpawnX > width - 95)
		player->areaSpawnX = width - 95;

	if (player->areaAtaqX > width - 75)
		player->areaAtaqX = width - 75;

	//LookAtack(RIGHT, &player);
}

void MovePlayerLeft(struct Player *player)
{
	player->pos_x -= player->velocidade;
	player->atackX -= 45;

	if (player->pos_x < 0)
		player->pos_x = 0;

	if (player->areaSpawnX < -95)
		player->areaSpawnX = -95;
	
	if (player->areaAtaqX < -75)
		player->areaAtaqX = -75;
	
	//LookAtack(LEFT, &player);
}

/*
void LookAtack(enum KEYS direcao, struct Player *player)
{
	if (direcao == UP)
	{
		player->atackY -= 45;
	}
	else if (direcao == DOWN)
	{
		player->atackY += 45;
	}
	else if (direcao == RIGHT)
	{
		player->atackX += 45;
	}
	else
	{
		player->atackX -= 45;
	}
}

*/



void InitEnemie(struct Enemie enemie[], int size)
{
	for (int i = 0; i < size; i++)
	{
		enemie[i].ID = ENEMY;
		enemie[i].vida = false;
		enemie[i].velocidade = 1;
		enemie[i].limiteX = 18;
		enemie[i].limiteY = 16;
	}
}

void DrawEnemie(struct Enemie enemie[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (enemie[i].vida)
		{
			al_draw_filled_rectangle(enemie[i].pos_x, enemie[i].pos_y, enemie[i].pos_x + 20, enemie[i].pos_y + 20, al_map_rgb(255, 0, 0));
		}		
	}
}

void StartEnemie(struct Enemie enemie[], struct Player *player ,int size)
{
	for (int i = 0; i < size; i++)
	{
		//if (!enemie[i].vida)
		//{
			//if (rand() % 500 == 0)
			//{
				enemie[i].vida = true;
				enemie[i].pos_x = rand() % (width - 40);
				enemie[i].pos_y = rand() % (height - 40);
				/*
					if (enemie[i].pos_x < 0)
					enemie[i].pos_x = 0;
				if (enemie[i].pos_x > width - 20)
					enemie[i].pos_x = width - 20;
				if (enemie[i].pos_y > height - 20)
					enemie[i].pos_y = height - 20;
				if (enemie[i].pos_y < 0)
					enemie[i].pos_y = 0;

				*/
				
				printf("Valor da posicao x do jogador: %d\nValor da posicao y do jogador: %d\n\n", player->pos_x, player->pos_y);
				printf("Valor da posicao x em volta do jogador: %d\nValor da posicao y em volta do jogador: %d\n\n", player->areaSpawnX, player->areaSpawnY);
				printf("Valor da posicao x: %d\nValor da posicao y: %d\n\n", enemie[i].pos_x, enemie[i].pos_y);
				
				while (enemie[i].pos_x > (player->areaSpawnX - player->pos_x) && enemie[i].pos_x < (player->areaSpawnX + player->pos_x)
					&& enemie[i].pos_y >(player->areaSpawnY - player->pos_y) && enemie[i].pos_y < (player->areaSpawnY + player->pos_y))
				{
					enemie[i].pos_x = rand() % (width - 40);
					enemie[i].pos_y = rand() % (height - 40);
					/*
					if (enemie[i].pos_x < 0)
						enemie[i].pos_x = 0;
					if (enemie[i].pos_x > width - 20)
						enemie[i].pos_x = width - 20;
					if (enemie[i].pos_y > height - 20)
						enemie[i].pos_y = height - 20;
					if (enemie[i].pos_y < 0)
						enemie[i].pos_y = 0;

					*/
					printf("Valor da posicao x: %d\nValor da posicao y: %d\n\n", enemie[i].pos_x, enemie[i].pos_y);
				}
			
				//break; //30 + rand() % (width - 60)
			//}
		//}
	}
}


void UpdateEnemie(struct Enemie enemie[], struct Player *player, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (enemie[i].vida)
		{

			//if (((player.x - monster->x < 64 ) && (player.x - monster->x > -64)) && ((player.y - monster->y < 64) && (player.y - monster->y > -64)))
			//if (((player->pos_x - enemie[i].pos_x < 150) && (player->pos_x - enemie[i].pos_x > -150)) && ((player->pos_y - enemie[i].pos_y < 150) && (player->pos_y - enemie[i].pos_y > -150)))
			//{
				if (enemie[i].pos_x > player->pos_x) {
					enemie[i].pos_x -= enemie[i].velocidade;
				}
				else if (enemie[i].pos_x < player->pos_x) {
					enemie[i].pos_x += enemie[i].velocidade;
				}

				if (enemie[i].pos_y > player->pos_y) {
					enemie[i].pos_y -= enemie[i].velocidade;
				}
				else if (enemie[i].pos_y < player->pos_y) {
					enemie[i].pos_y += enemie[i].velocidade;
				}
			//}
			
			

			//
			//((enemie[i].pos_y < player->areaY + player->pos_y) && (enemie[i].pos_y > player->areaY - player->pos_y)) && ((enemie[i].pos_x > player->areaX - player->pos_x) && (enemie[i].pos_x < player->areaX + player->pos_x))
			
			//if ()
				//enemie[i].pos_x = player->pos_x - enemie[i].velocidade;
			//if (enemie[i].pos_y < player->areaY + player->pos_y && enemie[i].pos_x < player->areaX + player->pos_x)
				//enemie[i].pos_y = player->pos_y - enemie[i].velocidade;
				//enemie[i].pos_x = player->pos_x - enemie[i].velocidade;
			//if (enemie[i].pos_y > player->areaY - player->pos_y)
				//enemie[i].pos_y = player->pos_y - enemie[i].velocidade;
		}
	}
}


int main(void)
{
	int item;
	do {
		printf("Digite o que voce deseja ver:\n\n0: Sair\n1: Jogo Teste\n\nEscolha: ");

		scanf_s("%d", &item);

		switch (item)
		{
		case 0: 
			exit(0);
			break;
		case 1:
			InputTimer();
			break;
		default:
			printf("Não foram digitados números correspondentes, digite novamente!");
			break;
		}
	} while (item != 0);
	
	return 0;
}