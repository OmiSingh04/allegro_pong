#ifndef FONT_H
#define FONT_H

#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>

ALLEGRO_FONT *font;

void load_fonts();
void render_points(const char*, const char*, unsigned  int, unsigned int);
#endif
