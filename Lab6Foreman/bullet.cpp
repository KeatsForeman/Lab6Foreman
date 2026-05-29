#include "bullet.h"
bullet::bullet()
{
	alive = false;;
	srand(time(0));
	bullet_bmp = nullptr;
}

bullet::~bullet() {
	al_destroy_bitmap(bullet_bmp);
}
bool bullet::getStatus()
{
	return alive;
}
//create bitmap for bullets
void bullet::create_bullet_bitmap(ALLEGRO_DISPLAY* display) {
	bullet_bmp = al_create_bitmap(8, 8);

	al_set_target_bitmap(bullet_bmp);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	int x = 0;
	int y = 0;

	al_draw_filled_rectangle(x, y, x+8, y+4, al_map_rgb(0, 0, 255));
	al_draw_filled_triangle(x, y + 4, x + 8, y + 4, x + 4, y + 8, al_map_rgb(255, 0, 0));
}

void bullet::draw(){
	al_draw_bitmap(bullet_bmp, x, y, 0);
}

void bullet::fire()
{
	x = rand() % 615 + 10;
	y = 40;
	alive = true;

}
void bullet::erase_bullet()
{
	al_draw_filled_rectangle(x, y, x + 8, y + 8, al_map_rgb(0, 0, 0)); //black color
}
int bullet::move_bullet(int arrowX, int arrowY, int width, int length, int height)
{
	y++;
	al_draw_bitmap(bullet_bmp, x, y, 0);


	if (x > arrowX && x < arrowX + width && y > arrowY && y < arrowY + length) {
		al_draw_filled_rectangle(x, y, x + 8, y + 8, al_map_rgb(0, 0, 0)); //BLACK
		alive = false;
		return 1;
	}
	if (y > height)
		alive = false;
	return 0;
}