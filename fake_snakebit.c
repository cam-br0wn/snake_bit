snake(as an vertex)
Length
position-> follows a pattern and moves
speed
direction


moving two modes

diferent directions
4 directions
if direction is up/down then buttons control right left
if direction is right left then buttons control up down
keeps track of how many times since last button was clicked...
depending on that thats how long that section is



hit snake- game over
hit end of screen- game over
apple- score up, length increase, generate new apple


apple generate: can be anywhere except for where the snake currently is

things that need to be universal variles
direction
snake array
head
apple eaten

things i need to do still
figure out:
how everything is drawn
how to make the link list of the snake
how to translate that into the screen
how to incorperate speed 

int cur_direction(int direction){
  if( direction == 1 | direction == 2 | direction ==0){
    if(right_button->pushed){
      return cur_direction = 3;
    }
    if(left_button->pushed){
      return cur_direction =4;
    }
    else if(direction == 3 | direction == 4){
      if(right_button->pushed){
        return cur_direction = 1;
      }
      if(left_button->pushed){
        return cur_direction = 2;
      }
    }
  }
}

void moving(snake_array, int cur_direction){
 if(direction == 1){
 // head.y = head.y +1;
 }
 if(direction == 2){
  // head.y = head.y -1;
 }
 if(direction == 3){
   // head.x = head.x+1;

 }
 if(direction == 4){
   // head.x = head.x-1;

 }
 if(!apple_eaten){
   //free(tail);
   //tail -> snake[snake.length]; // last element in list
 }
}

integer speed(heartbeat_sensor val){
speed = heartbeat_sensor/ some value;
return speed;
}

void new_apple(){
  // free apple
  // apple.x = random; //
  // apple.y = random; // but not soemwehre the snake is
}

bool apple_eaten(head, apple){
  if(head.x == apple.x && head.y == apple.y){
    new_apple();
    return true;
  }
}

bool lost(){
  //if(head.y<= 0 || head.y>=screen.height){
  //return true
//}
//if(head.x<=0 || head.x>= screen.length){
//  return true
//}
// (for i =1; 1++; i< head.length){
    //if head == snake[i]{
    //return true;
  //}
}
void new_game(){
  // make the snake and set it in the middle
  // direction == 0
}
void game_over(){
  // display final score;
  new_game();
}
