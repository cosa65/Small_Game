#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <list>
#include <fstream>
#include <istream>
#include <stdlib.h>
#include <time.h>

//#include "background_gen.cpp"
#include "map.h"
#include "main_menu.h"
//#include "mapmanager.cpp"

const float FPS = 30;
ALLEGRO_BITMAP *main_buf;
int resx = 1024;
int resy = 768;

int main(int argc, char *argv[])
{

	if(!al_init()) std::cerr << "Error inicializando Allegro";
	if(!al_init_image_addon()) std::cerr << "Error inicializando allegro_image";
	//if(!al_init_ttf_addon()) std::cerr << "Error inicializando allegro_ttf";

	if(!al_install_keyboard()) std::cerr << "Error inicializando teclado";
	if(!al_install_mouse()) std::cerr << "Error inicializando mouse";
	al_set_new_display_flags(ALLEGRO_WINDOWED + ALLEGRO_FRAMELESS);




	ALLEGRO_DISPLAY *ventana = al_create_display(1024, 768);
	main_buf = al_get_backbuffer(ventana);

	ALLEGRO_BITMAP *temporary_buf = al_create_bitmap(1024, 768);
	al_set_target_bitmap(temporary_buf);


	al_grab_mouse(ventana);

	ALLEGRO_EVENT_QUEUE *event_queue;
   	ALLEGRO_TIMER *main_timer;
   	bool redraw;

	
//-------------------------------DEPRUEBA-------------------------------
	ALLEGRO_COLOR verde_oscuro = al_map_rgb(24,150,18);

//----------------------------------------------------------------------

	main_timer = al_create_timer(1.0 / FPS);
	redraw = false;





	event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(main_timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

//////////////////////////////////MAIN MENU//////////////////////////////////
	{
		bool loop_main = true;
		bool clicked;
		
		al_start_timer(main_timer);
		
		main_menu menu = main_menu(1024, 768);
		
		al_set_mouse_xy(ventana, 512, 128);
		menu.update_mouse_axes(512, 128);

		while(loop_main) {

			ALLEGRO_EVENT ev;
			clicked = false;


		    while(!al_get_next_event(event_queue, &ev)) { 
		      	switch (ev.type) {
		      		
		      		case ALLEGRO_EVENT_TIMER : 
		      			redraw = true;
		      			break;

		    		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
		    			if(!clicked) {
			    			if(ev.mouse.button == 1) {
			    				menu.clicked();
			    			}
			    			clicked = true;
		    			}
		    			break;
		    		}

		    		case ALLEGRO_EVENT_KEY_UP : {
		    			if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
		    				loop_main = false;
	    				}
		    			break;
		    		}

		    		case ALLEGRO_EVENT_MOUSE_AXES : {
		    			menu.update_mouse_axes(ev.mouse.x, ev.mouse.y);
		    			break;
		    		}
			    }
		    }

			if(redraw) {
			
				al_set_target_bitmap(main_buf);
				al_draw_scaled_bitmap(temporary_buf, 0.0, 0.0, 1024.0, 768.0, 0.0, 0.0, (float)resx, (float)resy, 0);
				al_set_target_bitmap(temporary_buf);

				redraw = false;
				if (!menu.update()) loop_main = false;
				al_flip_display();
			
			}
		}
	}
////////////////////////////END MAIN MENU////////////////////////////////

	std::string back_loc = gphandle::generate_back();

	ALLEGRO_BITMAP *background = al_load_bitmap(back_loc.c_str());

	//al_draw_bitmap(background, 0.0, 0.0, 0);


	map new_map = map(32,24);
	//al_draw_bitmap(background, 0.0, 0.0, 0);
	new_map.add_unit(0,0,ARCHER_NUM);
	new_map.add_unit(1,1,ARCHER_NUM);
	new_map.add_unit(2,2,SWORDSMAN_NUM);	

	bool loop = true;

	bool clicked;
	


		
//-------------------------------DEPRUEBA-------------------------------
		//new_map.attack(1,1,0,0);
		//new_map.print_units();

		//new_map.mouse_select(5,0);

//----------------------------------------------------------------------
	
	ALLEGRO_EVENT ev;
	clicked = false;

	while(loop)
	{
		al_start_timer(main_timer);


		al_draw_bitmap(background, 0.0, 0.0, 0);

		
//-------------------------------DEPRUEBA-------------------------------
		//new_map.attack(1,1,0,0);
		//new_map.print_units();

		//new_map.mouse_select(5,0);

//----------------------------------------------------------------------
		
		ALLEGRO_EVENT ev;
		clicked = false;
	    while(!al_get_next_event(event_queue, &ev)) { 
	      	switch (ev.type) {
	      		
	      		case ALLEGRO_EVENT_TIMER : 
	      			redraw = true;
	      	
	    		case ALLEGRO_EVENT_KEY_UP :
	    			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
	    				loop = false;
	    				break;
	    			}
	    			
	    			/*switch (ev.keyboard.keycode) {
	    				case ALLEGRO_KEY_ESCAPE :
	    					loop = false;
	    			}*/

	    		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
	    			if(!clicked) {
		    			if(ev.mouse.button == 1) {
			    			new_map.mouse_select(ev.mouse.x, ev.mouse.y); 

		    			} else if(ev.mouse.button == 2) {
		    				new_map.move(new_map.current_x(), new_map.current_y(), ev.mouse.x/32, ev.mouse.y/32);
		    			}
		    			clicked = true;
	    			}
	    		}
	    	}
		}
		//	ALLEGRO_KEYBOARD_STATE *key_state = new ALLEGRO_KEYBOARD_STATE;
		//	al_get_keyboard_state(key_state);
		//	if(al_key_down(key_state, ALLEGRO_KEY_ESCAPE)) {break;}
		

		if(redraw) {
			new_map.update_anims();	
			redraw = false;
			
			al_set_target_bitmap(main_buf);
			al_draw_scaled_bitmap(temporary_buf, 0.0, 0.0, 1024.0, 768.0, 0.0, 0.0, (float)resx, (float)resy, 0);
			al_set_target_bitmap(temporary_buf);

			al_flip_display();
		}
	}

	//new_map.print_units();

	return 0;
}