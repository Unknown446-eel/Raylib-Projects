#include <raylib.h>
#include "UserInputLib.hpp"
#include "bouncingBall.hpp"


int main(void){

    int colorNumber{};
    do{
        printColors();
        colorNumber = userInput::getInput<int>("Please pick a color (1-10): ");
    }while(!(colorNumber >=1 && colorNumber <=10));


    Ball ball{};
    ball.position.x = static_cast<float>(constants::winWidth/2);
    ball.position.y = static_cast<float>(constants::winHeight/2);
    ball.color = constants::colors[colorNumber-1];



    InitWindow(constants::winWidth, constants::winHeight, "Bouncing Ball with Gravity");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
 
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){  
            ball.position = GetMousePosition();
            ball.fallingSpeed = 0;
        }

        ballUpdate(ball, constants::wGravity, constants::deltaTime);
        
        ballEdgeDetection(ball, constants::winWidth, constants::winHeight);

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawCircleV(ball.position, ball.radius, ball.color);

        EndDrawing();


    }
    



    CloseWindow();


    return 0;
}