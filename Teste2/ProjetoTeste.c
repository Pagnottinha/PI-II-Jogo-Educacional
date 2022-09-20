#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>


void Geometria()
{
	ALLEGRO_DISPLAY* display = NULL;
	int width = 640;
	int height = 480;

	if (!al_init())
	{
		return -1;
	}

	display = al_create_display(width, height);

	if (!display)
	{
		return -1;
	}

	al_init_primitives_addon();

	al_draw_circle(100, 100, 50, al_map_rgb(255, 0, 255), 7);
	al_draw_filled_circle(400, 400, 70, al_map_rgb(255, 255, 255));
	al_draw_ellipse(150, 100, 100, 50, al_map_rgb(127, 3, 34), 6);
	al_draw_filled_ellipse(400, 250, 100, 200, al_map_rgb(0, 255, 255));

	float points[] = { 0, 0, 400, 100, 50, 200, width, height };
	al_draw_spline(points, al_map_rgb(255, 0, 255), 1);

	float points2[] = { 0, height, 200, 100, 400, 200, width, height };
	al_draw_spline(points2, al_map_rgb(0, 255, 0), 3);


	al_flip_display();

	al_rest(5.0);

	al_destroy_display(display);

}


void Start()
{

	ALLEGRO_DISPLAY* display = NULL;

	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to initialize allgro!", NULL, NULL);
		return -1;
	}

	display = al_create_display(640, 480);

	if (!display)
	{
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to initialize allgro!", NULL, NULL);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font24 = al_load_font("arial.ttf", 24, 0);
	ALLEGRO_FONT* font36 = al_load_font("arial.ttf", 36, 0);
	ALLEGRO_FONT* font18 = al_load_font("arial.ttf", 18, 0);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_text(font24, al_map_rgb(255, 0, 255), 50, 50, 0, "Hello World, this is 24 point");
	al_draw_text(font36, al_map_rgb(255, 127, 127), 640 / 2, 480 / 2, ALLEGRO_ALIGN_CENTER, "This is Centered and 36 point");
	al_draw_text(font18, al_map_rgb(15, 240, 18), 620, 350, ALLEGRO_ALIGN_RIGHT, "This is right aligned and 18 point");

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	al_draw_textf(font18, al_map_rgb(255, 255, 255), screen_w / 2, 400, ALLEGRO_ALIGN_CENTER, "Text with variable output (textf): Screen width and height = %i / %i", screen_w, screen_h);

	al_flip_display();

	al_rest(5.0);

	al_destroy_display(display);

}


int main(void)
{
	int item;
	do {
		printf("Digite o que voce deseja ver:\n\n1: Operação Teste\n2: Construindo Geometrias\n3: Sair\n\nEscolha: ");

		scanf_s("%d", &item);

		switch (item)
		{
		case 1:
			Start();
			break;
		case 2:
			Geometria();
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("Não foram digitados números correspondentes, digite novamente!");
			break;
		}
	} while (item != 3);
	
	return 0;
}