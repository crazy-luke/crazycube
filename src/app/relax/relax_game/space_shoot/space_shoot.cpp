
#include "space_shoot.h"

SpaceShoot::SpaceShoot(TFT_eSPI* tft) {
  this->tft = tft;
  colorBlack = tft->color565(0, 0, 0);
  colorRed = tft->color565(255, 0, 0);
  colorBlue = tft->color565(0, 0, 255);
  colorWhite = tft->color565(255, 255, 255);
  colorMagenta = tft->color565(255, 0, 255);
  colorYellow = tft->color565(255, 255, 0);
  memset(alienLive, true, S_ENEMY_NUM);
}
SpaceShoot::~SpaceShoot() { free(); }

void SpaceShoot::free() {
  playing_ = false;
  tft = nullptr;
}

bool SpaceShoot::playing() { return playing_; }

//=============================== setup and loop =============================
void SpaceShoot::Init() {
  tft->fillRect(0, 0, tft->width(), tft->height(), colorBlack);  //刷新背景
  tft->setTextColor(0x5E85);
  tft->setTextSize(4);

  alienLiveCount = S_ENEMY_NUM;
  alienX = 7;
  alienY = 25;
  oldAlienX = 7;
  oldAlienY = 25;
  changeAlienX = 6;
  changeAlienY = 0;
  alienSpeed = 200;
  oldAlienSpeed;
  chanceOfFire = 2;

  shipX = 147;
  shipY = 190;
  oldShipX = 0;
  oldShipY = 0;
  changeShipX = 0;
  changeShipY = 0;
  shipSpeed = 50;
  doSplode = false;
  fire = false;
  auto_fire_ = false;

  memset(fFireX, 0, 5);
  memset(fFireY, 0, 5);
  memset(fFireAge, 0, 5);

  startPrinted = false;
  beginGame = false;
  beginGame2 = true;
  playing_ = false;
  score = 0;
  scoreInc = 10;
  level = 1;
  offsetM = 0;
  offsetT = 0;
  offsetF = 0;
  offsetB = 0;
  offsetA = 0;
  offsetAF = 0;
  offsetAB = 0;
  offsetS = 0;

  game_over_ = false;
}

void SpaceShoot::Loop() {
  if(game_over_)
    return;
  //-------------Start Screen--------------
  if (millis() - offsetS >= 900 and !beginGame) {
    if (!startPrinted) {
      tft->setCursor(77, 105);
      tft->print(">START<");
      startPrinted = true;
      offsetS = millis();
    } else {
      tft->fillRect(77, 105, 240, 32, colorBlack);
      startPrinted = false;
      offsetS = millis();
    }
  }
  if (beginGame and beginGame2) {
    tft->fillRect(77, 105, 240, 32, colorBlack);
    beginGame2 = false;
    playing_ = true;
  }
  //-------------Player--------------------
  if (millis() - offsetM >= shipSpeed and playing_) {
    moveShip();
    offsetM = millis();
  }
  if (oldShipX != shipX or oldShipY != shipY) {
    tft->fillRect(oldShipX, oldShipY, 28, 44, colorBlack);
    oldShipX = shipX;
    oldShipY = shipY;
    drawBitmap((char*)shipImg, shipImgW, shipImgH, shipX, shipY, 2);
  }

  if (fire and playing_) {
    fireDaLazer();
  }
  if (millis() - offsetB >= 50) {
    for (int i = 0; i < 5; i++) {
      if (fFireAge[i] < 20 and fFireAge[i] > 0) {
        keepFirinDaLazer(i);
      }
      if (fFireAge[i] == 20) {
        stopFirinDaLazer(i);
      }
    }
    offsetB = millis();
  }

  if (millis() - offsetT > 50) {
    changeShipX = 0;
    changeShipY = 0;
  }

  //---------------Aliens-----------------------------------
  if (millis() - offsetA >= alienSpeed and playing_) {
    moveAliens();
    offsetA = millis();
  }
  if (findAlienX(4) >= 240) {
    changeAlienX = -3;
    changeAlienY = 7;
  }
  if (alienX <= 6) {
    changeAlienX = 3;
    changeAlienY = 7;
  }

  alienLiveCount = 0;
  for (int i = 0; i < S_ENEMY_NUM; i++) {
    if (alienLive[i]) {
      alienLiveCount += 1;
      if (alienShot(i)) {
        tft->fillRect(findOldAlienX(i), findOldAlienY(i), 28, 22, colorBlack);
        alienLiveCount -= 1;
        alienLive[i] = false;
        score += scoreInc;
      }
      if (onPlayer(i) or exceedBoundary(i)) {
        gameOver();
      }
    }
  }
  if (alienLiveCount == 1) {
    oldAlienSpeed = alienSpeed;
    if (alienSpeed > 50) {
      alienSpeed -= 10;
    } else {
      alienSpeed = 20;
    }
  }
  if (alienLiveCount == 0) {
    levelUp();
  }
}

