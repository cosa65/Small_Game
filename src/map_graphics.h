#pragma once

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>	
#include <vector>

#include "unit_anims.h"
#include "refList.h"

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
	
	//effects animations handler
	//std::list<  > ;

	//mouse selection handler
	sprite_file mouse_selection;
	int mouse_x, mouse_y;

	//ALLEGRO_BITMAP *main_buf;
};
