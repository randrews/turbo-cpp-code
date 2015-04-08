#include <conio.h>
#include "xgraph.cpp"
#include "mouse.cpp"
void main(){int ox,oy,a=0,v=1;
startgraph();
actpage(a);
vispage(v);
while(!kbhit())
 {
 readmouse();mousex/=2;
 if(ox!=mousex||oy!=mousey)
  {
  ox=mousex;oy=mousey;
  //cleargfx(0);
  actpage(v);
  rectangle(ox,oy,ox+10,oy+10,0,CLOSED);
  actpage(a);
  rectangle(mousex,mousey,mousex+10,mousey+10,15,CLOSED);
  }
 v++;a++;
 if(v==2)v=0;
 if(a==2)a=0;
 vispage(v);actpage(a);
 }
}