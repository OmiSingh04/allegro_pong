#include <stdio.h>
#include <allegro5/allegro5.h>


#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro_primitives.h>	

#include "game.h"

void must_init(bool test, const char *message){
	if(test)
		return;
	printf("Couldnt initialize %s\n", message);
}

int main(){

	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");
	
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	must_init(event_queue, "event queue");

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	
	ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
    	must_init(disp, "display");
	
	must_init(al_init_primitives_addon(), "primitives");//drawing basic shapes and lines for my pong game

	must_init(al_install_audio(), "audio");
    	must_init(al_init_acodec_addon(), "audio codecs");
    	must_init(al_reserve_samples(10), "reserve samples");

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(disp));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//640 * 480

	Bar bar1 = {.position = {.x = 100, .y = 640 / 2 - 20 / 2}, .size = {.width = 20, .height = 100}, .color = al_map_rgb(255, 255, 255)};

	bool game_over = false;
	bool redraw = false;
	ALLEGRO_EVENT event;
	enum y_direction direction = UP;

	al_start_timer(timer);//generates events, as the timer increments at a constant rate

	
	while(!game_over){
		printf("yeah bro");
		al_wait_for_event(event_queue, &event);
		switch(event.type){
			case ALLEGRO_EVENT_TIMER:
				redraw = true;//time for the next draw
				break;

			case ALLEGRO_EVENT_KEY_DOWN:// any key is pressed
				if(event.keyboard.keycode == ALLEGRO_KEY_W)
				 	move_bar(&bar1, UP);
				if(event.keyboard.keycode == ALLEGRO_KEY_S)
					move_bar(&bar1, DOWN);
				if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					game_over = true;
				break;						
	

			if(redraw){

				al_draw_filled_rectangle(bar1.position.x, bar1.position.y, bar1.position.x + bar1.size.width, 
							bar1.position.y + bar1.size.height, bar1.color);
				al_flip_display();
				redraw = false;
			}
		}

	}	

}
