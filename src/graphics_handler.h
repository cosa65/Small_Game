#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>

class gphandle{

	public:

		static void draw_at(ALLEGRO_BITMAP *sprite, int x, int y);
		static ALLEGRO_BITMAP *set_frame(ALLEGRO_BITMAP *sprites, int i, int max, int sizex, int sizey);
		static std::string search_for(std::string key, std::string strdirs);
		static std::string generate_back();

};