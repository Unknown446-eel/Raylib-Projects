#include<raylib.h>
#include<iostream>

struct SpriteAnimation{

    Texture2D sprite{};
    int fWidth{0},fHeight{0};

    int cFrame{0};
    int numberOfFrames{0};
    int framesPerRow{0};
    
} spriteAnimation;


void printFrame(SpriteAnimation* spriteA);


int main(void){

    InitWindow(800 , 450, "Sprite Animations");

    spriteAnimation.sprite = LoadTexture("./Lyn_Blade_Lord_crit.png");
    spriteAnimation.fWidth = 200;
    spriteAnimation.fHeight= 200;

    const int numberOfRows = spriteAnimation.sprite.height/spriteAnimation.fHeight;
    const int numberOfColumns = spriteAnimation.sprite.width/spriteAnimation.fWidth;

    spriteAnimation.numberOfFrames = numberOfRows*numberOfColumns;
    spriteAnimation.framesPerRow = numberOfColumns;


    SetTargetFPS(60);

    const float updateTime {1.0f/35.0f};
    float runningTime{0};
    

    while(!WindowShouldClose()){

        float deltaTime = GetFrameTime();
        runningTime += deltaTime;

        BeginDrawing();

            ClearBackground(BLACK);

            if(runningTime >= updateTime){
                runningTime=0;
                printFrame(&spriteAnimation);
            }    

        EndDrawing();
    }

    UnloadTexture(spriteAnimation.sprite);

    CloseWindow();



    return 0;
}


void printFrame(SpriteAnimation* spriteA){

    float xPosition = static_cast<float>( ( spriteA->cFrame % spriteA->framesPerRow )*spriteA->fWidth );
    float yPosition = static_cast<float>( ( spriteA->cFrame / spriteA->framesPerRow )*spriteA->fHeight );

    constexpr float scaling{2};

    DrawTexturePro(spriteA->sprite, {xPosition, yPosition, static_cast<float>( spriteA->fWidth ), static_cast<float>(spriteA->fHeight)},
    {100, 0, scaling*static_cast<float>( spriteA->fWidth ), scaling*static_cast<float>(spriteA->fHeight)} ,{0,0}  , 0.0f , WHITE );

    ++spriteA->cFrame;

    if(spriteA->cFrame == spriteA->numberOfFrames){
        spriteA->cFrame =0;
    }

}