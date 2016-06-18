#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>	
#include <vector>

#include "sprite_file.h"
#include "unit.h"

void draw_at(ALLEGRO_BITMAP *sprite, int x, int y);
ALLEGRO_BITMAP *set_frame(ALLEGRO_BITMAP *sprites, int i, int max);
std::string search_for(std::string key, std::string strdirs);
std::string generate_back();

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