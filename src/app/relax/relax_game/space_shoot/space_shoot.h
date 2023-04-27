#include <SPI.h>
#include <TFT_eSPI.h>
#include "../relax_game.h"

#define S_MOVE_PIXEL 4
#define S_ENEMY_NUM 15
#define S_ENEMY_LINE 5

class SpaceShoot : public RelaxGame {
private:
//============================= game variables =================================
unsigned long offsetM = 0;
unsigned long offsetT = 0;
unsigned long offsetF = 0;
unsigned long offsetB = 0;
unsigned long offsetA = 0;
unsigned long offsetAF = 0;
unsigned long offsetAB = 0;
unsigned long offsetS = 0;

boolean startPrinted = false;
boolean beginGame = false;
boolean beginGame2 = true;
boolean playing_ = false;
int score = 0;
int scoreInc = 10;
int level = 1;

//---------------------Player-----------------------------------------------
int shipX = 147;
int shipY = 190;
int oldShipX = 0;
int oldShipY = 0;
int changeShipX = 0;
int changeShipY = 0;
int shipSpeed = 50;
boolean doSplode = false;
boolean fire = false;
bool auto_fire_ = false;

int fFireX[5] = {0, 0, 0, 0, 0};
int fFireY[5] = {0, 0, 0, 0, 0};
int fFireAge[5] = {0, 0, 0, 0, 0};


//--------------------------Aliens-----------------------------------------------

boolean alienLive[S_ENEMY_NUM];
int alienLiveCount = S_ENEMY_NUM;
int alienX = 7;
int alienY = 25;
int oldAlienX = 7;
int oldAlienY = 25;
int changeAlienX = 6;
int changeAlienY = 0;
int alienSpeed = 200;
int oldAlienSpeed;
int chanceOfFire = 2;

bool game_over_ = false;


//================================ bitmaps ===================================
//your starship
const int shipImgW = 14;
const int shipImgH = 16;
char const * shipImg = "ZZZZZZWWZZZZZZZZZZZYWWYZZZZZZZZZZWWWWZZZZZZZZZZWWWWZZZZZZZZZWWWWWWZZZZZZZZWWWWWWZZZZZYZZWWWWWWZZYZZYZZWWWWWWZZYZWWZZWWBBWWZZWWWWZZWBBBBWZZWWWWZWWBBBBWWZWWWWZWWWWWWWWZWWWWWWWWWWWWWWWWWRWWWWWWWWWWRWZZWWWWWWWWWWZZZZZWRRWWRRWZZZ";

//flames
const int flamesImgW = 12;
const int flamesImgH = 6;
char const * flamesImg = "RZZZZZZZZZZRRZRYYRRYYRZRRZRYYRRYYRZRZZRYRZZRYRZZZZZRZZZZRZZZZZZRZZZZRZZZ";

//alien
const int alienImgW = 14;
const int alienImgH = 11;
char const * alienImg = "GGGZZZZZZZZGGGZZZGZZZZZZGZZZZZGGGGGGGGGGZZZGGGGGGGGGGGGZGGGZGGGGGGZGGGGGGZZGGGGZZGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGZZZGGZZGGZZZGZGGZGGZZGGZGGZZZZZZGZZGZZZZZ";

//ship 'sploded
const int splodedImgW = 14;
const int splodedImgH = 16;
char const * splodedImg = "ZZZZZZWWZZZZZZZZZZRYWWYRZZZYZZZRRWWRRRRZRWYZRRRRRYYRRRZWYZRYRYYRYYRRRZWWRYYYRYYYYYRZWWRYYRYRYYYYRRWWRYYYRWRYBRRZRRRYRRWWWRYRWZZRYYRRBBWRYRWWZZRYYBBBRRYBWWRZZRYYYRRYYZZWZRRWRYYRBYRZZWZZRYBRYYYYYRRZZRWWYYYWWRRRZZZZWRRWWRRRWZZZ";

private:
    void gameOver();
    void drawScore(boolean win);
     void levelUp();
    boolean alienShot(int num);
    boolean onPlayer(int num);
    boolean exceedBoundary(int num);
    int findAlienX(int num);
    int findAlienY(int num);
    int findOldAlienX(int num);
    int findOldAlienY(int num);
    void fireDaLazer();
    void keepFirinDaLazer(int bulletNo);
    void stopFirinDaLazer(int bulletNo) ;
    void moveShip();
    void drawBitmap(char img[], int imgW, int imgH, int x, int y, int scale) ;

void moveAliens();


private:
  uint16_t colorWhite;
  uint16_t colorBlue;
  uint16_t colorRed;
  uint16_t colorBlack;
  uint16_t colorMagenta;
  uint16_t colorYellow;
  TFT_eSPI* tft;

 public:
    SpaceShoot(TFT_eSPI* tft);
   ~SpaceShoot();


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

