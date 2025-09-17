#pragma once
#include <iostream>
#include <raylib.h>
#include "UserInputLib.hpp"


namespace constants {
    constexpr int winWidth{2*800};
    constexpr int winHeight{2*450};
    constexpr Color colors[10] = {RED, GREEN, BLUE, VIOLET, GOLD, PURPLE, MAGENTA, SKYBLUE, GRAY, DARKBROWN};
    constexpr float deltaTime = 0.001;
    constexpr float wGravity = 9.81*10000;
}

struct Ball
{
    Vector2 position{};
    float fallingSpeed{0};
    Color color = MAGENTA;
    int radius{50};
};

void printColors(){
    std::cout << "COLOR PICKER: \n";
    std::cout << "1.)  RED \n";
    std::cout << "2.)  GREEN \n";
    std::cout << "3.)  BLUE \n";
    std::cout << "4.)  VIOLET \n";
    std::cout << "5.)  GOLD \n";
    std::cout << "6.)  PURPLE \n";
    std::cout << "7.)  MAGENTA \n";
    std::cout << "8.)  SKYBLUE \n";
    std::cout << "9.)  GRAY \n";
    std::cout << "10.) DARKBROWN \n";
    
}

void ballEdgeDetection( Ball& ball, int windowWidth, int windowHeight){

    if( (ball.position.x + ball.radius) > windowWidth) ball.position.x = windowWidth-ball.radius;
    
    if( ball.position.x - ball.radius < 0) ball.position.x = ball.radius;

    if( (ball.position.y + ball.radius > windowHeight) ) {
        ball.position.y = windowHeight -ball.radius;
        ball.fallingSpeed *= -0.60;  
    }
    if( ball.position.y - ball.radius < 0) ball.position.y = ball.radius;
}

void ballUpdate(Ball& ball, float gravity, float deltaT ){
    ball.fallingSpeed += gravity*deltaT;
    ball.position.y += ball.fallingSpeed*deltaT +0.5*gravity*deltaT*deltaT;
}