#include "lightbar.h"

Lightbar::Lightbar(int r, int c)
{
   x = new int(r);
   y = new int(c);
   size = new int(0);
   light = NULL;
   altSide[0] = &Lightbar::altBegin;
   altSide[1] = &Lightbar::altEnd;
   for(int i = 0; i < 256; i++)
      command[i] = &Lightbar::nothing;
   command[97] = &Lightbar::altEnds;
   command[98] = &Lightbar::moveRight;
   command[99] = &Lightbar::moveLeft;
   command[100] = &Lightbar::centerOutward;
}
Lightbar::~Lightbar()
{
   delete x;
   delete y;
   delete size;
   delete begin;
   delete end;
   delete light;
}
void Lightbar::executeCommand(int key)
{
   (this->*command[key])();     
}
void Lightbar::createLight(int x)
{
   *size = x;
   begin = new int(0);
   end = new int(*size - 1);
   light = new char[*size + 1];
   for(int i = 1; i < *size; i++)
      *(light+i) = '-';
   *(light+*begin) = '<';
   *(light+*end) = '>';
   *(light+*size) = '\0';
}
void Lightbar::moveLeft()
{
   attron(COLOR_PAIR(WHITEONBLUE));
   int *current = new int(*end);
   mvprintw(*x, *y+*current, "*");
   int *input = new int;
   while((*input = kbinput()) == 99) //while input is c
   {
      int *previous = new int(*current);
      *current = (*current == *begin) ? *end : *current-1;
      mvprintw(*x, *y+*current, "*");
      mvprintw(*x, *y+*previous, "%c", *(light+*previous));
      refresh();
      delete previous;
   }
   display();
   attroff(COLOR_PAIR(WHITEONBLUE));    
   delete current;
   delete input;
}
void Lightbar::moveRight()
{
   attron(COLOR_PAIR(WHITEONBLUE));
   int *current = new int(*begin);
   mvprintw(*x, *y, "*");
   int *input = new int;
   while((*input = kbinput()) == 98) //while input is b
   {
      int *previous = new int(*current);
      *current = (*current == *end) ? *begin : *current+1;
      mvprintw(*x, *y+*current, "*");
      mvprintw(*x, *y+*previous, "%c", *(light+*previous));
      refresh();
      delete previous;
   }
   display();
   attroff(COLOR_PAIR(WHITEONBLUE));      
   delete current;
   delete input;
}
void Lightbar::altEnds()
{
   attron(COLOR_PAIR(WHITEONBLUE));
   bool toggle = true;
   int *input = new int;
   while((*input = kbinput()) == 97) //while input is a or the same
   {  
      (this->*altSide[toggle])();
      mvprintw(*x, *y+*begin, "%c", *(light+*begin));
      mvprintw(*x, *y+*end, "%c", *(light+*end));
      toggle = !toggle;
      refresh();
   }
   *(light+*begin) = '<';
   *(light+*end) = '>';
   display();
   attroff(COLOR_PAIR(WHITEONBLUE));
   delete input;    
}
void Lightbar::altBegin()
{
   *(light+*begin) = '*';
   *(light+*end) = '>';
}
void Lightbar::altEnd()
{
   *(light+*begin) = '<';
   *(light+*end) = '*';  
}
void Lightbar::centerOutward()
{
   attron(COLOR_PAIR(WHITEONBLUE));
   
   int *mid = new int(*size/2);
   if(*size%2) //if it is 1, then it is odd
   {
      int *input = new int;
      int i = 0;         
      while((*input = kbinput()) == 100)
      {
         mvprintw(*x, *y+*mid+i-1, "-");
         mvprintw(*x, *y+*mid-i+1, "-");
      
         mvprintw(*x, *y+*mid+i, "*");
         mvprintw(*x, *y+*mid-i, "*");
         
         refresh();
         if(i == *mid) 
         {
            for(int j = 0; j < 3; j++)
               blinkSide();
            i = -1;     
         }
         i++;   
      }
      delete input;
   }
   else
   {
      int *mid2 = new int(*mid-1);
      int *input = new int;
      int i = 0;         
      while((*input = kbinput()) == 100)
      {
         mvprintw(*x, *y+*mid+i-1, "-");
         mvprintw(*x, *y+*mid2-i+1, "-");
      
         mvprintw(*x, *y+*mid+i, "*");
         mvprintw(*x, *y+*mid2-i, "*");
         
         refresh();
         if(i == *mid2) 
         {
            for(int j = 0; j < 3; j++)
               blinkSide();
            i = -1;     
         }
         i++;   
      }
      delete mid2;
      delete input; 
   }
   display();
   attroff(COLOR_PAIR(WHITEONBLUE));
   delete mid;
}
void Lightbar::blinkSide()
{
   int *input = new int;            
   
   mvprintw(*x, *y+*begin, "*");
   mvprintw(*x, *y+*end, "*");
   refresh();
   *input = kbinput();  
    
   mvprintw(*x, *y+*begin, "<");
   mvprintw(*x, *y+*end, ">");  
   refresh(); 
   *input = kbinput();         
}
void Lightbar::display()
{
   attron(COLOR_PAIR(WHITEONBLUE));
   for(int i = 0; i < *size; i++)
      mvprintw(*x, *y+i, "%c", *(light+i));
   refresh(); 
   attroff(COLOR_PAIR(WHITEONBLUE));     
}
void Lightbar::nothing()
{
   //nothing     
}

