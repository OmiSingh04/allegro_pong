#ifndef SOUND_H
#define SOUND_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

ALLEGRO_SAMPLE *game_over;
ALLEGRO_SAMPLE *collide;


void init_sound_files(){
	game_over = al_load_sample("../assets/game-over.wav");
	collide = al_load_sample("../assets/collide.wav");
}

void play_game_over();
void play_collide();

#endif
