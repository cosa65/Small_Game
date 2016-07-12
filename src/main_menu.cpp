#include "main_menu.h"

int ypoint_at(int x, int xi, int yi, int xf, int yf) {
	return (yf - yi)/(xf - xi) * (x - xi) + yi;
}

bool inside_of(int xm, int ym, int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {
	bool higher_than = ym > ypoint_at(xm, x11, y11, x12, y12);
	bool lower_than = ym < ypoint_at(xm, x21, y21, x22, y22);
	bool righter_than = xm > ypoint_at(ym, y12, x12, y22, x22);
	bool lefter_than = xm < ypoint_at(ym, y11, x11, y21, x21);

	return !(higher_than || lower_than || righter_than || lefter_than);
}

int xpoint_at(int y, int xi, int yi, int xf, int yf) {
	return (y - yi) * ( (xf - xi) / (yf - yi) ) + xi;
}

int intersects_left(int x, int y, int x1, int y1, int x2, int y2) {
	if (y1 == y2) {return 0;}

	int xat = xpoint_at(y, x1, y1, x2, y2);
	
	bool intsect = (xat >= x1) && (xat <= x2);

	//std::cout << xat << std::endl;

	return intsect && (xat >= x);
}

int intersects_right(int x, int y, int x1, int y1, int x2, int y2) {
	int xat = xpoint_at(y, x1, y1, x2, y2);
	
	bool intsect = (xat >= x1) && (xat <= x2);

	return intsect && xat >= x;
}

bool inside_of_raytrc(int x, int y, int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {
	//std::cout << "HOLO" << std::endl;
	return (intersects_left(x, y, x11, y11, x21, y21) + (intersects_left(x, y, x12, y12, x22, y22)) + intersects_left(x, y, x11, y11, x12, y12) + intersects_left(x, y, x21, y21, x22, y22))%2 == 1;
}

main_menu::main_menu(int sizex, int sizey) {
	std::string STRstart_game_unhover = gphandle::search_for("start_game_unhover", "dirs.txt");
	std::string STRstart_game_hover = gphandle::search_for("start_game_hover", "dirs.txt");
	std::string STRend_game_unhover = gphandle::search_for("end_game_unhover", "dirs.txt");
	std::string STRend_game_hover = gphandle::search_for("end_game_hover", "dirs.txt");
	std::string STRmain_menu_background = gphandle::search_for("main_menu_background", "dirs.txt");

	ALLEGRO_BITMAP *bmpstart_game_unhover = al_load_bitmap(STRstart_game_unhover.c_str());
	ALLEGRO_BITMAP *bmpstart_game_hover = al_load_bitmap(STRstart_game_hover.c_str());
	ALLEGRO_BITMAP *bmpend_game_unhover = al_load_bitmap(STRend_game_unhover.c_str());
	ALLEGRO_BITMAP *bmpend_game_hover = al_load_bitmap(STRend_game_hover.c_str());
	ALLEGRO_BITMAP *bmpmain_menu_background = al_load_bitmap(STRmain_menu_background.c_str());	//???

	//start_game_unhover= sprite_file("1", bmpstart_game_unhover, 1, 1024, 768);

	end_game_hover = sprite_file("1", bmpend_game_unhover, 1, 1024, 768);
	end_game_hover.push_back(bmpend_game_hover);

	start_game_hover = sprite_file("2", bmpstart_game_unhover, 1, 1024, 768);
	start_game_hover.push_back(bmpstart_game_hover);

	background= sprite_file("3", bmpmain_menu_background, 1, 1024, 768);

	this->sizex = sizex;
	this->sizey = sizey;

	stay = true;
	start_hover_act = 0;
	end_hover_act = 0;
	/*al_draw_bitmap(background[0], 0.0, 0.0, 0);
	al_draw_bitmap(start_game_hover[0], 512-128, 384-64, 0);*/
}



bool main_menu::update() {

	al_draw_bitmap(background[0], 0.0, 0.0, 0);

	if(changed) {

		if(inside_of(mousex, sizey - mousey, 412, sizey - 360, 685, sizey - 354, 412, sizey - 467, 685, sizey - 200)) {
			start_hover_act = 1;//al_draw_bitmap(start_game_hover[1], 0.0, 0.0, 0);
			end_hover_act = 0;
		} else {

			start_hover_act = 0;

			if (inside_of(mousex, sizey - mousey, 412, sizey - 676, 685, sizey - 666, 412, sizey - 767, 685, sizey - 768)) {
				end_hover_act = 1;
			} else {
				end_hover_act = 0;
			}
		}	

		changed = false;
	}
	
	al_draw_bitmap(start_game_hover[start_hover_act], 0.0, 0.0, 0);
	al_draw_bitmap(end_game_hover[end_hover_act], 0.0, 0.0, 0);

	return stay;
}

void main_menu::clicked() {
	if( inside_of(mousex, sizey - mousey, 412, sizey - 360, 685, sizey - 354, 412, sizey - 467, 685, sizey - 200)) {
		stay = false;
	} else if( inside_of(mousex, sizey - mousey, 412, sizey - 676, 685, sizey - 666, 412, sizey - 767, 685, sizey - 768)) {
		exit(0);
	}
}

void main_menu::update_mouse_axes(int x, int y) {
	mousex = x;
	mousey = y;
	changed = true;
}