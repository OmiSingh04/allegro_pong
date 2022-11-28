#include <stdio.h>
#include <stdlib.h>


#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "font.h"
#include "game.h"
#include "sound.h"
#define KEY_SEEN 1
#define KEY_RELEASED 2
#define DISPLAY_WIDTH 1000
#define DISPLAY_HEIGHT 800
#define BALL_RADIUS 15
#define CENTRE_LINE_WIDTH 5




Vector2 *generate_stars(){
	Vector2* vectors = malloc(sizeof(float) * 2 * 40);
	float* ptr = (float*) vectors;
	for(int i = 0; i < 40; i++, ptr++){
		float x = rand() % DISPLAY_WIDTH;
		float y = rand() % DISPLAY_HEIGHT;
		*ptr = x;
		*(++ptr) = y;
	}
	return vectors;
	
}


void must_init(bool test, const char *message){
	if(test)
		return;
	printf("Couldnt initialize %s\n", message);
}

int main(){
	
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");
	
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	must_init(event_queue, "event queue");

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	

	Dimension display_dimensions = {.width = 1000, .height = 800};

	ALLEGRO_DISPLAY* disp = al_create_display(display_dimensions.width, display_dimensions.height);
    	must_init(disp, "display");
		
	must_init(al_init_primitives_addon(), "primitives");//drawing basic shapes and lines for my pong game

	must_init(al_install_audio(), "audio");
    	must_init(al_init_acodec_addon(), "audio codecs");
    	must_init(al_reserve_samples(16), "reserve samples");
	must_init(al_init_font_addon(), "fonts");
	must_init(al_init_ttf_addon(), "ttf_fonts");
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(disp));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	init_sound_files();
	load_fonts();

	Player player1 = {.name = {0}, .points = 0}, player2  = {.name = {0}, .points = 0};
	printf("Player1\nEnter your name\n");
	fgets(player1.name, 20, stdin);
	player1.name[strlen(player1.name) - 1] = 0;

	printf("Player2\nEnter your name\n");
	fgets(player2.name, 20, stdin);
	player2.name[strlen(player2.name) - 1] = 0;


	Bar bar1 = {.position = {.x = 100, .y = 640 / 2 - 20 / 2}, .size = {.width = 20, .height = 100}, .color = al_map_rgb(255, 192, 203)};
	Bar bar2 = {.position = {.x = 900 - 20, .y = 640 / 2 - 20 / 2}, .size = {.width = 20, .height = 100}, .color = al_map_rgb(255, 192, 203)};
	Ball ball = {.position = {.x = DISPLAY_WIDTH/2 - BALL_RADIUS/2, .y = DISPLAY_HEIGHT/2 - BALL_RADIUS/2}, .velocity = {.x = -4, .y = -7}, BALL_RADIUS, al_map_rgb(255, 0, 0)};
	bool game_over = false;
	bool redraw = false;
	ALLEGRO_EVENT event;
	enum y_direction direction = UP;

	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	

	Vector2* stars = generate_stars();
	

	bool point = false;
	

	al_start_timer(timer);//generates events, as the timer increments at a constant rate
	while(!game_over){

				
	
		al_wait_for_event(event_queue, &event);
		switch(event.type){
			case ALLEGRO_EVENT_TIMER:
				redraw = true;//time for the next draw
				
				if(key[ALLEGRO_KEY_W])
				 	move_bar(&bar1, UP, DISPLAY_HEIGHT);

				if(key[ALLEGRO_KEY_S])
					move_bar(&bar1, DOWN, DISPLAY_HEIGHT);
				

				if(key[ALLEGRO_KEY_UP])
					move_bar(&bar2, UP, DISPLAY_HEIGHT);

				
				if(key[ALLEGRO_KEY_DOWN])
					move_bar(&bar2, DOWN, DISPLAY_HEIGHT);
				

				if(key[ALLEGRO_KEY_ESCAPE])
					game_over = true;

				for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            				key[i] &= KEY_SEEN;

				
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
				break;

			case ALLEGRO_EVENT_KEY_UP:
				key[event.keyboard.keycode] &= KEY_RELEASED;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				game_over = true;
		}

		if(game_over)
			break;
		
		update_ball(&ball, bar1, bar2, display_dimensions);
		point = detect_point(ball, &player1, &player2, display_dimensions);
		

		if(point)
			reset_state(&bar1, &bar2, &ball, display_dimensions, BALL_RADIUS);
		
		
		game_over = (!game_over && (player1.points >= 5 || player2.points >= 5))?true:false;
		if(redraw){
				
			al_clear_to_color(al_map_rgb(0, 0, 0));
			render_points(player1.name, player2.name, player1.points, player2.points);
			{//drawing them stars

				Vector2* ptr = stars;
				for(int i = 1; i <= 40; i++){
					al_draw_filled_circle(ptr->x, ptr->y, rand()%4, al_map_rgb(255, 255, 255));//oh wow its like playing a game among twinkling stars
					ptr++;
				}

			}
			
			al_draw_line(DISPLAY_WIDTH/2 - CENTRE_LINE_WIDTH/2, 0, DISPLAY_WIDTH/2 - CENTRE_LINE_WIDTH/2,
					DISPLAY_HEIGHT,  al_map_rgb(255, 255, 255), CENTRE_LINE_WIDTH);

			//DRAW A THICCC LINE RIGHT IN THE MIDDLE
			

			al_draw_filled_rectangle(bar1.position.x, bar1.position.y, bar1.position.x + bar1.size.width,
                                                 bar1.position.y + bar1.size.height, bar1.color);

			al_draw_filled_rectangle(bar2.position.x, bar2.position.y, bar2.position.x + bar2.size.width, 
						 bar2.position.y + bar2.size.height, bar2.color);

			al_draw_filled_circle(ball.position.x + (float)ball.radius/2, ball.position.y + (float)ball.radius/2, BALL_RADIUS, ball.color);



			al_flip_display();
			redraw = false;
		}

	}	

}
