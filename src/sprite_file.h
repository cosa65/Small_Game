#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>

#include "graphics_handler.h"

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