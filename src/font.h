#ifndef FONT_H
#define FONT_H

#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>

ALLEGRO_FONT *font;
ALLEGRO_FONT *game_over_font;//need bigg size font :)

void load_fonts();
void render_points(const char*, const char*, unsigned  int, unsigned int);
void display_current_count(int);
void display_game_over(const char* winner);
#endif
