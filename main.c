#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

char player_user_character = 'U';
char player_ai_character  = 'C';

int game_grid_width = 119, game_grid_height = 23;
int position_player_user, position_player_user_y,position_player_ai,position_player_ai_y;
int game_grid_move_x, game = 1,winner;
int trajectory_angle = 0, trajectory_speed = 0;
int ai_destroyed = 0, user_destroyed = 0;

void generate_grid(int x_num,int y_num);
void grid_position_check(int x, int y, int x_num, int y_num);
int trajectory(int input_x, int input_angle, int input_speed);
int sinus(int x);


// Set configuration for GAME
void configuration()
{
    srand(time(0));
    // Calculate random position for players
    position_player_ai = (rand() % (100 - 51 + 1)) + 51;
    position_player_user = (rand() % (50 - 1 + 1)) + 1;

    // Calculate random movement for grid
    game_grid_move_x = (rand() % (45 - 0 + 1)) + 0;
}


// Render new game status
void renderGame(){
    system("cls");
    generate_grid(game_grid_width,game_grid_height);
    trajectory_angle = trajectory_speed = 0;
}


// Display grid
void generate_grid(int x_num,int y_num)
{
    int x,y;
    for(y=y_num;y>0;y--){
        for(x=0;x<x_num;x++){
            grid_position_check(x,y,x_num,y_num);
        }
        printf("\n");
    }
}


// Check each cell for status
void grid_position_check(int x, int y, int x_num, int y_num)
{
    char print_value = ' ';
    int printed_already = 0;


    // Coloring output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //Start Your conditions

    //set user position
    if((x==position_player_user)&&(y==sinus(x)+1)){
        position_player_user_y = y;
    }
    //set ai position
    if((x==position_player_ai)&&(y==sinus(x)+1)){
        position_player_ai_y = y;
    }

    // Generate terrain
    if((y == sinus(x))||(y < sinus(x))){

        // TODO: destroying terrain
        if(0){
            //destroyed terrain
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
            printf(" ");
        }else{
            //not destroyed terrain
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
            printf(" ");
        }
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printed_already = 1;
    }else{

        //render trajectory
        if(y == trajectory(x-position_player_user,trajectory_angle,trajectory_speed)+position_player_user_y){

            if(!ai_destroyed){
                print_value = '*';
            }

            // test shot before user
            if((y==sinus(x)+1) && (position_player_ai-x<=1 && position_player_ai-x >= 0) ){
                ai_destroyed = 1;
            }
        }


        if(y == trajectory(x+1-position_player_user,trajectory_angle,trajectory_speed)+position_player_user_y){

            // test shot after user
            if(((y==sinus(x+1)+1)) && (x+1-position_player_ai <=1 && x+1-position_player_ai >=0)){
                ai_destroyed = 1;
            }
        }

    }

    //Put user on terrain
    if((x==position_player_user)&&(y==sinus(x)+1)){

        if(user_destroyed == 1){
            winner = 0;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("X");
            printed_already = 1;
            SetConsoleTextAttribute(hConsole, saved_attributes);
            game = 0;

        }else{
            print_value = player_user_character;
        }
    }

    // Put AI on terrain
    if((x==position_player_ai)&&(y==sinus(x)+1)){

        if(ai_destroyed == 1){
            winner = 1;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("X");
            printed_already = 1;
            SetConsoleTextAttribute(hConsole, saved_attributes);
            game = 0;

        }else{
            print_value = player_ai_character;
        }

    }
    // End your conditions
    if(!printed_already){
        printf("%c", print_value);
    }
}


// User Turn
void turn_user(){

    printf("1 - Move forwards\n");
    printf("2 - Move backwards\n");
    printf("3 - Shoot\n");

    int option;
    printf("\nEnter your move: ");
    scanf("%d",&option);
    switch (option){
        case 1:
            position_player_user += 2;
            break;
        case 2:
            position_player_user -= 2;
            break;
        case 3:
        {
            printf("Enter angle: ");
            scanf("%d",&trajectory_angle);
            printf("Enter speed (m/s): ");
            scanf("%d",&trajectory_speed);
        }
            break;
    }
}


// AI Turn
void turn_ai(){

}


// Calcucalte terrain with sinus function
int sinus(int x){
    int move_x=game_grid_move_x, move_y =4;
    float width = -6.0, height = -6.5;
    float x_val = ((float)(x + move_x) )*(10.0 + width);
    int y_val = (int)(sin(x_val*(M_PI / 180.0))*(10.0 + height)) + move_y;
    return y_val;
}

// Calculate trajectory for shot
int trajectory(int input_x, int input_angle, int input_speed){
    float g = 9.81, position = (float)position_player_user;
    float angle =((float)input_angle)*(M_PI / 180.0),
            speed = (float)input_speed,
            x = (float)input_x;
    float y_val = x*tan(angle)-((g*x*x)/(2*speed*speed*cos(angle)*cos(angle)));
    return (int)y_val;
}


// MAIN
int main()
{
    //Run configuration
    configuration();
    //Start GAME
    while(game){

        renderGame();

        // Get User MOVE
        turn_user();
        renderGame();
        Sleep(2);

        /*renderGame();

        //Get AI MOVE
        turn_ai();
        renderGame();
        sleep(2);*/


    }// End game

    if(winner){
        printf("\n\n\n\t\tYou WIN!\n\n\n");
    }else{
        printf("\n\n\n\t\tYou Lose!\n\n\n");
    }
    sleep(5);
    return 0;
}
