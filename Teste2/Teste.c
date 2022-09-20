
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>


int main(void)
{
	ALLEGRO_DISPLAY  *display = NULL;

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

	return 0;
}