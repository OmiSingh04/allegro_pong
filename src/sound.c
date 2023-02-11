#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include<stdio.h>
#include "sound.h"


ALLEGRO_SAMPLE *game_over;
ALLEGRO_SAMPLE *collide;

void init_sound_files(){
	game_over = al_load_sample("../../assets/game-over.wav");
	collide = al_load_sample("../../assets/collide.wav");
	if(!game_over || !collide)
		printf("failed!");
}

void play_game_over(){
	al_play_sample(game_over, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void play_collide(){
	al_play_sample(collide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void destroy_sound_files(){


	al_destroy_sample(game_over);
	al_destroy_sample(collide);

	

}
