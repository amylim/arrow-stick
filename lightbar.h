#ifndef _LIGHTBAR
#define _LIGHTBAR

#include "initialize.h"
#include "keyboard.h"
#include <curses.h>

using namespace std;

class Lightbar
{
  public:
     Lightbar(int r = 12, int c = 32);
     ~Lightbar();
     void createLight(int x);
     void moveLeft();
     void moveRight();
     void altEnds();
     void centerOutward();
     void display();
     void nothing();
     void executeCommand(int key);
     
  private:
     int *x, *y, *size, *begin, *end;  
     char *light;
     void (Lightbar::*altSide[2])(); 
     void (Lightbar::*command[256])();
     void altBegin();
     void altEnd(); 
     void blinkSide();   
      
      
};



#endif
