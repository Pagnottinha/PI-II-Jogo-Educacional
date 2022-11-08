#include "Inimigo.h"

void InitEnemie(Enemies* enemies)
{

    ALLEGRO_BITMAP* correndo = al_load_bitmap("Sprites/Inimigo/correr.png");
    ALLEGRO_BITMAP* atacando = al_load_bitmap("Sprites/Inimigo/ataque.png");

    al_convert_mask_to_alpha(correndo, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(atacando, al_map_rgb(0, 0, 0));


    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        Enemie* enemie = &enemies->enemie[i];

        enemie->vida = false;
        enemie->velocidade = 1;

		// frame
		enemie->dimensoesFrame[X] = 151;
		enemie->dimensoesFrame[Y] = 130;
		enemie->ContFrame = 0;
		enemie->FrameAtual = 0;
		enemie->linhaAnimacao = DIREITA;
        enemie->tipoAnimacao = CORRENDO;
		enemie->frameDelay = 15;

		enemie->maxFrame[CORRENDO] = 6;
		enemie->maxFrame[ATACANDO] = 6;

        enemie->sheets[CORRENDO] = correndo;
        enemie->sheets[ATACANDO] = atacando;

    }
}

void NewWave(Enemies* enemies) {
    for (int i = 0; i < enemies->countEnemies; i++) {
        Enemie* enemie = &enemies->enemie[i];

        enemie->vida = true;

        if (rand() % 2) {
            enemie->POS[X] = -enemie->dimensoesFrame[X];
        }
        else {
            enemie->POS[X] = WIDTH + enemie->dimensoesFrame[X];
        }

        enemie->POS[Y] = rand() % HEIGHT;
    }
}

void DrawEnemie(Enemies enemies)
{
    for (int i = 0; i < enemies.countEnemies; i++)
    {
        Enemie enemie = enemies.enemie[i];
        if (enemie.vida)
        {
			int fx = enemie.FrameAtual * enemie.dimensoesFrame[X];
			int fy = enemie.linhaAnimacao * enemie.dimensoesFrame[Y];

			al_draw_bitmap_region(enemie.sheets[enemie.tipoAnimacao], fx, fy, enemie.dimensoesFrame[X], enemie.dimensoesFrame[Y],
				enemie.POS[X], enemie.POS[Y], 0);
        }
    }
}

void UpdateEnemie(Enemies* enemies, Player player)
{
    for (int i = 0; i < enemies->countEnemies; i++)
    {
        Enemie *enemie = &enemies->enemie[i];

        if (enemie->vida)
        {

            if (enemie->POS[X] > player.POS[X] + 30) {
                enemie->linhaAnimacao = ESQUERDA;
                enemie->POS[X] -= enemie->velocidade;
            }
            else if (enemie->POS[X] < player.POS[X]) {
                enemie->linhaAnimacao = DIREITA;
                enemie->POS[X] += enemie->velocidade;
            }


            if (enemie->POS[Y] > player.POS[Y]) {
                enemie->POS[Y] -= enemie->velocidade;
            }
            else if (enemie->POS[Y] < player.POS[Y]) {
                enemie->POS[Y] += enemie->velocidade;
            }
        }

        if (enemie->POS[X] == player.POS[X] && enemie->POS[Y] == player.POS[Y] && enemie->vida)
        {
            enemie->vida = false;
            enemies->enemieDeath++;
        }
        else if (++enemie->ContFrame >= enemie->frameDelay) {
            enemie->FrameAtual++;

            if (enemie->FrameAtual >= enemie->maxFrame[enemie->tipoAnimacao])
                enemie->FrameAtual = 0;

            enemie->ContFrame = 0;
        }
        
    }
}

void destroyBitmapsEnemie(Enemies* enemies) {
    for (int i = 0; i < enemies->countEnemies; i++) {
        Enemie* enemie = &enemies->enemie[i];
        for (int j = 0; j < NUM_SPRITES_ENEMIE; j++) {
            al_destroy_bitmap(enemie->sheets[j]);
        }
    }
}