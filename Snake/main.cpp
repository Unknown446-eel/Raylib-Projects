#include "raylib.h"
#include <iostream>
#include <random>

namespace constants{
    constexpr int tilesPerRow{4};
    constexpr int tileSideLength{50};
    constexpr int windowSideLength{tilesPerRow*tileSideLength};
    constexpr int DoesNotExist{-2};
}



struct Board {
    const Color tile1{DARKGRAY};
    const Color tile2{LIGHTGRAY};


} sBoard;

struct Apple{
    const Color appleSkin{RED};
    Vector2 position{1, 1};
}apple1;


class Snake{
    private:
        const Color skin {DARKGREEN};
        const Color eyes {BLACK};
        int currentNumberOfParts{2}; 
        Vector2 positions[constants::tilesPerRow*constants::tilesPerRow]{ {2 ,2}, {1,2}};
        int direction{1}; // 1=right, 2=up, 3=left, 4=down

    public:
        Snake();
        void DrawSnake();
        void MoveSnake();
        void SnakeAteApple(Apple& apple);
        bool IsSnakeDead();
        bool SnakeWin();

};


void DrawBoard(Board& board);
void DrawApple(Apple& apple);


int main (void){

    constexpr int side{constants::windowSideLength};

    InitWindow(side, side, "SnakeGame");
    SetTargetFPS(3);

    Snake snake1;

    while(!WindowShouldClose()){
    
    snake1.SnakeAteApple(apple1);
    snake1.MoveSnake();



    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawBoard(sBoard);
        DrawApple(apple1);
        snake1.DrawSnake();

    EndDrawing();

    if(snake1.IsSnakeDead()){

    break;
    }

    if(snake1.SnakeWin()){

        break;
    }

    }

    
    

    CloseWindow();
    return 0;
}


void DrawBoard(Board& board){

    constexpr int sLength{ constants::tileSideLength};
    Color tilecolor{};
    
    for(int i{0}; i < constants::tilesPerRow; i++){
        for(int j{0}; j < constants::tilesPerRow; j++ ){

            tilecolor = ((i+j)%2 == 0) ? board.tile1 : board.tile2;

            DrawRectangle(j*sLength, i*sLength, sLength, sLength, tilecolor);
        }
    }

}

void DrawApple(Apple& apple){
    constexpr int sLength{ constants::tileSideLength};
    DrawRectangle(apple.position.x*sLength, apple.position.y*sLength, 
        sLength, sLength, apple.appleSkin);
}

Snake::Snake() {
    constexpr int maxNumberOfParts{constants::tilesPerRow*constants::tilesPerRow};
    for(int i{1}; i < maxNumberOfParts; i++){
        this->positions[i] = {constants::DoesNotExist, constants::DoesNotExist};
    }
};

void Snake::DrawSnake(){
    
    constexpr int sLength{ constants::tileSideLength};

    for(int i{0}; i < this->currentNumberOfParts; i++ ){
        DrawRectangle(this->positions[i].x*sLength, this->positions[i].y*sLength, 
            sLength, sLength, this->skin);
    }

    Vector2 basePos = this->positions[0];

    switch(this->direction){

        case 1:{

            DrawCircle( (basePos.x+1)*sLength - 15 , basePos.y*sLength + 15, 5, this->eyes);
            DrawCircle( (basePos.x+1)*sLength - 15 ,(basePos.y+1)*sLength - 15, 5, this->eyes);

        }
        break;

        case 2:{

            DrawCircle( (basePos.x)*sLength + 15 ,(basePos.y)*sLength + 15, 5, this->eyes);
            DrawCircle( (basePos.x+1)*sLength - 15 , (basePos.y)*sLength + 15, 5, this->eyes);

        }

        break;

        case 3:

            DrawCircle( (basePos.x)*sLength + 15 ,(basePos.y)*sLength + 15, 5, this->eyes);
            DrawCircle( (basePos.x)*sLength + 15 , (basePos.y+1)*sLength - 15, 5, this->eyes);

        break;

        case 4:

            DrawCircle( (basePos.x)*sLength + 15 ,(basePos.y+1)*sLength - 15, 5, this->eyes);
            DrawCircle( (basePos.x+1)*sLength - 15 , (basePos.y+1)*sLength - 15, 5, this->eyes);


        break;
    }

}

void Snake::MoveSnake(){

    if (IsKeyDown(KEY_DOWN) && this->direction != 2) this->direction = 4;
    if (IsKeyDown(KEY_LEFT) && this->direction != 1) this->direction = 3;
    if (IsKeyDown(KEY_UP) && this->direction != 4) this->direction = 2;
    if (IsKeyDown(KEY_RIGHT) && this->direction != 3) this->direction = 1;


    for(int i{this->currentNumberOfParts-1}; i > 0; i--){
        this->positions[i] = this->positions[i-1];
    }
    
    switch(this->direction){
        case 1:
            this->positions[0].x +=1;
            break;

        case 2:
            this->positions[0].y -=1;
            break;

        case 3:
            this->positions[0].x -=1;
            break;

        case 4:
            this->positions[0].y +=1;
            break;
    }

}

void Snake::SnakeAteApple(Apple& apple){

    if(this->positions[0].x == apple.position.x  && this->positions[0].y == apple.position.y){
        this->currentNumberOfParts++;
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution randomTile{0 , constants::tilesPerRow-1 };

        bool validPosition{true};

        do{

            apple.position = {static_cast<float>(randomTile(mt)), 
            static_cast<float>(randomTile(mt))};

            for(int i{0}; i < this->currentNumberOfParts-1; i++){

                if(apple.position.x == this->positions[i].x && apple.position.y == this->positions[i].y){
                    validPosition = false;
                    break;
                }else{
                    validPosition = true;
                }

            }

        }while(!validPosition);
    }
}

bool Snake::IsSnakeDead(){

    if(this->positions[0].x < 0 || this->positions[0].x >= constants::tilesPerRow  ||
        this->positions[0].y < 0 || this->positions[0].y >= constants::tilesPerRow)
    {
        return true;
    }

    for(int i{1}; i < this->currentNumberOfParts - 1; i++ ){
        if( (this->positions[0].x == this->positions[i].x) && 
            (this->positions[0].y == this->positions[i].y) ){
                return true;
            }
    }

    return false;
}

bool Snake::SnakeWin(){
    if(this->currentNumberOfParts == constants::tilesPerRow*constants::tilesPerRow){
        return true;
    }
    return false;
}

