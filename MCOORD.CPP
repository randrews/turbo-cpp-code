#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include "mouse.cpp"
void main(){char c='j';int ox,oy;
clrscr();
showmouse();
while(c!='q')
 {
 readmouse();
 if(mousex!=ox||mousey!=oy)
  {
  ox=mousex,oy=mousey;
  gotoxy(1,1);
  printf("Mousex: %i\t\nMousey: %i\t",mousex,mousey);
  }
 if(kbhit())c=getch();
 }
}