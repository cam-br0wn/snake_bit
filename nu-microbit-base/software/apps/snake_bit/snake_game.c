#include <stdio.h>

// First draft of a snake game

char board[32][64];                          // 2048 bytes, global representing board state
char direction;                              // 1 byte, global to store head direction
char *dir_arr = {0, 1, 2, 3};                // 8...? bytes, 0 = N, 1 = E, 2 = S, 3 = W
unsigned char head_x, head_y, tail_x, tail_y;// 4 bytes, x and y coords of head and tail
unsigned char collision;                     // 1 byte, boolean for collision condition
unsigned char seg_add;                       // 1 byte, segment add counter
unsigned int snake_len;                      // 4 bytes, snake length
char *turn_arr[128];                         // 128 bytes


// function to initialize the snake game
void init(){

    head_x = 15;
    head_y = 31;
    direction = 0;
    seg_add = 5;

}

// function to change snake direction
// should be called via Button interrupt handler
char change_dir(char input){

    // if the turn is to the left, decrement direction
    if(input == 'L'){
        direction = dir_arr[(direction - 1) % 4];
    }
    // else if the turn is to the right, then increment direction
    else if(input == 'R'){
        direction = dir_arr[(direction + 1) % 4];
    }
    // otherwise maintain direction
    // return technically unnecessary since we are storing direction as a global
    return direction;
}

// moving the snake and checking for collision with self (Note: wall collision check handled separately)
// return 1: no collision
// return 0: collision with self
int move_snake(){

    board[head_y][head_x] = 'S';

    // Changing the coordinates of the snake's head, as well as checking for collision before doing so
    // North case
    if(direction == 0){
        if(board[head_y - 1][head_x] == 'S'){
            return 0;
        }
        head_y--;
    }
    // East case
    else if(direction == 1){
        if(board[head_y][head_x + 1] == 'S'){
            return 0;
        }
        head_x++;
    }
    // South case
    else if(direction == 2){
        if(board[head_y + 1][head_x] == 'S'){
            return 0;
        }
        head_y++;
    }
    // West case
    else{
        if(board[head_y][head_x - 1] == 'S'){
            return 0;
        }
        head_x--;
    }

    board[head_y][head_x] = 'H';

    // damn im such an idiot how on earth am i going to figure out what the new tail is now
    // I think this works but it might be shit...
    if(!seg_add){
        if(turn_arr[snake_len - 1] == 'N'){
            tail_y--;
        }
        else if(turn_arr[snake_len - 1] == 'S'){
            tail_y++;
        }
        else if(turn_arr[snake_len - 1] == 'E'){
            tail_x++;
        }
        else{
            tail_x--;
        }
    }
    
}

int check_wall_collision(){

    // first check to see if snake has hit a wall
    if(head_x < 0 || head_y < 0 || head_x > 63 || head_y > 31){
        return 1;
    }
    return 0;

}

void main(){
    char button_dir;    // local variable to main that holds Left or Right (as 'L' or 'R')

    // initialize the game conditions
    init();
    while(!collision){
        
        // for max responsiveness, I think we want to interrupt handle for button press first, then modify game conditions, then update screen

        // > INTERRUPT HANDLER CALL HERE <
        
        button_dir = the_interrupt_handler(); // PLACEHOLDER

        // UPDATE GAME STATE
        change_dir(button_dir);

        // TODO: poll the heartbeat sensor


        if(!move_snake() || check_wall_collision()){
            break;
        }
    }
}
