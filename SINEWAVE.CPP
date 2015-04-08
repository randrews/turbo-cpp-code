#include <conio.h>
#include "graphics.inc"

void main(){int c,y;double s,z;
StartGfx();
for(int x=0;x!=MAXX;x++)
 {
 s=sin(x/5-MIDX)*3.14;
 c=cos(x/5-MIDY)*3.14;
 c=s;y=z;
 Pixel(MIDX+2*c,MIDY+2*y,15);
 }
getch();
}