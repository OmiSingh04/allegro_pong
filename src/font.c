#include "font.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>

ALLEGRO_FONT *font;
ALLEGRO_FONT *game_over_font;//need bigg size font :)

void load_fonts(){
	font = al_load_ttf_font("../../assets/8-bit-hud.ttf", 28, 0);
	game_over_font = al_load_ttf_font("../../assets/8-bit-hud.ttf", 50, 0);
	if(!font || !game_over_font)
		printf("Font failedGddd!!!!!");
}

void render_points(const char* name1, const char* name2, unsigned int player1, unsigned int player2){
	char points1[2] = {player1 + 48, 0};
	char points2[2] = {player2 + 48, 0};
	al_draw_text(font, al_map_rgb(255, 255, 255), 50, 50, ALLEGRO_ALIGN_LEFT, points1);
	al_draw_text(font, al_map_rgb(255, 255, 255), 1000 - 50, 50, ALLEGRO_ALIGN_RIGHT, points2);
	al_draw_text(font, al_map_rgb(255, 255, 255), 50, 800 - 50, ALLEGRO_ALIGN_LEFT, name1);
	al_draw_text(font, al_map_rgb(255, 255, 255), 1000 - 50, 800 - 50, ALLEGRO_ALIGN_RIGHT, name2);
}

void display_current_count(int count){
	char str[2] = {count + 48, 0};
	al_draw_text(game_over_font, al_map_rgb(255, 255, 255), 1000/2, 800/2 - 50, ALLEGRO_ALIGN_CENTER, str);
}

void display_game_over(const char* winner){

	int size = strlen(winner) + strlen(" wins!") + 1;
	char* str = malloc(size);
	memset(str, 0, size);
	strcat(str, winner);
	strcat(str, " Wins!");
		
	al_draw_text(game_over_font, al_map_rgb(255, 255, 255), 1000/2, 800/2 - 40, ALLEGRO_ALIGN_CENTER, "Game Over!");
	al_draw_text(game_over_font, al_map_rgb(255, 255, 255), 1000/2, 800/2 + 40, ALLEGRO_ALIGN_CENTER, str);
	free(str);

}
