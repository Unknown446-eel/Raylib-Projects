#include "raylib.h"
#include <iostream>

namespace constants { 
    constexpr int numberOfTiles{10};
    constexpr int tilesWidth{50};
    constexpr int tilesHeight{50};
    constexpr int width{tilesWidth*numberOfTiles};
    constexpr int height{tilesHeight*numberOfTiles};
    constexpr Color colors[10] = {DARKGRAY, LIGHTGRAY, BLUE, VIOLET, GOLD, PURPLE, MAGENTA, SKYBLUE, GRAY, DARKBROWN};

}

struct Board {
    Color tile1{DARKGRAY};
    Color tile2{LIGHTGRAY};
} board1;

void pickColor(Board& board);


int main(void){

    InitWindow(constants::width, constants::height, "Chessboard");
    SetTargetFPS(60);


    while(!WindowShouldClose()){

        pickColor(board1);


        BeginDrawing();

            ClearBackground(RAYWHITE);

            for(int i{0}; i < constants::numberOfTiles; ++i ){
                for(int j{0}; j < constants::numberOfTiles; ++j){

                    Color tilecolor =( (i+j)%2 == 0 )? board1.tile1: board1.tile2;
                    
                    DrawRectangle((j)*constants::tilesWidth,(i)*constants::tilesHeight, 
                                constants::tilesWidth, constants::tilesHeight,tilecolor );

                }
            }

        EndDrawing();
    }
    


    CloseWindow();
    return 0;
}

void pickColor(Board& board){

    for(int i{KEY_ZERO}, j{0}; i <= KEY_NINE; ++i, ++j){
        if(IsKeyDown(i) && !IsKeyDown(KEY_LEFT_SHIFT)){
            board.tile1=constants::colors[j];
        }
        if(IsKeyDown(i) && IsKeyDown(KEY_LEFT_SHIFT)){
            board.tile2=constants::colors[j];
        }
    }

}