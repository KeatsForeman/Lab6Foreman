// Lab6Foreman.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include "ship.h";
#include "bullet.h"
#include <stdio.h>
#include <string>
#include <iostream>

int main(void)
{
	shipClass arrow;
	bullet mybullet[10];
	int score = 0;
	bool redraw = true;
	const int FPS = 60;
	int frames = 0;
	

	//variables
	int width = 640;
	int height = 520;
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	for (int i = 0; i < 10; i++) {
		mybullet[i].create_bullet_bitmap(display);
	}


	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_init_font_addon();

	ALLEGRO_FONT* font = al_load_font("Cat.ttf", 30, 0);

	arrow.create_ship_bitmap(display);


	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	arrow.drawShip();
	al_flip_display();
	al_start_timer(timer);
	int time = 30;
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			frames += 1;
			redraw = true;
			//every 60 frames time drops one second
			if (frames % 60 == 0) {
				time -= 1;
			}
			if (frames >= 1800) {
				break;
			}
			for (int i = 0;i < 10;i++)
			{
				if (!mybullet[i].getStatus()) {
					mybullet[i].fire();
					mybullet[i].draw();
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				arrow.up();
				break;
			case ALLEGRO_KEY_DOWN:
				arrow.down();
				break;
			case ALLEGRO_KEY_LEFT:
				arrow.left();
				break;
			case ALLEGRO_KEY_RIGHT:
				arrow.right();
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			if (arrow.getSpeed() != 0) {
				arrow.erase_ship();
				arrow.move_ship(width, height);
			}
			arrow.drawShip();
			for (int i = 0;i < 10;i++)
			{
				mybullet[i].erase_bullet();
				score += mybullet[i].move_bullet(arrow.getX(), arrow.getY(), 64, 64, height);
			}
		}
		//clear top of screen before writing
		al_draw_filled_rectangle(0, 0, width, 40, al_map_rgb(0, 0, 0));
		std::string scores = std::to_string(score);
		al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, 5, 0, scores.c_str());
		std::string times = std::to_string(time);
		al_draw_text(font, al_map_rgb(255, 255, 255), (width / 2) - 100, 5, 0, times.c_str());
		al_flip_display();
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	std::string scores = std::to_string(score);
	al_draw_text(font, al_map_rgb(255, 255, 255), width / 2, 5, 0, scores.c_str());
	
	al_rest(5.0);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}