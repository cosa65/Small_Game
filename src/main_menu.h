#pragma once

#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>

#include "graphics_handler.h"
#include "sprite_file.h"

class main_menu {

public:

	main_menu(int sizex, int sizey);
	bool update();
	void clicked();
	void update_mouse_axes(int x, int y);


private:

	//sprite_file start_game_unhover;
	sprite_file start_game_hover;
	sprite_file end_game_hover;
	sprite_file background;

	bool stay;

	int mousex, mousey;
	bool changed;
	int start_hover_act;
	int end_hover_act;

	int sizex, sizey;

};