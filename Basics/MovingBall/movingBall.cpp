#include <raylib.h>
#include "UserInputLib.hpp"
#include "movingBall.hpp"


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



    InitWindow(constants::winWidth, constants::winHeight, "Moving Colored Ball Example");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
 
        if (IsKeyDown(KEY_RIGHT)) ball.position.x  += 5.0f;
        if (IsKeyDown(KEY_LEFT)) ball.position.x  -= 5.0f;
        if (IsKeyDown(KEY_UP)) ball.position.y -= 5.0f;
        if (IsKeyDown(KEY_DOWN)) ball.position.y += 5.0f; 

        // ball.position = GetMousePosition();

        
        ballEdgeDetection(ball, constants::winWidth, constants::winHeight);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            DrawCircleV(ball.position, ball.radius, ball.color);

        EndDrawing();


    }
    



    CloseWindow();


    return 0;
}