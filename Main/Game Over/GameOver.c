#include "../game.h"
#include "../Background.h"
#include "../MenuInicial/Menu.h"

int GameOver(Allegro *allegro) {

	Background BG;
	InitBackground(&BG, 0, 0, "./Sprites/Background/GameOver.png");

	Botao botaoMenu;
	Botao tenteNovamente;
	Botao sair;

	bool done = false;
	bool desenhar = true;

	int mouseX;
	int mouseY;

	botaoMenu.botaoImage = al_load_bitmap("./Sprites/Botoes/Button_Animation1.png");
	botaoMenu.botaoHover = al_load_bitmap("./Sprites/Botoes/Button_Animation2.png");

	botaoMenu.hover = false;

	botaoMenu.posX = WIDTH / 2;
	botaoMenu.posY = 580;

	tenteNovamente.hover = false;

	tenteNovamente.posX = WIDTH / 2 - 350;
	tenteNovamente.posY = 580;


	sair.hover = false;

	sair.posX = WIDTH / 2;
	sair.posY = 580;


	int width = al_get_bitmap_width(botaoMenu.botaoImage); //350
	int height = al_get_bitmap_height(botaoMenu.botaoImage); //150

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(allegro->eventQueue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
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

			botaoMenu.hover = mouseX > 523 && mouseX < 758 &&
				mouseY > 624 && mouseY < 684;

			tenteNovamente.hover = mouseX > 198 && mouseX < 434 &&
				mouseY > 624 && mouseY < 684;

			sair.hover = mouseX > 848 && mouseX < 1083 &&
				mouseY > 624 && mouseY < 684;

		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouseX = ev.mouse.x;
			mouseY = ev.mouse.y;

			if (ev.mouse.button & 1)
			{
				if (mouseX > 523 && mouseX < 758 &&
					mouseY > 624 && mouseY < 684)
				{
					allegro->menu = true;
					done = true;
				}
				else if (mouseX > 198 && mouseX < 434 &&
					mouseY > 624 && mouseY < 684)
				{
					done = true;
					return 1;
				}
				else if (mouseX > 848 && mouseX < 1083 &&
					mouseY > 624 && mouseY < 684)
				{
					allegro->close = true;
					done = true;
					return 0;
				}
			}
		}

		if (desenhar && al_is_event_queue_empty(allegro->eventQueue))
		{
			desenhar = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			DrawBackground(BG);

			al_draw_multiline_text(allegro->font[r30], al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 50, 600, 30, ALLEGRO_ALIGN_CENTER, "Ah nao, parece que voce morreu e nao foi capaz de ganhar a guerra. Escolha o que voce deseja fazer.");

			//botao voltar para o menu
			if (!botaoMenu.hover)
				al_draw_bitmap(botaoMenu.botaoImage, botaoMenu.posX - 175, botaoMenu.posY, 0);
			else
				al_draw_bitmap(botaoMenu.botaoHover, botaoMenu.posX - 175, botaoMenu.posY, 0);

			al_draw_text(allegro->font[r30], al_map_rgb(255, 255, 255), botaoMenu.posX - 45, 640, 0, "MENU");

			//botao tente novamente
			if (!tenteNovamente.hover)
				al_draw_bitmap(botaoMenu.botaoImage, tenteNovamente.posX - 150, tenteNovamente.posY, 0);
			else
				al_draw_bitmap(botaoMenu.botaoHover, tenteNovamente.posX - 150, tenteNovamente.posY, 0);

			al_draw_text(allegro->font[r18], al_map_rgb(255, 255, 255), tenteNovamente.posX - 83, 645, 0, "TENTAR NOVAMENTE");
			
			//botao sair
			if (!sair.hover)
				al_draw_bitmap(botaoMenu.botaoImage, sair.posX + 150, sair.posY, 0);
			else
				al_draw_bitmap(botaoMenu.botaoHover, sair.posX + 150, sair.posY, 0);

			al_draw_text(allegro->font[r30], al_map_rgb(255, 255, 255), sair.posX + 290, 640, 0, "SAIR");


			al_flip_display();
		}

	}

	al_destroy_bitmap(botaoMenu.botaoImage);
	al_destroy_bitmap(botaoMenu.botaoHover);
	al_destroy_bitmap(BG.image);

	return 0;
}