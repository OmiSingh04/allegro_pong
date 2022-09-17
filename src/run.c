#include <stdio.h>
#include <allegro5/allegro5.h>


#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro_primitives.h>	

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

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	must_init(queue, "event queue");

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	
	ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
    	must_init(disp, "display");
	
	must_init(al_init_primitives_addon(), "primitives");//drawing basic shapes and lines for my pong game

	must_init(al_install_audio(), "audio");
    	must_init(al_init_acodec_addon(), "audio codecs");
    	must_init(al_reserve_samples(16), "reserve samples");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));



	//Bar bar1 = {.position = {.x = }


	bool redraw = false;

	al_start_timer(timer);//generates events, as the timer increments at a constant rate

	
	while(1){

		al_wait_for_event(queue, &event);
		switch(event.type){
			case ALLEGRO_EVENT_TIMER:
				redraw = true;//time for the next draw
				break;

			case ALLEGRO_EVENT_KEY_DOWN:// any key is pressed
				if(event.keyboard.keycode == ALLEGRO_KEY_W)
										
		}	

	}	

}
