#include "Menu.h"
#include "../game.h"

int loadMenu(Allegro* allegro)
{
	bool done = false;
	bool desenhar = true;

	BackgroundMenu BG;

	InitBackgroundMenu(&BG, 0, 0, WIDTH, HEIGHT, "./Sprites/Botoes/MenuInicialBG.png");

	Botao botaoJogar;
	Botao botaoTutorial;
	Botao botaoSair;

	//inicializando os botoes com as suas respectivas imagens
	botaoJogar.botaoImage = al_load_bitmap("./Sprites/Botoes/Button_Animation1.png");
	botaoJogar.botaoHover = al_load_bitmap("./Sprites/Botoes/Button_Animation2.png");

	int mouseX;
	int mouseY;

	botaoJogar.hover = false;
	botaoTutorial.hover = false;
	botaoSair.hover = false;

	botaoJogar.posX = WIDTH / 2 - 175;
	botaoJogar.posY = 200;

	botaoTutorial.posX = WIDTH / 2 - 175;
	botaoTutorial.posY = 275;

	botaoSair.posX = WIDTH / 2 - 175;
	botaoSair.posY = 350;

	int width = al_get_bitmap_width(botaoJogar.botaoImage); //350
	int height = al_get_bitmap_height(botaoJogar.botaoImage); //150

	int teste = width + botaoJogar.posX;
	int teste2 = botaoJogar.posY + height;


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

			botaoJogar.hover = mouseX > 522 && mouseX < 758 &&
				mouseY > 245 && mouseY < 305;

			botaoTutorial.hover = mouseX > 522 && mouseX < 758 &&
				mouseY > 320 && mouseY < 380;

			botaoSair.hover = mouseX > 522 && mouseX < 758 &&
				mouseY > 395 && mouseY < 455;
			
					
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouseX = ev.mouse.x;
			mouseY = ev.mouse.y;

			if (ev.mouse.button & 1)
			{
				if (mouseX > 522 && mouseX < 758 &&
					mouseY > 245 && mouseY < 305)
				{
					return 0;
				}
				else if (mouseX > 522 && mouseX < 758 &&
					mouseY > 320 && mouseY < 380)
				{
					allegro->creditos = true;
					done = true;
				}
				else if (mouseX > 522 && mouseX < 758 &&
					mouseY > 395 && mouseY < 455)
				{
					allegro->close = true;
					done = true;
				}
			}
		}

		if (desenhar && al_is_event_queue_empty(allegro->eventQueue))
		{
			desenhar = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			DrawnBackMenu(BG);

			al_draw_text(allegro->font[r60], al_map_rgb(255, 255, 255), WIDTH / 2 - 100, 100, 0, "ILIADA");

			//botao jogar
			if (!botaoJogar.hover)
				al_draw_bitmap(botaoJogar.botaoImage, botaoJogar.posX, botaoJogar.posY, 0);
			else
				al_draw_bitmap(botaoJogar.botaoHover, botaoJogar.posX, botaoJogar.posY, 0);
			
			al_draw_text(allegro->font[r30], al_map_rgb(255, 255, 255), WIDTH / 2 - 50, 260, 0, "JOGAR");

			//botao de tutorial
			if (!botaoTutorial.hover)
				al_draw_bitmap(botaoJogar.botaoImage, botaoTutorial.posX, botaoTutorial.posY, 0);
			else
				al_draw_bitmap(botaoJogar.botaoHover, botaoTutorial.posX, botaoTutorial.posY, 0);

			al_draw_text(allegro->font[r30], al_map_rgb(255, 255, 255), WIDTH / 2 - 77, 335, 0, "CREDITOS");

			//botao de sair
			if (!botaoSair.hover)
				al_draw_bitmap(botaoJogar.botaoImage, botaoSair.posX, botaoSair.posY, 0);
			else
				al_draw_bitmap(botaoJogar.botaoHover, botaoSair.posX, botaoSair.posY, 0);

			al_draw_text(allegro->font[r30], al_map_rgb(255, 255, 255), WIDTH / 2 - 30, 410, 0, "SAIR");


			al_flip_display();
		}	
		
	}

	al_destroy_bitmap(botaoJogar.botaoImage);
	al_destroy_bitmap(botaoJogar.botaoHover);
	al_destroy_bitmap(BG.backgroundMenu);

	return 0;
}

void InitBackgroundMenu(BackgroundMenu* BG, float x, float y, int width, int height, char* imagePath)
{
	BG->X = x;
	BG->Y = y;
	BG->width = width;
	BG->height = height;
	BG->backgroundMenu = al_load_bitmap(imagePath);
}

void DrawnBackMenu(BackgroundMenu BG)
{
	al_draw_bitmap(BG.backgroundMenu, BG.X, BG.Y, 0);
}