#include "xgraph.cpp"
#include "mouse.cpp"
#include <conio.h>

void main(){int ox,oy=-1;
startgraph();
actpage(0);
cleargfx(0);
vispage(0);
setminmaxx(0,319*2);
setminmaxy(0,199);
setmousexy(319,100);
while(!kbhit())
 {
 readmouse();mousex>>=1;
 if(mousex!=ox||mousey!=oy)
  {
  //pixel(mousex,mousey,15);
  //pixel(ox,oy,0);
  line(160,100,ox,oy,0);
  line(160,100,mousex,mousey,15);
  ox=mousex,oy=mousey;
  }
 }
}