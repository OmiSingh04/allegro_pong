#include "game_objects.h"
bool detect_collisions(Ball *ball, Bar *bar1, Bar *bar2, Dimension *screen_dimensions){


	//display bounds check, only the top and bottom, cause the sides would mean point
	if(ball->position.y <= 0 || ball->position.y >= screen_dimensions->height)
		return true;

	//ball collides with bar - 1 - the left one
	if((ball->position.x <= bar1->position.x + bar1->size.width) && 
		(ball->position.y + ball->radius > bar1->position.y || ball->position.y < bar1->position.y + bar1->size.height))
		return true;


	if(ball->position.x + ball->radius >= bar2->position.x && (ball->position.y + ball->radius > bar2->position.y || ball->position.y < bar2->position.y + bar2->size.height))
		return true;

	return false;

}


bool detect_and_add_point(Ball *ball, Player *player1, Player *player2, Dimension *screen_dimensions){

	if(ball->position.x < 0){
		player2->points++;
		return true;
	}



 	if(ball->position.x + ball->radius > screen_dimensions->width){
		player1->points++;
		return true;
	}

	return false;	
}
