#include "Inimigo.h"
#include <stdio.h>

void InitEnemie(Enemies* enemies, int numWaves)
{
    enemies->countEnemies = 0;
    enemies->enemieDeath = 0;
    enemies->waves[MAX] = numWaves;
    enemies->waves[QNT] = 0;

    ALLEGRO_BITMAP* correndo = al_load_bitmap("./Sprites/Inimigo/correr.png");
    ALLEGRO_BITMAP* atacando = al_load_bitmap("./Sprites/Inimigo/ataque.png");

    al_convert_mask_to_alpha(correndo, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(atacando, al_map_rgb(0, 0, 0));


    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        Enemie* enemie = &enemies->enemie[i];

        enemie->vivo = false;

		// frame
		enemie->dimensoesFrame[X] = 151;
		enemie->dimensoesFrame[Y] = 130;
		enemie->ContFrame = 0;
		enemie->FrameAtual = 0;
        enemie->tipoAnimacao = CORRENDO;
		enemie->frameDelay = 10;
        enemie->hitboxEspada = 87;
        enemie->dimensoesEspada[X] = 28;
        enemie->dimensoesEspada[Y] = 18;

		enemie->maxFrame[CORRENDO] = 6;
		enemie->maxFrame[ATACANDO] = 6;

        enemie->sheets[CORRENDO] = correndo;
        enemie->sheets[ATACANDO] = atacando;

    }
}

void NewWave(Enemies* enemies) {
    for (int i = 0; i < enemies->countEnemies; i++) {
        Enemie* enemie = &enemies->enemie[i];

        enemie->vivo = true;
        enemie->vida[MAXIMA] = rand() % 20 + 50;
        enemie->vida[ATUAL] = enemie->vida[MAXIMA];
        enemie->velocidade = rand() % 501 / 1000.0 + 1;

        if (rand() % 2) {
            enemie->POS[X] = -enemie->dimensoesFrame[X];
            enemie->linhaAnimacao = DIREITA;
        }
        else {
            enemie->POS[X] = WIDTH;
            enemie->linhaAnimacao = ESQUERDA;
        }

        enemie->POS[Y] = rand() % (HEIGHT - MIN_HEIGHT) + MIN_HEIGHT;
    }
}

void DrawEnemie(Enemies enemies)
{
    for (int i = 0; i < enemies.countEnemies; i++)
    {
        Enemie enemie = enemies.enemie[i];
        if (enemie.vivo)
        {
			int fx = enemie.FrameAtual * enemie.dimensoesFrame[X];
			int fy = enemie.linhaAnimacao * enemie.dimensoesFrame[Y];

			al_draw_bitmap_region(enemie.sheets[enemie.tipoAnimacao], fx, fy, enemie.dimensoesFrame[X], enemie.dimensoesFrame[Y],
				enemie.POS[X], enemie.POS[Y], 0);
        }
    }
}

void UpdateEnemie(Enemies* enemies, Player* player)
{
    for (int i = 0; i < enemies->countEnemies; i++)
    {
        Enemie *enemie = &enemies->enemie[i];

        if (enemie->vivo)
        {
            if (enemieAcerta(enemie, player))
            {
                ataqueEnemie(enemie, player);
            }
            else if (enemie->tipoAnimacao == ATACANDO) {
                enemie->tipoAnimacao = CORRENDO;
            }
            else {

                MoveEnemie(enemie, player);
            }
        }
        
        if (++enemie->ContFrame >= enemie->frameDelay) {
            enemie->FrameAtual++;

            if (enemie->FrameAtual >= enemie->maxFrame[enemie->tipoAnimacao])
                enemie->FrameAtual = 0;

            enemie->ContFrame = 0;
        }
        
    }
}

void MoveEnemie(Enemie* enemie, Player* player) {
    int meioPlayer[2] = { player->POS[X] + player->dimensoesFrame[X] / 2.0, player->POS[Y] + player->dimensoesFrame[Y] / 2.0 };
    int meioEnemie[2] = { enemie->POS[X] + enemie->dimensoesFrame[X] / 2.0, enemie->POS[Y] + enemie->dimensoesFrame[Y] / 2.0 };

    double dx = meioEnemie[X] > meioPlayer[X] ?
        meioEnemie[X] - meioPlayer[X] :
        meioPlayer[X] - meioEnemie[X];
    double dy = meioEnemie[Y] > meioPlayer[Y] ?
        meioEnemie[Y] - meioPlayer[Y] :
        meioPlayer[Y] - meioEnemie[Y];

    double angulo = atan(dx / dy);
    
    if (enemie->POS[X] >= meioPlayer[X]) {
        enemie->linhaAnimacao = ESQUERDA;
        enemie->POS[X] -= sin(angulo) * enemie->velocidade;
    }
    else if (enemie->POS[X] + enemie->dimensoesFrame[X] <= meioPlayer[X]) {
        enemie->linhaAnimacao = DIREITA;
        enemie->POS[X] += sin(angulo) * enemie->velocidade;
    }
    
    if (enemie->POS[Y] > player->POS[Y] + 1) {
        enemie->POS[Y] -= cos(angulo) * enemie->velocidade;
    }
    else if (enemie->POS[Y] < player->POS[Y] - 1) {
        enemie->POS[Y] += cos(angulo) * enemie->velocidade;
    }
}

void destroyBitmapsEnemie(Enemies* enemies) {

    Enemie* enemie = &enemies->enemie[0];
    for (int j = 0; j < NUM_SPRITES_ENEMIE; j++) {
        al_destroy_bitmap(enemie->sheets[j]);
    }

}

void ataqueEnemie(Enemie* enemie, Player* player) {
    if (enemie->tipoAnimacao != ATACANDO) {
        enemie->FrameAtual = 0;
        enemie->tipoAnimacao = ATACANDO;
    }

    if ((enemie->FrameAtual == 3 || enemie->FrameAtual == 4) && enemie->ContFrame == 0) {
        
        player->vida[ATUAL] -= rand() % 10 + 20;

        if (player->vida[ATUAL] <= 0) {
            player->vivo = false;
            player->vida[ATUAL] = 0;
            return;
        }

        if (enemie->linhaAnimacao == ESQUERDA) {
            player->POS[X] -= 25;
        }
        else {
            player->POS[X] += 25;
        }
    }
}

bool enemieAcerta(Enemie* enemie, Player* player) {
    int coordenadasX = player->POS[X] + player->dimensoesFrame[X] / 2.0;

    if (enemie->linhaAnimacao == ESQUERDA) {
        coordenadasX += player->hitboxPlayer;
    }
    else {
        coordenadasX -= player->hitboxPlayer;
    }

    return (enemie->POS[X] < coordenadasX) &&
        (enemie->POS[X] + enemie->dimensoesFrame[X] > coordenadasX) &&
        ((enemie->POS[Y] + enemie->hitboxEspada) > player->POS[Y]) && ((enemie->POS[Y] + enemie->hitboxEspada) < player->POS[Y] + player->dimensoesFrame[Y]) &&
        ((enemie->POS[Y] + enemie->hitboxEspada) > player->POS[Y]) &&
        ((enemie->POS[Y] + enemie->hitboxEspada + enemie->dimensoesEspada[Y]) < player->POS[Y] + player->dimensoesFrame[Y]);
}