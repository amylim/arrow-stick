/**********************************************************
Author: Amy Lim
Program: CS3A Test 2 - Extra credit
Purpose: Simulation of an arrow stick for traffic advisers.
Notes: None.
**********************************************************/
#include <cstdlib>
#include <iostream>
#include <curses.h>
#include "initialize.h"
#include "keyboard.h"
#include "lightbar.h"

using namespace std;

void showMenu();

int main(int argc, char *argv[])
{
    try
    {
       cout << "Number of amber lights (8-12): ";
       int size;
       cin >> size;
    
       initialize();
       Lightbar test;
       if(size >= 8 && size <= 12)
          test.createLight(size);
       else 
          throw 100;
    
       test.display();
       showMenu();
    
       int input;
       while((input = kbinput()) != 27)
       {
          input = kbinput();
          test.executeCommand(input);
       }
    }
    catch(int x)
    {
       cout << "Invalid number of lights. " << endl;          
    }
    myExit();
    system("PAUSE");
    return EXIT_SUCCESS;
}

void showMenu()
{
   mvprintw(2,1, "a - Alternate ends of light bar");     
   mvprintw(3,1, "b - Left to right");
   mvprintw(4,1, "c - Right to left");
   mvprintw(5,1, "d - Center and outwards");
}
