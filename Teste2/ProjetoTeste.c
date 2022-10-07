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
int width = 640;
int height = 480;

enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};

void InitPlayer(struct Player *player);
void DrawnPlayer(struct Player *player);
void MovePlayerUp(struct Player *player);
void MovePlayerDown(struct Player *player);
void MovePlayerRight(struct Player *player);
void MovePlayerLeft(struct Player *player);

void InitEnemie(struct Enemie enemie[], int size);
void DrawEnemie(struct Enemie enemie[], int size);
void StartEnemie(struct Enemie enemie[], int size);
void UpdateEnemie(struct Enemie enemie[], int size);

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
	InitEnemie(enemie, NUM_ENEMIE);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

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

			StartEnemie(enemie, NUM_ENEMIE);
			UpdateEnemie(enemie, NUM_ENEMIE);
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
			DrawEnemie(enemie, NUM_ENEMIE);
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
	player->vida = true;
	player->velocidade = 5;
	player->limiteX = 6;
	player->limiteY = 7;
	player->pontuacao = 0;
}

void DrawnPlayer(struct Player *player)
{
	al_draw_filled_rectangle(player->pos_x, player->pos_y, player->pos_x + 30, player->pos_y + 30, al_map_rgb(0, 0, 255));
}

void MovePlayerUp(struct Player *player)
{
	player->pos_y -= player->velocidade;
	if (player->pos_y < 0)
		player->pos_y = 0;
}

void MovePlayerDown(struct Player *player)
{
	player->pos_y += player->velocidade;
	if (player->pos_y > height)
		player->pos_y = height;
}

void MovePlayerRight(struct Player *player)
{
	player->pos_x += player->velocidade;
	if (player->pos_x > width)
		player->pos_x = width;
}

void MovePlayerLeft(struct Player *player)
{
	player->pos_x -= player->velocidade;
	if (player->pos_x < 0)
		player->pos_x = 0;
}


void InitEnemie(struct Enemie enemie[], int size)
{
	for (int i = 0; i < size; i++)
	{
		enemie[i].ID = ENEMY;
		enemie[i].vida = false;
		enemie[i].velocidade = 2.5;
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

void StartEnemie(struct Enemie enemie[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!enemie[i].vida)
		{
			if (rand() % 500 == 0)
			{
				enemie[i].vida = true;
				enemie[i].pos_x = 30 + rand() % (width - 60);
				enemie[i].pos_y = height - 479;

				break;
			}
		}
	}
}

void UpdateEnemie(struct Enemie enemie[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (enemie[i].vida)
		{
			enemie[i].pos_y += enemie[i].velocidade;

			if (enemie[i].pos_y > height)
				enemie[i].vida = false;
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