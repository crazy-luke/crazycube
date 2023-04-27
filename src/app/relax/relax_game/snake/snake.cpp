#include "snake.h"

Snake::Snake(TFT_eSPI* tft) {
  this->tft = tft;
  colorBlack = tft->color565(0, 0, 0);
  colorRed = tft->color565(255, 0, 0);
  colorBlue = tft->color565(0, 0, 255);
  colorWhite = tft->color565(255, 255, 255);
  gs = 1000 / gameSpeed;      // calculated gameSpeed in milliseconds
  memset(beenHeadX, 0, 470);  // initiate beenHead with a bunch of zeros
  memset(beenHeadY, 0, 470);
  dot_x_max_ = tft->width() / kDotPixel;
  dot_y_max_ = tft->height() / kDotPixel;
}
Snake::~Snake() { free(); }

void Snake::free() {
  playing_ = false;
  tft = nullptr;
}
void Snake::Init() {
  tft->fillRect(0, 0, tft->width(), tft->height(), colorBlack);  //刷新背景
  tft->setTextColor(colorWhite);  // Start notification
  tft->setTextSize(3);
  tft->setCursor(50, 100);
  tft->print("START");
  randomSeed(analogRead(6));  // make every game unique
}

void Snake::Loop() {
  if (clearScore and playing_) {  // resets score from last game, won't clear
    score = 1;                    // until new game starts so you can show off
    PrintScore();                 // your own score
    clearScore = false;
  }
  if (millis() - offsetM > gs and playing_) {
    beenHeadX[loopCount] = headX;  // adds current head coordinates to be
    beenHeadY[loopCount] = headY;  // covered later

    headX = headX + (changeX);  // head moved
    headY = headY + (changeY);

    if (headX - foodX == 0 and headY - foodY == 0) {  // food
      score += 1;
      PrintScore();
      eaten = true;
    }

    loopCount += 1;  // loopCount used for addressing, mostly

    if (loopCount > 467) {             // if loopCount exceeds size of
      clearPoint = loopCount - score;  // beenHead arrays, reset to zero
      loopCount = 0;
    }

    DrawDot(headX, headY);  // head is drawn

    if (loopCount - score >= 0) {  // if array has not been reset
      EraseDot(beenHeadX[loopCount - score], beenHeadY[loopCount - score]);
    }  // covers end of tail
    else {
      EraseDot(beenHeadX[clearPoint], beenHeadY[clearPoint]);
      clearPoint += 1;
    }

    if (eaten) {  // randomly create a new piece of food if last was eaten
      foodX = random(2, dot_x_max_ - 1);
      foodY = random(2, dot_y_max_ - 1);
      eaten = false;
    }

    DrawDotRed(foodX, foodY);  // draw the food

    if (headX > dot_x_max_ or headX < 1 or headY < 1 or
        headY > dot_y_max_) {  // Boudaries
      EndGame();
    }

    if (loopCount - score < 0) {  // check to see if head is on tail
      for (int j = 0; j < loopCount; j++) {
        if (headX == beenHeadX[j] and headY == beenHeadY[j]) {
          EndGame();
        }
      }
      for (int k = clearPoint; k < 467; k++) {
        if (headX == beenHeadX[k] and headY == beenHeadY[k]) {
          EndGame();
        }
      }
    } else {
      for (int i = loopCount - (score - 1); i < loopCount; i++) {
        if (headX == beenHeadX[i] and headY == beenHeadY[i]) {
          EndGame();
        }
      }
    }

    offsetM = millis();  // reset game loop timer
  }
}

void Snake::EndGame() {
  // tft->fillRect(3, 21, 316, 226, colorBlack); //deletes the old game
  // tft->fillScreen(colorBlack);

  tft->fillRect(0, 0, tft->width(), tft->height(), colorBlack);  //刷新背景
  eaten = true;  // new food will be created

  tft->setCursor(80, 90);  // Retry message
  tft->setTextSize(3);
  tft->setTextColor(colorWhite);
  tft->print("RETRY?");

  PrintScore();

  headX = 1;  // reset snake
  headY = 1;
  changeX = 0;
  changeY = 1;
  lastMoveH = false;

  memset(beenHeadX, 0, 470);  // clear the beenHead arrays
  memset(beenHeadY, 0, 470);  // probably not necessary

  loopCount = 0;
  clearScore = true;
  playing_ = false;  // stops game
}

void Snake::DrawDot(int x, int y) {
  tft->fillRect(kDotPixel * (x - 1), kDotPixel * (y - 1), kDotPixel, kDotPixel,
                colorWhite);
}

void Snake::DrawDotRed(int x, int y) {
  tft->fillRect(kDotPixel * (x - 1), kDotPixel * (y - 1), kDotPixel, kDotPixel,
                colorRed);
}

void Snake::EraseDot(int x, int y) {
  tft->fillRect(kDotPixel * (x - 1), kDotPixel * (y - 1), kDotPixel, kDotPixel,
                colorBlack);
}

void Snake::PrintScore() {
  //刷新背景  
  tft->fillRect(200, 220, 40, 20, colorBlack);  
  tft->setTextColor(colorBlue);
  tft->setTextSize(3);
  tft->setCursor(200, 220);
  tft->print(score);
}

void Snake::Up() {
  // lastMoveH makes sure you can't go back on yourself
  if (millis() - offsetT > gs && lastMoveH) {
    changeX = 0;  // changes the direction of the snake
    changeY = -1;
    offsetT = millis();
    lastMoveH = false;
  }
}

void Snake::Down() {
  if (millis() - offsetT > gs and lastMoveH) {
    changeX = 0;
    changeY = 1;
    offsetT = millis();
    lastMoveH = false;
  }
}

void Snake::Left() {
  if (millis() - offsetT > gs and !lastMoveH) {
    changeX = -1;
    changeY = 0;
    offsetT = millis();
    lastMoveH = true;
  }
}

void Snake::Right() {
  if (millis() - offsetT > gs and !lastMoveH) {
    changeX = 1;
    changeY = 0;
    offsetT = millis();
    lastMoveH = true;
  }
}

void Snake::Start() {
  if (millis() - offsetT > gs and !playing_) {
    //擦除文字
    tft->fillRect(80, 90, 126, 24, colorBlack);
    tft->fillRect(210, 220, 30, 20, colorBlack);
    tft->fillRect(50, 100, 100, 50, colorBlack);
    playing_ = true;
    offsetT = millis();
    PrintScore();
  }
}

bool Snake::playing() { return playing_; }