#include "font.h"
#include <stdio.h>
#include <allegro5/allegro_font.h>


void load_fonts(){
	font = al_load_ttf_font("../../assets/8-bit-hud.ttf", 28, 0);
	if(!font)
		printf("Font failedddd!!!!!");
}

void render_points(const char* name1, const char* name2, unsigned int player1, unsigned int player2){
	char points1[2] = {player1 + 48, 0};
	char points2[2] = {player2 + 48, 0};
	al_draw_text(font, al_map_rgb(255, 255, 255), 50, 50, ALLEGRO_ALIGN_LEFT, points1);
	al_draw_text(font, al_map_rgb(255, 255, 255), 1000 - 50, 50, ALLEGRO_ALIGN_RIGHT, points2);
	al_draw_text(font, al_map_rgb(255, 255, 255), 50, 800 - 50, ALLEGRO_ALIGN_LEFT, name1);
	al_draw_text(font, al_map_rgb(255, 255, 255), 1000 - 50, 800 - 50, ALLEGRO_ALIGN_RIGHT, name2);
}
