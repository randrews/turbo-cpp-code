// Fire. New and improved! (Includes comments)
#include "graph.inc"
#include "mouse.cpp"
#include <stdlib.h>
#include <dos.h>

void setpalette(){        // This sets up a palette for us.
/*for(int n=0;n!=256;n++)
 palette(n,0,0,0);
for(n=0;n!=32;n++)
 palette(n,63,n*2,0);
for(n=32;n!=64;n++)
 palette(n,(63-n)*2,63,0);
for(n=64;n!=96;n++)
 palette(n,0,63,n*2);
for(n=96;n!=128;n++)
 palette(n,0,(63-n)*2,63);
for(n=128;n!=160;n++)
 palette(n,n*2,0,63);
for(n=0;n!=32;n++)
 palette(n+160,(63-n),n,(63-n));
for(n=0;n!=32;n++)
 palette(n+192,n+32,n+32,n+32);
palette(0,0,0,0);*/

for(int n=0;n!=10;n++)
 {
 palette(n,n+3,n+3,n+3);        // Lowering shades of gray: smoke.
 }
palette(0,0,0,0);	// Black must be black!
for(n=10;n!=32;n++)
 {
 palette(n,n*2,2*n/5,0);  // All our red shades
 }
for(n=32;n!=256;n++)
 {
 palette(n,63,40+n/8,0);      // Everything else is yellow
 }
palette(255,63,63,63);
}

void burn(){int t;
for(int y=0;y!=200;y++)
 {
 for(int x=0;x!=320;x++)
  {
  t=(getpixel(x,y)+
     getpixel(x+1,y)+      // We average all the pixels around
     getpixel(x-1,y)+
     (y<199?getpixel(x,y+1):getpixel(x,y))-1
     )/4;      // us, except the one above us.
  pixel(x,y-1,t);
  }
 }
}

void flame(){
_fmemset(off_screen+199*320,0,321);
readmouse();mousex>>=1;
directpixel(mousex,mousey,255);
if(mouseb==0)
 {
 pixel(mousex,mousey,255);
 pixel(mousex+(random(3)-1),mousey,128);
 pixel(mousex+(random(3)-1),mousey,128);
 if(mousey<199)
  pixel(mousex,mousey+1,128);
 pixel(mousex,mousey-1,128);
 }

if(mouseb!=0)
for(int z=0; z<150; z++)
{
ellipse(mousex, mousey,z, z, 50);

}

}
void main(){
startgraph();
setpalette();
while(!kbhit())
 {
 flame();
 burn();
 display();
 }
endgraph();
}