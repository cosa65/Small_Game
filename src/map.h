#include <iostream>
#include "map_graphics.h"

#ifndef MAP_H
#define MAP_H


class map
{
public:

	map(int xsize, int ysize);
	~map();
	//map *new_map(int sizex, int sizey);
	bool is_empty(int x, int y);
	bool move(int xi, int yi, int xf, int yf);
	bool add_unit(int xi, int yi, int type);
	bool attack(int xi, int yi, int xf, int yf);
	void update_anims();
	void mouse_select(int x, int y);
	int current_x();
	int current_y();

	void print_units();

private:

	class tile 
	{
	public:

		tile();
		~tile();
		bool occupy(unit *new_unit);
		void free_up();
		bool is_empty();
		unit *myunit();
		bool move(int xf, int yf);
		bool attack(int x, int y);
		int get_atk();
		int be_attacked(int dmg);
		void print();
	
	private:
		unit *myunit_;
	};

	int xsize;
	int ysize;
	std::vector< std::vector <tile> > grid;
	rlist< unit > units;
	int id;
	map_graphics graphics;
	int mouse_x;
	int mouse_y;


	//blocking actions handler stuff
	int block_input;		//If no_actions is different than -1, no new input is taken
	action_type curr_action;
	unit *curr_unit_acting;
};

#endif