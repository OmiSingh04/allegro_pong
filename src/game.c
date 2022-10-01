#include "game.h"

#include "sound.h"


#define BAR_VELOCITY  5.0


bool detect_point(Ball ball, Player *player1, Player *player2, Dimension screen_dimensions){

	if(ball.position.x < 0){
		player2->points++;
		play_collide();
		return true;
	}

 	if(ball.position.x + ball.radius > screen_dimensions.width){
		player1->points++;
		//play_collide();
		return true;
	}

	return false;	
}

void move_bar(Bar* bar, enum y_direction direction, unsigned int screen_height){
	switch(direction){
		case UP:
			bar->position.y -= BAR_VELOCITY;
			break;
		case DOWN:
			bar->position.y += BAR_VELOCITY;
			break;
	}

	if(bar->position.y < 0)
		bar->position.y = 0;
	if(bar->position.y + bar->size.height > screen_height)
		bar->position.y = screen_height - bar->size.height;
}


void update_ball(Ball *ball, Bar bar1, Bar bar2, Dimension screen_dimensions){

	ball->position.x += ball->velocity.x;
	ball->position.y += ball->velocity.y;

	//up down collision
	if(ball->position.y <= 0 || ball->position.y >= screen_dimensions.height){
		ball->velocity.y *= -1;
		play_collide();
	}
	

	//bar collisions

	//need to do the boolean checks again. reflects even without bar.
	  
	//bar1 and ball 	
	if(bar1.position.x + bar1.size.width > ball->position.x && 
		((ball->position.y + ball->radius > bar1.position.y) && (ball->position.y < bar1.position.y + bar1.size.width))){
		ball->velocity.x *= -1;
		play_collide();
	}
		//i see the error now...

	if(bar2.position.x > ball->position.x + ball->radius && 
		/*y value cecks*/	(bar2.position.y < ball->position.y + ball->radius && bar2.position.y + bar2.size.height > ball->position.y)){
		ball->velocity.x *= -1;
		play_collide();
	}



}
