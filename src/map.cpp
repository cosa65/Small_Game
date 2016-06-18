#include "map.h"

map::map(int xsize, int ysize) {

	this->xsize = xsize;
	this->ysize = ysize;
	id = 0;
	
	block_input = -1;

	grid.resize(xsize);

	for(int i=0; i < xsize; i++) {
		grid[i].resize(ysize);
		
		for(int j=0; j < ysize; j++) {
			grid[i][j] = tile();
		}

	}

	graphics = map_graphics(&units);
	mouse_x = 0;
	mouse_y = 0;

	//graphics.load_sprite("archer_shot", 32);
	graphics.load_mouse_selection("mouse_selection");

	graphics.load_animation("archer_fixed", 1, fixd_t, ARCHER_NUM);
	graphics.load_animation("archer_attack", 32, atk_t, ARCHER_NUM);

	graphics.load_animation("swordsman_fixed", 1, fixd_t, SWORDSMAN_NUM);
	graphics.load_animation("swordsman_attack", 32, atk_t, SWORDSMAN_NUM);	
}

map::~map() {
/*
	for(int i=0; i < xsize; i++) {
		for(int j=0; j < ysize; j++) {
			~(grid[i][j]);
		}
	}
*/
}

bool map::is_empty(int x, int y) {
	return grid[x][y].is_empty();
}

bool map::move(int xi, int yi, int xf, int yf) {
	if(block_input != -1) return false;
	if(grid[xi][yi].is_empty()) return false;			//Case origin grid position is empty

	unit *umoving = grid[xi][yi].myunit();

	if(grid[xf][yf].is_empty()) {				//Case final grid position is empty
		if( grid[xi][yi].move(xf, yf) ){
			grid[xf][yf].occupy(umoving);
			grid[xi][yi].free_up();

			mouse_x = xf;
			mouse_y = yf;
			graphics.update_mouse_selection(xf, yf);

			return true;
		}
	} else {											
		
		if(grid[xi][yi].attack(xf,yf)) {						//Case final grid position occupied, (attack)

			block_input = 31;							
			graphics.run_anim(atk_t, grid[xi][yi].myunit());	
			bool died = grid[xf][yf].be_attacked(grid[xi][yi].myunit()->my_atk());
			if(died) {
				units.remove(grid[xf][yf].myunit());
				grid[xf][yf].free_up();
			}

			return true;
		}
	}
}

bool map::add_unit(int xi, int yi, int type) {
	unit *newunit = new unit(type, 100, 20, xi, yi,id);
	id++;
	if (grid[xi][yi].occupy(newunit)) {
		units.push_back(newunit);
		return true;
	}

	return false;
}

bool map::attack(int xi, int yi, int xf, int yf) {			//OLD

	if (grid[xi][yi].attack(xf, yf)) {
		int attacker_dmg = grid[xi][yi].get_atk();
		bool is_dead = grid[xf][yf].be_attacked(attacker_dmg);
		graphics.run_anim(action_type::atk_t, grid[xi][yi].myunit());
		if(is_dead) {
			if(!(units.remove(grid[xf][yf].myunit()))) {
				std::cerr << "Error: Unit not found in units list" << std::endl;
 				exit(-1);
			}
			grid[xf][yf].free_up();
			return true;
		}
	}

	return false;
}

void map::update_anims() {

	/*for(rlist<unit>::r_iterator it = units.begin(); !(it.null()); ++it) {
		//HOLA, ACA CAMBIO COSITAS DESPUES
		//(*it).update_sprite(32);
	}*/

	if(block_input != -1) {
		block_input--;
	}
	
	graphics.update_animations();

}

void map::mouse_select(int x, int y) {
	if(block_input == -1) {
		graphics.update_mouse_selection(x/32, y/32);
		mouse_x = x/32;
		mouse_y = y/32;
	}
}

int map::current_x() {
	return mouse_x;
}

int map::current_y() {
	return mouse_y;
}

void map::print_units() {
	std::cout << "---units---" << std::endl;
	for(rlist<unit>::r_iterator it = units.begin(); !it.null(); ++it) {
		(*it).print();
	}
	/*if(units.mysize() > 0){
		(*units.end()).print();
	}*/
	std::cout << "-----------" << std::endl;
}



map::tile::tile() {
	this->myunit_ = NULL;
}

map::tile::~tile() {
	//delete _myunit;
}

bool map::tile::occupy(unit *new_unit) {
	if(myunit_ == NULL) {
		myunit_ = new_unit;
		return true;
	}
	std::cout << "Error ocupying tile, is already occupied with: ";
	this->print(); 
	std::cout << std::endl;
	return false;
}

void map::tile::free_up() {
	myunit_ = NULL;
}

bool map::tile::is_empty() {
	return myunit_ == NULL;
}

unit *map::tile::myunit() {
	return this->myunit_;
}

bool map::tile::move(int xf, int yf) {
	return myunit_->move(xf, yf);
}

bool map::tile::attack(int xf, int yf) {
	if(!is_empty()) {
		return myunit_->attack(xf, yf);
	}
	return false;
}

int map::tile::get_atk() {
	if(!is_empty()) return myunit_->my_atk();
	return false;
}

int map::tile::be_attacked(int dmg) {
	if(!is_empty()) return myunit_->be_attacked(dmg);
	return false;
}

void map::tile::print() {
	if(myunit_ != NULL) {
		myunit_->print();
	} else {
		std::cout << "Empty tile." << std::endl;
	}
}