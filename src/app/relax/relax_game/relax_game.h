#pragma once

enum class RelaxBook{
  SNAKE,
  SPACESHOOT,
};

enum class RelaxDirection{
  UNKNOW,
  LEFT,
  RIGHT,
  DOWN,
  UP,
  CENTER,
};

class RelaxGame{
 public:   
   virtual void Init() = 0;
   virtual void Loop() = 0;
   virtual void Up() = 0;
   virtual void Down() = 0;
   virtual void Left() = 0;
   virtual void Right() = 0;
   virtual void Start() = 0;
   virtual bool playing() = 0;
   virtual void free() = 0;
};