#include "ship.h"
shipClass::shipClass()
{
	speed = 0;
	x = 100;
	y = 100;
	dir = 1;
	score = 0;
	for (int i = 0; i < 4; i++)
	{
		ship_bmp[i] = NULL;
	}
}
shipClass::~shipClass()
{
	for (int i = 0; i < 4; i++)
	{
		al_destroy_bitmap(ship_bmp[i]);
	}
}
void shipClass::drawShip()
{
	al_draw_bitmap(ship_bmp[getDirection()], getX(), getY(), 0);
}
void shipClass::create_ship_bitmap(ALLEGRO_DISPLAY* display)
{
	for (int i = 0;i < 4; i++)
	{
		ship_bmp[i] = al_create_bitmap(64, 64);
		if (!ship_bmp[i]) {
			exit(1);
			al_destroy_display(display);

		}

		al_set_target_bitmap(ship_bmp[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		int x = 32;
		int y = 32;
		al_draw_filled_ellipse(x, y + 12, 32, 20, al_map_rgb(0, 0, 255));
		al_draw_filled_triangle(x - 5, y + 10, x + 4, y + 10, x, y - 32, al_map_rgb(255, 0, 0));
		al_draw_filled_triangle(x - 25, y + 8, x - 15, y + 8, x - 5, y - 25, al_map_rgb(0, 255, 0));
		al_draw_filled_triangle(x + 25, y + 8, x + 15, y + 8, x + 5, y - 25, al_map_rgb(0, 255, 0));
		al_draw_filled_rectangle(x - 26, y + 5, x + 26, y + 20, al_map_rgb(50, 50, 50));
		al_draw_filled_circle(x - 20, y + 9, 7, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x + 20, y + 9, 7, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x, y + 10, 8, al_map_rgb(0, 0, 0));
	}
}
void shipClass::erase_ship()
{

	int left = x;
	int top = y;
	int right = x + 64;
	int bottom = y + 64;

	al_draw_filled_rectangle(left, top, right, bottom, al_map_rgb(0, 0, 0));
}

void shipClass::up()
{
	dir = 0;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void shipClass::down()
{
	dir = 2;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}


void shipClass::left()
{
	dir = 3;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}

void shipClass::right()
{
	dir = 1;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}
int shipClass::getDirection()
{
	return dir;
}
int shipClass::getSpeed()
{
	return speed;
}
int shipClass::getX()
{
	return x;
}
int shipClass::getY()
{
	return y;
}
void shipClass::move_ship(int width, int height)
{

	//update ship position based on direction
	switch (dir)
	{
	case 0:
		y -= speed;
		break;
	case 1:
		x += speed;
		break;
	case 2:
		y += speed;
		break;
	case 3:
		x -= speed;
	}

	//keep ship inside the screen
	if (x > width - 64)
	{
		x = width - 64;
		speed = 0;
	}
	if (x < 0)
	{
		x = 0;
		speed = 0;
	}
	if (y > height - 64)
	{
		y = height - 64;
		speed = 0;
	}
	if (y < 0)
	{
		y = 0;
		speed = 0;
	}
}