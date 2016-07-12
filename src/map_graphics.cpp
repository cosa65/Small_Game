#include "map_graphics.h"

map_graphics::map_graphics() {}

map_graphics::map_graphics(rlist<unit> *active_units) {
	_active_units = active_units;

	animations.resize(UNITS_AMOUNT);

}
map_graphics::~map_graphics() {
}

void map_graphics::load_animation(std::string type, int max, action_type action, int unit) {

	animations[unit].load_animation(type, max, action);

}

void map_graphics::load_sprite(std::string name, int max) {

	std::string png_location = gphandle::search_for(name, "dirs.txt");
	ALLEGRO_BITMAP *source_img = al_load_bitmap(png_location.c_str());
	sprite_file new_spr = sprite_file(name, source_img, max, 32, 32);
	sprite_files.push_back(new_spr);

}

void map_graphics::load_mouse_selection(std::string name) {
	std::string png_location = gphandle::search_for(name, "dirs.txt");
	ALLEGRO_BITMAP *source_img = al_load_bitmap(png_location.c_str());
	this -> mouse_selection = sprite_file(name, source_img, 1, 32, 32);
}

void map_graphics::update_animations() {

	sprite_file actual;

	for(rlist<unit>::r_iterator it = (*_active_units).begin(); !(it.null()); ++it) {

		actual = animations[(*it).mytype()].anim_for((*it).action());
		(it.current())->update_sprite(actual.size());
		gphandle::draw_at(actual[(*it).sprite_num()], (*it).x(), (*it).y());

	}
	
	gphandle::draw_at(mouse_selection[0], mouse_x, mouse_y);
}

void map_graphics::update_mouse_selection(int x, int y) {
	mouse_x = x;
	mouse_y = y;
}

void map_graphics::run_anim(action_type action, unit *animating) { //Blocking function, no other actions allowed in the map for the duration of this animation
	animating->start_animation(action);
}

/*void map_graphics::move_sprite(int xi, int yi, int xf, int yf) {

}


void map_graphics::remove_sprite(int x, int y) {

}*/