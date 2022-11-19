#include "game.h"
#include "sound.h"
#define BAR_VELOCITY  6.0

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

	//simply move the ball! but with twists
	ball->position.x += ball->velocity.x;
	ball->position.y += ball->velocity.y;


	//within screen dimensions check - 
	
	//y within 0 and screen_height
	if(ball->position.y < 0 || ball->position.y + ball->radius > screen_dimensions.height){
		play_collide();
		ball->velocity.y *= -1;
		ball->position.y += (ball->velocity.y * 5);
	}

	//if x reaches the boundaries, then its a point, i think i will handle that in detect_point function

	//now just the bar checks! i need a basic but not crappy collision detection how hard can that be...
	if((ball->position.x <= bar1.position.x + bar1.size.width) && ((ball->position.y + ball->radius > bar1.position.y) && (ball->position.y - ball->radius < bar1.position.y + bar1.size.height))){
		play_collide();
		ball->velocity.x *= -1;
		ball->position.x += 5;
	}

	if(ball->position.x + ball->radius > bar2.position.x && 
		((ball->position.y + ball->radius > bar2.position.y) && (ball->position.y - ball->radius < bar2.position.y + bar2.size.height))){
		play_collide();
		ball->velocity.x *= -1;
		ball->position.x -= 5;
	}

}
