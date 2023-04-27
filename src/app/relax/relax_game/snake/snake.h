/**
 * @file snake.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 贪食蛇
 * @version 1.0
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <SPI.h>
#include <TFT_eSPI.h>
#include "../relax_game.h"

class Snake : public RelaxGame {
 private:
  float gameSpeed = 3;        // Higher numbers are faster
  boolean playing_ = false;      // will not start without say-so
  unsigned long offsetT = 0;  // time delay for touch
  unsigned long offsetM = 0;  // time delay for main loop

  const int32_t kDotPixel = 10;  //像素点大小
  uint8_t dot_x_max_ = 0;  //X 方向 游戏空间最大长度
  uint8_t dot_y_max_ = 0;  //y 方向 游戏空间最大长度
  

  float gs;
  int headX = 1;  // coordinates for head
  int headY = 1;
  int beenHeadX[470];  // coordinates to clear later
  int beenHeadY[470];
  int changeX = 0;  // the direction of the snake
  int changeY = 1;
  boolean lastMoveH = false;  // to keep from going back on oneself
  int score = 1;
  int foodX;  // coordinates of food
  int foodY;
  boolean eaten = true;  // if true a new food will be made
  int loopCount = 0;     // number of times the loop has run
  int clearPoint = 0;    // when the loopCount is reset
  boolean clearScore = false;

  uint16_t colorWhite;
  uint16_t colorBlue;
  uint16_t colorRed;
  uint16_t colorBlack;

  TFT_eSPI* tft;


 private:
  void EndGame();
  void DrawDot(int x, int y);
  void DrawDotRed(int x, int y);
  void EraseDot(int x, int y);
  void PrintScore();

 public:
    Snake(TFT_eSPI* tft);
   ~Snake();

public:
  void Init();
  void Loop();
  void Up();
  void Down();
  void Left();
  void Right();
  void Start();

  bool playing();
  void free();
};