void SpaceShoot::gameOver() {
  playing_ = false;
  if (doSplode) {
    drawBitmap((char*)splodedImg, splodedImgW, splodedImgH, shipX, shipY, 2);
  }
  tft->fillRect(0, 0, tft->width(), tft->height(), colorBlack);  //刷新背景
  drawScore(false);
  tft->setCursor(53, 188);
  tft->setTextColor(colorBlue);
  tft->setTextSize(3);
  tft->print("Retry?");
  game_over_ = true;
}

void SpaceShoot::drawScore(boolean win) {
    tft->setCursor(53, 40);
    tft->setTextColor(colorWhite);
    tft->setTextSize(3);
    if (win) {
      tft->print("LEVEL UP!");
    } else {
      tft->print("GAME OVER");
    }

    for (;millis() - offsetM <= 1000;) yield();

    tft->setCursor(39, 89);
    tft->setTextSize(3);
    tft->print("Score: ");
    tft->print(score);
    
    offsetM = millis();
    for (;millis() - offsetM <= 1000;) yield();

    tft->setCursor(71, 128);
    tft->print("Level: ");
    tft->print(level);

}

void SpaceShoot::levelUp() {
  playing_ = false;

  memset(alienLive, true, S_ENEMY_NUM);

  alienX = 7;
  alienY = 25;
  oldAlienX = 7;
  oldAlienY = 25;
  alienSpeed = oldAlienSpeed;
  if (alienSpeed > 100) {
    alienSpeed -= 10;
    chanceOfFire -= 10;
  } else if (alienSpeed > 50) {
    alienSpeed -= 10;
    chanceOfFire -= 5;
  } else if (alienSpeed > 25) {
    alienSpeed -= 5;
    chanceOfFire -= 1;
  }

  score += 50;
  scoreInc += 5;

  changeShipX = 0;
  changeShipY = 0;

  for (unsigned long i = millis(); millis() - i <= 1600;) {
    if (millis() - offsetM >= 20) {
      tft->fillRect(oldShipX, oldShipY, 28, 44, colorBlack);
      drawBitmap((char*)shipImg, shipImgW, shipImgH, shipX, shipY, 2);
      drawBitmap((char*)flamesImg, flamesImgW, flamesImgH, shipX + 1, shipY + 32, 2);
      oldShipX = shipX;
      oldShipY = shipY;
      shipY -= 6;
      offsetM = millis();
    }
  }

  drawScore(true);
  level += 1;
  shipX = 147;
  shipY = 190;
  for (; millis() - offsetM <= 4000;) {
  }
  tft->fillRect(0, 0, tft->width(), tft->height(), colorBlack);  //刷新背景
  offsetM = millis();
  playing_ = true;
}

boolean SpaceShoot::alienShot(int num) {
  for (int i; i < 5; i++) {
    if (fFireAge[i] < 20 and fFireAge[i] > 0) {
      if (fFireX[i] > findAlienX(num) - 4 and
          fFireX[i] < findAlienX(num) + 28 and
          fFireY[i] < findAlienY(num) + 22 and
          fFireY[i] > findAlienY(num) + 4) {
        fFireAge[i] = 20;
        return true;
      }
    }
  }
  return false;
}

boolean SpaceShoot::onPlayer(int num) {
  if (findAlienX(num) - shipX < 24 and findAlienX(num) - shipX > -28 and
      findAlienY(num) - shipY < 32 and findAlienY(num) - shipY > -22) {
    doSplode = true;
    return true;
  } else {
    return false;
  }
}

boolean SpaceShoot::exceedBoundary(int num) {
  if (findAlienY(num) > 218) {
    return true;
  } else {
    return false;
  }
}

void SpaceShoot::moveAliens() {
  for (int i = 0; i < S_ENEMY_NUM; i++) {
    if (alienLive[i]) {
      tft->fillRect(findOldAlienX(i), findOldAlienY(i), 28, 22, colorBlack);
      drawBitmap((char*)alienImg, alienImgW, alienImgH, findAlienX(i), findAlienY(i),
                 2);
    }
  }
  oldAlienX = alienX;
  oldAlienY = alienY;
  alienX += changeAlienX;
  alienY += changeAlienY;
  if (changeAlienY != 0) {
    changeAlienY = 0;
  }
}

