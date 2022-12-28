#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


char player_a_char = 'A';
char player_b_char = 'B';

int position_player_a;
int position_player_b;

int ai_angle = 25;
float ai_speed = 25;

int width = 100;
int game = 1;
int option;
int winner;
int shot_position = -1;
int shot_position_ai = -1;


float const g = 9.81;

void main()
{

    srand(time(0));
    position_player_a = (rand() % (50 - 1 + 1)) + 1;
    position_player_b = (rand() % (100 - 51 + 1)) + 51;


    ai_speed = ((rand() % (100 - 30 + 1)) + 30);


    while(game == 1){


        renderGame();

        printf("Enter your option: ");
        scanf("%d",&option);


        switch (option){

            case 1:
                movePlayerA(1);
                system("cls");
                renderGame();
                break;

            case 2:
                movePlayerA(-1);
                system("cls");
                renderGame();
                break;

            case 3:
                shoot();
                system("cls");

                renderGame();
                checkOutOfRange(0);

                sleep(2);
                system("cls");
                renderGame();

                break;
        }



        if(game){
            sleep(1);
            system("cls");

            runAI();

            system("cls");

            renderGame();
            checkOutOfRange(1);

            sleep(2);

            system("cls");
        }






 // Game while end
    }


    if(winner){
        system("cls");
        printf("\n\nCongratz!!\n\nYou WIN!\n\n");
    }else{
        system("cls");
        printf("\n\nGame OVER!\n\nYou lose!\n\n");
    }
}

void checkOutOfRange(int ai){



        if(ai){
            if(shot_position_ai > width || (shot_position_ai < 0 && shot_position_ai != -1)){
                printf("Out of Range!\n");
            }
            shot_position_ai = -1;
        }else{
            if(shot_position > width || (shot_position < 0 && shot_position != -1)){
                printf("Out of Range!\n");
            }
            shot_position = -1;
        }

}


void renderGame(){



 for(int i=0;i<15;i++){
            printf("\n");
        }


        for(int i = 0; i < width; i++){

            if(i == position_player_a ){
                printf("%c",player_a_char);
            }else if(i == position_player_b){
                 printf("%c",player_b_char);
            }else if(i == shot_position || i == shot_position_ai){
                printf("*");
            }else{
                printf("_");
            }
        }


        for(int i=0;i<2;i++){
            printf("\n");
        }

        printf("1 - move player A forward \n");
        printf("2 - move player A backward \n");
        printf("3 - Shoot \n");


        for(int i=0;i<4;i++){
            printf("\n");
        }

}



void shoot()
{

    int angle,speed;
    printf("Enter shooting angle: ");
    scanf("%d",&angle);

    printf("Enter shooting speed (km/h):");
    scanf("%d",&speed);


    float converted_speed = speed / 3.6;

    int range = ((converted_speed*converted_speed)/g)*sin((angle*(M_PI/180))*2);

    shot_position = position_player_a + abs(range);

    if(shot_position == position_player_b){
        player_b_char = 'X';
        game = 0;
        winner = 1;
    }


}


void movePlayerA(int move)
{

    if(position_player_a > 0 || position_player_a < width){
        position_player_a = position_player_a + move;
    }
}


void runAI(){

    float converted_speed = ai_speed / 3.6;

    int range = ((converted_speed*converted_speed)/g)*sin((ai_angle*(M_PI/180))*2);

    shot_position_ai = position_player_b - abs(range);

    if(shot_position_ai == position_player_a){
        player_a_char = 'X';

        game = 0;
        winner = 0;
    }

    if(shot_position_ai < position_player_a ){


        if((player_a_char-shot_position_ai)>8){
            ai_angle = ai_angle + 5;
            ai_speed = ai_speed - 13;
        }else{
            ai_angle = ai_angle + 1;
            ai_speed = ai_speed - 4;
        }


        checkAI_angle_speed();

    }

    if(shot_position_ai > position_player_a ){

        if((shot_position_ai - position_player_a)<8){
            ai_speed = ai_speed + 5;
            ai_angle = ai_angle - 1;
        }else{
            ai_speed = ai_speed + 14;
            ai_angle = ai_angle - 4;
        }


    }
}




void checkAI_angle_speed(){


        if(ai_angle > 80){
            ai_angle = 10;
        }

        if(ai_angle < 10){
            ai_angle = 20;
        }

        if(ai_speed < 25){
            ai_speed = 20;
        }


         if(ai_speed > 200){
            ai_speed = 60;
        }

}


