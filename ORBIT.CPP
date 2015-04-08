#include <dos.h>
#include "graphics.inc"

void main(){int dx=0,dy=dx,x=50,y=x,a=35;
StartGfx();
while (!kbhit())
 {
 ClearGfx(0);
 Circle(MIDX,MIDY,5,4); // Mars!
 x+=dx+1;y+=dy+1;
 Pixel(x,y,15); // Starship!
 if(x<MIDX)dx+=a/abs(MIDX-x);else dx-=a/abs(MIDX-x);
 if(y<MIDY)dy+=a/abs(MIDY-y);else dy-=a/abs(MIDY-y);
 if(x<0)x=0;if(y<0)y=0;
 if(x>MAXX)x=MAXX;if(y>MAXY)y=MAXY;
 delay(50);
 }
}