int SpaceShoot::findAlienX(int num) {
  return alienX + 42 * (num % S_ENEMY_LINE);
}

int SpaceShoot::findAlienY(int num) {
  return alienY + 33 * (num / S_ENEMY_LINE);
}

int SpaceShoot::findOldAlienX(int num) {
  return oldAlienX + 42 * (num % S_ENEMY_LINE);
}

int SpaceShoot::findOldAlienY(int num) {
  return oldAlienY + 33 * (num / S_ENEMY_LINE);
}

//---------------------------Player----------------------------------------
void SpaceShoot::fireDaLazer() {
  int bulletNo = -1;
  for (int i = 0; i < 4; i++) {
    if (fFireAge[i] == 0) {
      bulletNo = i;
    }
  }
  if (bulletNo != -1) {
    fFireAge[bulletNo] = 1;
    fFireX[bulletNo] = shipX + 13;
    fFireY[bulletNo] = shipY - 4;
    tft->fillRect(fFireX[bulletNo], fFireY[bulletNo], 4, 3, colorMagenta);
  }
  if (!auto_fire_) fire = false;
}

void SpaceShoot::keepFirinDaLazer(int bulletNo) {
  tft->fillRect(fFireX[bulletNo], fFireY[bulletNo], 4, 4, colorBlack);
  fFireY[bulletNo] -= 8;
  tft->fillRect(fFireX[bulletNo], fFireY[bulletNo], 4, 4, colorMagenta);
  fFireAge[bulletNo] += 1;
}

void SpaceShoot::stopFirinDaLazer(int bulletNo) {
  tft->fillRect(fFireX[bulletNo], fFireY[bulletNo], 4, 4, colorBlack);
  fFireAge[bulletNo] = 0;
}

void SpaceShoot::moveShip() {
  if (shipX + changeShipX < 240 and shipX + changeShipX > 6 and
      changeShipX != 0) {
    shipX += changeShipX;
  }
  if (shipY + changeShipY > 24 and shipY + changeShipY < 192 and
      changeShipY != 0) {
    shipY += changeShipY;
  }
  if (oldShipX != shipX or oldShipY != shipY) {
    tft->fillRect(oldShipX, oldShipY, 28, 44, colorBlack);
    oldShipX = shipX;
    oldShipY = shipY;
    drawBitmap((char*)shipImg, shipImgW, shipImgH, shipX, shipY, 2);
  }
}

void SpaceShoot::drawBitmap(char img[], int imgW, int imgH, int x, int y,
                            int scale) {
  uint16_t cellColor;
  char curPix;
  for (int i = 0; i < imgW * imgH; i++) {
    curPix = img[i];
    if (curPix == 'W') {
      cellColor = colorWhite;
    } else if (curPix == 'Y') {
      cellColor = colorYellow;
    } else if (curPix == 'B') {
      cellColor = colorBlue;
    } else if (curPix == 'R') {
      cellColor = colorRed;
    } else if (curPix == 'G') {
      cellColor = 0x5E85;
    }
    if (curPix != 'Z' and scale == 1) {
      tft->drawPixel(x + i % imgW, y + i / imgW, cellColor);
    } else if (curPix != 'Z' and scale > 1) {
      tft->fillRect(x + scale * (i % imgW), y + scale * (i / imgW), scale,
                    scale, cellColor);
    }
  }
}

void SpaceShoot::Up() {
  if (millis() - offsetT >= 50 and playing_) {
    changeShipX = 0;
    changeShipY = -S_MOVE_PIXEL;
    offsetT = millis();
  }
}

void SpaceShoot::Down() {
  if (millis() - offsetT >= 50 and playing_) {
    changeShipX = 0;
    changeShipY = S_MOVE_PIXEL;
    offsetT = millis();
  }
}

void SpaceShoot::Left() {
  if (millis() - offsetT >= 50 and playing_) {
    changeShipX = -S_MOVE_PIXEL;
    changeShipY = 0;
    offsetT = millis();
  }
}

void SpaceShoot::Right() {
  if (millis() - offsetT >= 50 and playing_) {
    changeShipX = S_MOVE_PIXEL;
    changeShipY = 0;
    offsetT = millis();
  }
}

void SpaceShoot::Start() {
  if(!playing_){
    Init();
    fire = true;
    beginGame = true;
    auto_fire_ = true;
    playing_ =true;
  }
}