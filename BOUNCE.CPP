#include <dos.h>
#include <stdlib.h>
#include "graphics.inc"
#include <conio.h>

void main(){int dx=1,dy=dx,x,y,c=16;char k='r';
StartGfx();
randomize();
while(k!='q')
 {
 ClearGfx(0);
 y=random(190)+5;x=random(310)+5;
 while(!kbhit())
  {
//  for(int f=0;f!=10;f++)
//   {
   if(x>314 || x<6)dx*=-1;if(y>194 || y<6)dy*=-1;
   if(c>255)c=16;
   c++;x+=dx;y+=dy;
   Circle(x,y,5,c);
   delay(3);
//   }
//  ClearGfx(0);
  }
 k=getch();
 }
}
