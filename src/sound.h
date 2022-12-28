#ifndef SOUND_H
#define SOUND_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

ALLEGRO_SAMPLE *game_over;
ALLEGRO_SAMPLE *collide;


void init_sound_files();
void play_game_over();
void play_collide();
void destroy_sound_files();

#endif
