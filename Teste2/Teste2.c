#include <allegro5\allegro.h>
#include <allegro5/allegro_primitives.h>

int main(void)
{
	int width = 640;
	int height = 480;

	ALLEGRO_DISPLAY* display = NULL;

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

	return 0;


}