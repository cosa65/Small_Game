#include "unit_anims.h"

unit_anims::unit_anims(){
}

void unit_anims::load_animation(std::string name, int max, action_type type) {

	std::string png_location = gphandle::search_for(name, "dirs.txt");
	ALLEGRO_BITMAP *source_img = al_load_bitmap(png_location.c_str());
	sprite_file new_spr = sprite_file(name, source_img, max);
	//sprite_files.push_back(new_spr);

	this->actions[type] = new_spr;

}

sprite_file unit_anims::anim_for(action_type action) {
	return actions[action];
}


sprite_file unit_anims::fixed() { return actions[fixd_t]; }

sprite_file unit_anims::attack() { return actions[atk_t]; }

sprite_file unit_anims::defend() { return actions[dfd_t]; }

sprite_file unit_anims::idle() { return actions[idle_t]; }