#include "raylib.h"
#include <math.h>
#include <stdio.h>

int main(){
  //raylib window config
  SetTargetFPS(60);
  int width = 1200;int height = 800;
  InitWindow(width,height,"Race Car");


  //car config
  int carWidth = 60;int carHeight = 100;float carX = (width/2) - (carWidth)/2;float carY = (height/2) - (carHeight/2);
  float carSpeed = 5.00f;
  float carRotation = 90.0f;
  Vector2 carPos = {.x = 60 /2,.y= 100/2};


  //car sprite
  Image c1 = LoadImage("car.png");
  ImageRotateCCW(&c1);
  Texture2D texture = LoadTextureFromImage(c1);
  UnloadImage(c1);

  
  //background
  Texture2D bg = LoadTexture("background.png");
  Rectangle sourceRect = {
    0.0f,0.0f,(float)texture.width,(float)texture.height
  };

  //world config
  int worldWidth = 2000; 
  int worldHeight = 2000;
  int worldWidthLimit = worldWidth/bg.width ;
  int worldHeightLimit= worldHeight/bg.height;

  //Camera Config
  Camera2D camera = {0};
  camera.target =(Vector2){0,0};
  camera.offset = (Vector2){0,0};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
  while(!WindowShouldClose()){
    //Forward and steer
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) ){
      float radians = DEG2RAD * carRotation;
      carY -= sinf(radians) * carSpeed;
      carX -= cosf(radians) * carSpeed;
      if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) carRotation +=2;
      if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) carRotation -= 2;

    }
    //Backward & steer
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) ){
      float radians = DEG2RAD * carRotation;
      carY += sinf(radians) * carSpeed;
      carX += cosf(radians) * carSpeed;
      if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) carRotation +=2;
      if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) carRotation -= 2;

    }

    //reset Rotation
    if(carRotation>=360) carRotation = 0;


    BeginDrawing();

    BeginMode2D(camera);
    //Destination of texture rect
    Rectangle car = {
      .x = carX,.y = carY,.width=carHeight,.height = carWidth
    };ClearBackground((Color){122, 104, 94});

    //Drawing world / background
    for(int i = 0;i<worldWidthLimit;i++){
      for(int j = 0;j<worldHeightLimit;j++){
        DrawTexture(bg,bg.width*i,bg.height*j,WHITE);
      }
    }
    //Camera Constraints
    
   camera.offset.x = -(carX+carWidth)+width/2; 
   camera.offset.y = -(carY+carHeight)+height/2; 
    
    //Draw the car
    printf("camera.target.x = %0.2f\n", camera.offset.x+carWidth);
    printf("camera.target.y = %0.2f\n", camera.offset.y+carHeight-carY);
    printf("world LIMIT = %d\n\t\n", worldWidthLimit*bg.width/2);
    DrawTexturePro(texture,sourceRect,car,carPos,carRotation,WHITE);

    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
