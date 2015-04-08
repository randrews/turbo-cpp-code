#include "graph.inc"
#include <stdlib.h>

void main(){int x,y;
startgraph();randomize();
directcleargfx(15);
cleargfx(15);
getch();
for(int long n=0;n!=64000;n=n)
 {
 x=random(320);
 y=random(200);
 if(getpixel(x,y)==15)
  {
  directpixel(x,y,0);
  pixel(x,y,0);
  n++;
  }
 }
getch();
endgraph();
//system("lava.exe");
}