#include "sprite_file.h"

sprite_file::sprite_file(){}

sprite_file::sprite_file(std::string type, ALLEGRO_BITMAP *source_img, int max, int sizex, int sizey) {
	this->_type = type;
	this->_size = max;
	_frames.resize(max);

	for(int i = 0; i < max; i++) {
		_frames[i] = gphandle::set_frame(source_img, i, max, sizex, sizey);
	}
}

sprite_file::~sprite_file() {
/*	for(int i = 0; i < max; i++) {
		frames[i].delete();
	}
*/
}

int sprite_file::size() {
	return this->_size;
}

ALLEGRO_BITMAP *sprite_file::operator[](int i) {
	return _frames[i];
}

void sprite_file::push_back(ALLEGRO_BITMAP *new_sprite) {
	_frames.push_back(new_sprite);
	this->_size++;
}
