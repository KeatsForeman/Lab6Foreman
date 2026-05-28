#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

#define MAXSPEED 3

class shipClass
{
public:
	shipClass();
	~shipClass();
	void create_ship_bitmap(ALLEGRO_DISPLAY* display);
	void erase_ship();
	void move_ship(int width, int height);
	void drawShip();
	int getDirection();
	int getSpeed();
	int getX();
	int getY();
	void up();
	void down();
	void right();
	void left();
private:

	int x, y;
	int dir, speed;
	int color;
	int score;
	ALLEGRO_BITMAP* ship_bmp[4];

};
