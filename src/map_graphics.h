#ifndef MAP_GRAPHICS_H
#define MAP_GRAPHICS_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>	
#include <vector>

#include "graphics_handler.h"
#include "refList.h"
#include "unit.h"

#define ACTIONS_AMOUNT 5
#define UNITS_AMOUNT 4

void draw_at(ALLEGRO_BITMAP *sprite, int x, int y);
ALLEGRO_BITMAP *set_frame(ALLEGRO_BITMAP *sprites, int i, int max);
std::string search_for(std::string key, std::string strdirs);
std::string generate_back();

class sprite_file {

	public:
		sprite_file();
		sprite_file(std::string type, ALLEGRO_BITMAP *source_img, int max);
		~sprite_file();
		int size();
		ALLEGRO_BITMAP *operator[](int i);

	private:

		std::string _type;
		int _size;
		std::vector< ALLEGRO_BITMAP *> _frames;

};



class unit_anims {

	public:

		unit_anims();
		void load_animation(std::string name, int max, action_type action);
		sprite_file anim_for(action_type action);
		sprite_file fixed();
		sprite_file attack();
		sprite_file defend();
		sprite_file idle();


	private:

		sprite_file actions[ACTIONS_AMOUNT];

		/*sprite_file fixed_;
		sprite_file attack_;
		sprite_file defend_;
		sprite_file idle_;*/

};


class map_graphics{
	
	public:

		map_graphics();
		map_graphics(rlist<unit> *active_units);
		~map_graphics();

		void load_animation(std::string type, int max, action_type action, int unit);
		void load_sprite(std::string type, int max);
		void load_mouse_selection(std::string mouse_sel_location);

		void update_animations();
		void update_mouse_selection(int x, int y);

		void run_anim(action_type type, unit *animating);

		//void move_sprite(int xi, int yi, int xf, int yf);
		//void remove_sprite(int x, int y);

	private:

		//units animations handler
		std::vector<unit_anims> animations;
		std::vector<sprite_file> sprite_files;
		rlist<unit> *_active_units;
		std::list< std::string > types;

		//mouse selection handler
		sprite_file mouse_selection;
		int mouse_x, mouse_y;

		//ALLEGRO_BITMAP *main_buf;
};






#endif