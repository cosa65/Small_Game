#include "unit.h"

unit::unit(){}

unit::unit(int type, int hp, int atk, int xpos, int ypos, int id) {
	this->type_ = type;
	this->hp_ = hp;
	this->atk_ = atk;
	this->xpos_ = xpos;
	this->ypos_ = ypos;
	this->id_ = id;
	this->sprite_num_ = 0;
	this->action_= fixd_t;
}

bool unit::attack(int xpos, int ypos) {
	if(this->type_ != ARCHER_NUM) {
		if(abs(this->xpos_ - xpos) <= 1 && abs(this->ypos_ - ypos) <= 1) {
			return true;
		}
	} else {
		if(abs(this->xpos_ - xpos) <= 3 && abs(this->ypos_ - ypos) <= 3) {
			return true;
		}
	}

	return false;
}

bool unit::move(int xf, int yf) {

	if(this->type_ != HORSEMAN_NUM) {
		if(abs(this->xpos_ - xf) <= 1 && abs(this->ypos_ - yf) <= 1) {
			this->xpos_ = xf;
			this->ypos_ = yf;
			return true;
		}
	} else {
		if(abs(this->xpos_ - xf) <= 2 && abs(this->ypos_ - yf) <= 2) {
			this->xpos_ = xf;
			this->ypos_ = yf;
			return true;
		}
	}
	return false;

}

bool unit::be_attacked(int dmg) {
	hp_ -= dmg;
	if(hp_ < 1) return true;
	return false;
}

int unit::my_atk() {
	return atk_;
}

int unit::mytype() {
	return type_;
}

void unit::print() {
	std::cout << type_ << " hp: " << hp_ << " X " << xpos_ << " Y " << ypos_ << "Sprite_num" << sprite_num_ << std::endl;
}

int unit::myid() {
	return id_;
}

int unit::sprite_num() {
	return sprite_num_;
}

void unit::update_sprite(int max) {
	sprite_num_ = (sprite_num_+1);
	if(sprite_num_ == max) {
		sprite_num_ = 0;
		action_ = fixd_t;
	}
}

int unit::x() {
	return xpos_;
}

int unit::y() {
	return ypos_;
}

void unit::start_animation(action_type action) {
	action_ = action;
	sprite_num_ = 0;
}

action_type unit::action() {
	return action_;
}