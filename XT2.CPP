#include <conio.h>
#include "xgraph.cpp"
#include "mouse.cpp"
void main(){int scr=0,buf=1;int ox,oy=-1;
startgraph();
setminmaxx(0,319*2);
setminmaxy(0,199);
setmousexy(319,100);
actpage(buf);vispage(buf);
while(!kbhit()){
readmouse();mousex=mousex>>1;
if(mousex!=ox||mousey!=oy)
 {
 pixel(ox,oy,0);
 actpage(scr);pixel(ox,oy,0);
 actpage(buf);
 ox=mousex,oy=mousey;
 pixel(mousex,mousey,15);
 if(scr==1){scr=0;buf=1;}
  else {scr=1;buf=0;}
 actpage(buf);vispage(scr);
 }
}
asm mov ax,0x3
asm int 0x10
}