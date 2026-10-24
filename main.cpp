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
                    state = Inspect ;
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
        





        EndDrawing();


    }

    CloseWindow();
    

    return 0;
}