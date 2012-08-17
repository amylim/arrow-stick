#include "keyboard.h"

int kbinput()
{
    static unsigned int previous = 11;
    unsigned int input = getch();

    if(input == ERR)
      return previous;
    else
    {
       previous = input;
       return input;
    }
}
