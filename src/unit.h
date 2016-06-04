 #include <iostream>

#ifndef UNIT_H
#define UNIT_H

#define ARCHER_NUM 0
#define SWORDSMAN_NUM 1
#define HORSEMAN_NUM 2

enum action_type { fixd_t = 0, atk_t = 1, dfd_t = 2, idle_t = 3, die_t = 4};

class unit
{
public:

	unit();
	unit(int type, int hp, int atk, int xpos, int ypos, int id);
	bool attack(int xpos, int ypos);	//returns whether it can attack or not
	bool move(int xf, int yf);			//returns it could move there or not
	bool be_attacked(int dmg);			//returns whether it has died or not
	int my_atk();						//returns this unit's damage
	int	 mytype();
	void print();						//pushes to stdout its type, hp and position
	int myid();							//TRASH/nose
	int sprite_num();					//returns its current sprite number in its current animation
	void update_sprite(int max);		//augments its sprite number in 1
	int x();
	int y();
	void start_animation(action_type action);
	action_type action();

private:
	int type_;
	int hp_;
	int atk_;
	int xpos_;
	int ypos_;
	int id_;
	int sprite_num_;
	action_type action_;
};

#endif