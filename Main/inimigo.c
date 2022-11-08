#include "Inimigo.h"

void InitEnemie(Enemies* enemies)
{
    enemies->countEnemies = 0;
    enemies->enemieDeath = 0;
    enemies->waves[MAX] = 5;
    enemies->waves[QNT] = 0;

    ALLEGRO_BITMAP* correndo = al_load_bitmap("Sprites/Inimigo/correr.png");
    ALLEGRO_BITMAP* atacando = al_load_bitmap("Sprites/Inimigo/ataque.png");

    al_convert_mask_to_alpha(correndo, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(atacando, al_map_rgb(0, 0, 0));


    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        Enemie* enemie = &enemies->enemie[i];

        enemie->vivo = false;
        enemie->velocidade = 1;

		// frame
		enemie->dimensoesFrame[X] = 151;
		enemie->dimensoesFrame[Y] = 130;
		enemie->ContFrame = 0;
		enemie->FrameAtual = 0;
		enemie->linhaAnimacao = DIREITA;
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

        if (rand() % 2) {
            enemie->POS[X] = -enemie->dimensoesFrame[X];
        }
        else {
            enemie->POS[X] = WIDTH;
        }

        enemie->POS[Y] = rand() % HEIGHT;
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
            if (enemieAtaca(enemie, player))
            {
                ataqueEnemie(enemie, player);
            }
            else if (enemie->tipoAnimacao == ATACANDO) {
                enemie->tipoAnimacao = CORRENDO;
            }
            else {

                // ARRUMAR CONDIÇÕES
                if (enemie->POS[X] >= player->POS[X] + player->dimensoesFrame[X] / 2 + player->hitboxPlayer) {
                    enemie->linhaAnimacao = ESQUERDA;
                    enemie->POS[X] -= enemie->velocidade;
                }
                else if (enemie->POS[X] <= player->POS[X]) {
                    enemie->linhaAnimacao = DIREITA;
                    enemie->POS[X] += enemie->velocidade;
                }

                if (enemie->POS[Y] > player->POS[Y]) {
                    enemie->POS[Y] -= enemie->velocidade;
                }
                else if (enemie->POS[Y] < player->POS[Y]) {
                    enemie->POS[Y] += enemie->velocidade;
                }
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

bool enemieAtaca(Enemie* enemie, Player* player) {
    int meioPlayer = player->POS[X] + player->dimensoesFrame[X] / 2;

    return (enemie->POS[X] > player->POS[X] && enemie->POS[X] < meioPlayer + player->hitboxPlayer) &&
        enemie->POS[Y] == player->POS[Y] &&
        enemie->vida;
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

    if ((enemie->FrameAtual == 3 || enemie->FrameAtual == 4) && enemie->ContFrame == 0 && enemieAcertou(enemie, player)) {
        
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

bool enemieAcertou(Enemie* enemie, Player* player) {
    double meioPlayer = player->POS[X] + player->dimensoesFrame[X] / 2.0;
    if (enemie->linhaAnimacao == ESQUERDA) {
        return (enemie->POS[X] < meioPlayer + player->hitboxPlayer) &&
            (enemie->POS[X] > meioPlayer - player->hitboxPlayer) &&
            ((enemie->POS[Y] + enemie->hitboxEspada) > player->POS[Y]) &&
            ((enemie->POS[Y] + enemie->hitboxEspada + enemie->dimensoesEspada[Y]) < meioPlayer + player->hitboxPlayer);
    }
    else {
        return (enemie->POS[X] + enemie->dimensoesFrame[X] > meioPlayer - player->hitboxPlayer) &&
            (enemie->POS[X] + enemie->dimensoesFrame[X] < meioPlayer + player->hitboxPlayer) &&
            ((enemie->POS[Y] + enemie->hitboxEspada) > player->POS[Y]) &&
            ((enemie->POS[Y] + enemie->hitboxEspada + enemie->dimensoesEspada[Y]) < player->POS[Y] + meioPlayer + player->hitboxPlayer);
    }
}