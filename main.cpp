#include "raylib.h"
#include <cmath>
#include <string>


enum GameState {
    Inspect,
    Angry,
    Victory,
    Game_Over 
};

enum PersonType{Knight , Noble , Monster , Ogre };

struct Person{
    PersonType type ;
    bool hasMud ;
    bool hasWeapon;
    bool paid;
    bool isRuleBroken;
    float x,y; 
};

Person CreateRandomPerson(){
    Person p;
    p.type = (PersonType)GetRandomValue(0,3);
    p.hasMud = GetRandomValue(0,1);
    p.hasWeapon = GetRandomValue(0,1);
    p.paid = GetRandomValue(0,1);

    p.isRuleBroken = (p.hasMud||p.hasWeapon||!p.paid);
    p.x = 450.0f ;
    p.y = 250.0f ;
    return p ;
}

const int width = 800;
const int height = 600;

int main(){
    InitWindow(1920,1080,"Little_Guy");
    ToggleFullscreen();
    SetTargetFPS(60);

    GameState state  = Inspect ;
    Person curPerson = CreateRandomPerson();

    int score = 0;
    int strikes = 0;
    int puppyEyesLeft = 3;
    const char* message = "press [1] to let in , [2] to reject";

    Color bootColors[4] = {LIGHTGRAY , GOLD , MAROON, DARKGREEN};
    const char* bootNames[4] = {"Knight" , "Noble", "Monster", "Ogre"};

    while (!WindowShouldClose())
    {
        if ((IsKeyPressed(KEY_F11))) ToggleFullscreen();
        
        switch(state){
            case Inspect:{
                curPerson.y = 250.0f;

                if (IsKeyPressed(KEY_ONE))
                {
                    if (curPerson.isRuleBroken)
                    {
                        strikes++;
                        message = "Boss: They broke a rule! Pay attension (+1 Strike)";
                    }
                    else
                    {
                        score++;
                        message = "Good Job!!";
                    }
                    curPerson = CreateRandomPerson();
                }

                if (IsKeyPressed(KEY_TWO))
                {
                    if (!curPerson.isRuleBroken)
                    {
                        strikes++;
                        message = "Boss: They followed the rules , Why Reject Them !!!!! (+1 Strike)";
                        curPerson = CreateRandomPerson();
                    }
                    else
                    {
                        state = Angry;
                        message = "GIANT IS MAD!! Press [SPACE] 'I'm just a little guy!' or [1] to cave in.";
                    }
                }

                if (strikes >= 3)
                {
                    state = Game_Over;
                }
                if (score >= 10)
                {
                    state = Victory;
                }
            } break;

            case Angry:{
                curPerson.y = 100.0f;

                if (IsKeyPressed(KEY_SPACE) && puppyEyesLeft >0 )
                {
                    puppyEyesLeft--;
                    score++;
                    message = "You did puppy eyes! Giant felt guilty and left.";
                    curPerson = CreateRandomPerson();
                    if (score >=10)
                    {
                        state = Victory;
                    }
                    else
                    {
                        state = Inspect;
                    }
                    
                    
                }

                else if (IsKeyPressed(KEY_ONE))
                {
                    strikes++;
                    message = "You caved in so you wouldn't get squished (+1 strikes)";
                    curPerson = CreateRandomPerson();
                    if (strikes >=3)
                    {
                        state = Game_Over;
                    }
                    else
                    {
                        state = Inspect;
                    }
                }
            } break;

            case Game_Over:
            case Victory:{
                if (IsKeyPressed(KEY_R))
                {
                    score = 0;
                    strikes = 0;
                    puppyEyesLeft = 3;
                    curPerson = CreateRandomPerson();
                    state = Inspect;
                    message = "New Shift Started!! , [1] to let in , [2] to reject.";
                }
            } break;
        }
        

        BeginDrawing();
        ClearBackground(DARKBROWN);

        DrawRectangle(0,800,1920,280,BROWN);
        DrawRectangle(curPerson.x , curPerson.y, 300,550, bootColors[curPerson.type]);
        DrawText(bootNames[curPerson.type],curPerson.x+30 ,curPerson.y+40, 40, BLACK);
        
        if (curPerson.hasMud)
        {
            DrawCircle(curPerson.x+80,curPerson.y +500, 45, DARKGRAY);
            DrawText("MUD", curPerson.x+55, curPerson.y +490, 25, WHITE);
        }
        if (curPerson.hasWeapon)
        {
            DrawRectangle(curPerson.x-100,curPerson.y +300 , 80,250, RED);
            DrawText("SWORD",curPerson.x -95, curPerson.y +400 , 20 ,WHITE);
        }


        Color mycol = (state == Angry) ? SKYBLUE : GREEN;

        DrawRectangle(1150 , 680 , 100,120, mycol);
        DrawText("LIL GUY",1155,720,20,BLACK);

        DrawRectangle(1000,760,450,220,BEIGE);
        DrawText("RULES:\n1. No Mud\n2.No Sword\n3. Must Pay Coin",1030,780,30,BLACK);

        if (curPerson.paid)
        {
            DrawCircle(1350,760,40,GOLD);
            DrawText("PAID",1325 , 750 , 20 ,BLACK);
        }


        DrawText(TextFormat("Score: %d / 10", score), 50, 40, 40, WHITE);
        DrawText(TextFormat("Strikes: %d / 3", strikes), 450, 40, 40, RED);
        DrawText(TextFormat("Puppy Eyes Left: %d", puppyEyesLeft), 850, 40, 40, PINK);

        DrawRectangle(0, 980, 1920, 100, BLACK);
        DrawText(message, 50, 1015, 32, YELLOW);


        if (state == Game_Over)
        {
            DrawRectangle(0,0,1920,1080,BLACK);
            DrawText("GAME OVER! YOU WERE FIRED!",550,450,50,RED);
            DrawText("Press [R] to Try Again" , 720 , 550, 35, WHITE);
        }

        else if (state == Victory)
        {
            DrawRectangle(0,0,1920,1080,BLACK);
            DrawText("YOU WIN! SHIFT COMPLETE",600,450,50,GREEN);
            DrawText("Press [R] to Try Again" , 720 , 550, 35, WHITE);
        }
        
        
        EndDrawing();


    }

    CloseWindow();
    

    return 0;
}