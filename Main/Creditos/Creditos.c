#include "../game.h"
#include "../Background.h"
#include "../MenuInicial/Menu.h"

int InitCreditos(Allegro *allegro)
{
	Background BG;
	InitBackground(&BG, 0, 0, "./Sprites/Background/ImagemCreditos.png");

	Botao botaoVoltar;

	bool done = false;
	bool desenhar = true;

	int mouseX;
	int mouseY;
	
	int controleY = 720;

	botaoVoltar.botaoImage = al_load_bitmap("./Sprites/Botoes/Button_Animation1.png");
	botaoVoltar.botaoHover = al_load_bitmap("./Sprites/Botoes/Button_Animation2.png");

	botaoVoltar.hover = false;

	botaoVoltar.posX = WIDTH / 2 + 275;
	botaoVoltar.posY = 580;

	int width = al_get_bitmap_width(botaoVoltar.botaoImage); //350
	int height = al_get_bitmap_height(botaoVoltar.botaoImage); //150

	int teste = width + botaoVoltar.posX;
	int teste2 = botaoVoltar.posY + height;


	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro->eventQueue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			controleY--;
			desenhar = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				allegro->close = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			allegro->close = true;
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouseX = ev.mouse.x;
			mouseY = ev.mouse.y;

			botaoVoltar.hover = mouseX > 973 && mouseX < 1208 &&
				mouseY > 624 && mouseY < 684;


		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouseX = ev.mouse.x;
			mouseY = ev.mouse.y;

			if (ev.mouse.button & 1)
			{
				if (mouseX > 973 && mouseX < 1208 &&
					mouseY > 624 && mouseY < 684)
				{
					done = true;
				}
			}
		}

		if (controleY == -1200)
			done = true;

		if (desenhar && al_is_event_queue_empty(allegro->eventQueue))
		{
			desenhar = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			DrawBackground(BG);

			al_draw_text(allegro->font[r60], al_map_rgb(255, 255, 255), WIDTH / 2 - 100, controleY, 0, "ILIADA");

			al_draw_multiline_text(allegro->font[r24], al_map_rgb(255, 255, 255), WIDTH / 2, controleY + 100, 
				500, 24, ALLEGRO_ALIGN_CENTER, "Creditos\n\nMebros do Grupo:\n\n\nErick Lima\nGustavo Faria\nLorran Palmeira\nRaphael Rocha\n\n\nLivro Base:\n\nIliada - Homero\n\n\nProgramacao:\n\nErick Lima\nGustavo Faria\n\n\nAnimacoes:\n\nErick Lima\nGustavo Faria\n\n\nEnredo:\n\nErick Lima\nGustavo Faria\nLorran Palmeira\nRaphael Rocha\n\n\n");

			al_draw_text(allegro->font[r60], al_map_rgb(255, 255, 255), WIDTH / 2, controleY + 1000, ALLEGRO_ALIGN_CENTER, "OBRIGADO");
			//botao jogar
			if (!botaoVoltar.hover)
				al_draw_bitmap(botaoVoltar.botaoImage, botaoVoltar.posX, botaoVoltar.posY, 0);
			else
				al_draw_bitmap(botaoVoltar.botaoHover, botaoVoltar.posX, botaoVoltar.posY, 0);

			al_draw_text(allegro->font[r30], al_map_rgb(255, 255, 255),botaoVoltar.posX + 110, 640, 0, "VOLTAR");

			al_flip_display();
		}

	}

	al_destroy_bitmap(botaoVoltar.botaoImage);
	al_destroy_bitmap(botaoVoltar.botaoHover);
	al_destroy_bitmap(BG.image);

	return 0;
}
