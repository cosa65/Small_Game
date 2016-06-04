CPPFLAGS= -g -std=c++11
OBJS= src/map.o src/map_graphics.o src/unit.o src/graphics_handler.o
#src/map_graphics.o
# LIBALLEGRO = $(pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_t)

#main: main.cpp $(OBJS) fastsqrt.h
#	g++ $(CPPFLAGS) main.cpp $(OBJS) -o main `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0`
main: clean $(OBJS) 
#src/main.cpp $(OBJS) 
		g++ $(CPPFLAGS) src/main.cpp -o main $(OBJS) `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0`

# sprite.o: sprite.h sprite.cpp
# 	g++ -c sprite.cpp -o sprite.o `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0`

# menu.o: menu.h menu.cpp
# 	g++ -c menu.cpp -o menu.o `pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0`

%.o: %.cpp %.h
	g++ -c $(CPPFLAGS) -o $@ $< `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0`

run:
	./main

debug:
	gdb main

clean:
	rm -f main
	rm -f src/*.o
	rm -f tmps/*.png

all: main run
	make clean