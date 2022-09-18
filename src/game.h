#ifndef GAME__H
#define GAME__H

#include<stdbool.h>
#include<allegro5/allegro5.h>
#include "player.h"



enum y_direction{UP, DOWN};//I HOPE THIS IS HOW YOU USE THESE THINGS
	

typedef struct Dimension{//i think i could have just gone with using vector for dimension too, but this is way cooler.
	unsigned int width;
	unsigned int height;
} Dimension;

typedef struct Vector2{//2 Dimensional vector
	float x;
	float y;
} Vector2;


typedef struct Bar{
	Vector2 position;
	Dimension size;
	ALLEGRO_COLOR color;
} Bar;

typedef struct Ball{
	Vector2 position;
	Vector2 velocity;
	int radius;
	ALLEGRO_COLOR color;
} Ball;



bool detect__point(Ball ball, Player player1, Player player2, Dimension screen_dimensions);//when ball reaches extreme left or right, giving a point to player

void move_bar(Bar* bar, enum y_direction direction, unsigned int screen_height);

void update_ball(Ball *ball, Bar bar1, Bar bar2, Dimension screen_dimensions);

#endif
