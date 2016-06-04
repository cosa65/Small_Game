#include "graphics_handler.h" 

void gphandle::draw_at(ALLEGRO_BITMAP *sprite, int x, int y) {
	al_draw_bitmap(sprite, (float)x*32, (float)y*32, 0);
}

ALLEGRO_BITMAP *gphandle::set_frame(ALLEGRO_BITMAP *sprites, int i, int max) {

	return (al_create_sub_bitmap(sprites,((i)%max)*32,0,32,32));
}

std::string gphandle::search_for(std::string key, std::string strdirs) {
	
	std::ifstream dirs(strdirs.c_str());
	std::string act_key;
	std::string location;
	while(getline(dirs, act_key, ':')) {
		if(act_key == key) {
			getline(dirs, location); 
			return location;
		}
		getline(dirs,act_key);
	}
	
	return "not found";
}

std::string gphandle::generate_back() {

	int grass_sprites_size = 9;

	std::string grass_loc = search_for("grass", "dirs.txt");

	ALLEGRO_BITMAP *grass_img = al_load_bitmap(grass_loc.c_str());

	std::vector<ALLEGRO_BITMAP *> grasses(grass_sprites_size);

	for(int i=0; i<grass_sprites_size; i++) {
		grasses[i] = al_create_sub_bitmap(grass_img, i*32, 0, (i+1)*32, 32);
	}

	ALLEGRO_BITMAP *new_back = al_create_bitmap(1024, 768);
	al_set_target_bitmap(new_back);

	srand(time(NULL));

	for(int i=0; i<24; i++){
		for(int j=0; j<32; j++) {
			int random = rand()%grass_sprites_size;
			al_draw_bitmap(grasses[random], 32.0 * j, 32.0 * i,0);
		}
	}

	std::string location = "tmps/background.png";

	al_save_bitmap(location.c_str(), new_back);

	return location;
}

