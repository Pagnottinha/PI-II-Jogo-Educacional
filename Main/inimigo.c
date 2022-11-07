#include "Inimigo.h"

void InitEnemie(Enemies* enemies)
{
    for (int i = 0; i < enemies->countEnemies; i++)
    {
        Enemie* enemie = &enemies->enemie[i];

        enemie->vida = true;
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

        enemie->sheets[CORRENDO] = al_load_bitmap("Sprites/Inimigo/correr.png");
        enemie->sheets[ATACANDO] = al_load_bitmap("Sprites/Inimigo/ataque.png");

        int j;
		for (j = 0; j < NUM_SPRITES_ENEMIE; j++) {
			al_convert_mask_to_alpha(enemie->sheets[j], al_map_rgb(0, 0, 0));
		}

        if (rand() % 2) {
            enemie->POS[X] = -enemie->dimensoesFrame[X];
        }
        else {
            enemie->POS[X] = WIDTH + enemie->dimensoesFrame[X];
        }

        enemie->POS[Y] = rand() % (HEIGHT - 40);

        

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

        if (enemie->POS[X] == player.POS[Y] && enemie->POS[Y] == player.POS[Y] && enemie->vida)
        {
            enemie->vida = false;
            enemies->enemieDeath--;
        }
        else if (++enemie->ContFrame >= enemie->frameDelay) {
            enemie->FrameAtual++;

            if (enemie->FrameAtual >= enemie->maxFrame[enemie->tipoAnimacao])
                enemie->FrameAtual = 0;

            enemie->ContFrame = 0;
        }
        
    }
}