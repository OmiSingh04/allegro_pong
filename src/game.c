#include "game.h"
#include "sound.h"
#define BAR_VELOCITY  6.0


void reset_state(Bar* bar1, Bar* bar2, Ball* ball, Dimension display_dimensions, float BALL_RADIUS){
	Vector2 v_bar1 = {.x = 100, .y = 640 / 2 - 20 / 2};
	bar1->position = v_bar1;
	Vector2 v_bar2 =  {.x = 900 - 20, .y = 640 / 2 - 20 / 2};
	bar2->position = v_bar2;
	Vector2 v_ball = {.x = display_dimensions.width/2 - BALL_RADIUS/2, .y = display_dimensions.height/2 - BALL_RADIUS/2};
	ball->position = v_ball;
}

bool detect_point(Ball ball, Player *player1, Player *player2, Dimension screen_dimensions){

	if(ball.position.x < 0){
		player2->points++;
		play_game_over();
		return true;
	}

 	if(ball.position.x + ball.radius > screen_dimensions.width){
		player1->points++;
		play_game_over();
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


	//great idea, just check in the beginning if the ball has passed... the point of no return. No more weird glitch.
	//Yeah i have no game dev knowledge
	if(ball->position.x + ball->radius < bar1.position.x)
		return;


	if(ball->position.x - ball->radius > bar2.position.x + bar2.size.width)
		return;

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
