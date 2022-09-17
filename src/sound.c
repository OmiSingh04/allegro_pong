#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "sound.h"

void play_game_over(){
	al_play_sample(game_over, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void play_collide(){
	al_play_sample(collide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
