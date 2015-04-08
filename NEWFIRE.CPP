// Fire. New and improved! (Includes comments)
#include "graph.inc"
//#include "palette.cpp"
#include <stdlib.h>
//#define PATH d:\download\source\   // I discovered that you
//#include "PATH pal256.h"           // can DEFINE a path and include
				     // stuff that's all over the
				     // place easier.
void setpalette(){        // This sets up a palette for us.
for(int n=0;n!=10;n++)
 {
 palette(n,n,n,n);        // Lowering shades of gray: smoke.
 }
for(n=10;n!=32;n++)
 {
 palette(n,n*2,2*n/5,0);  // All our red shades
 }
for(n=32;n!=256;n++)
 {
 palette(n,63,40,0);      // Everything else is yellow
 }
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
}

void randline(){          // The all-important random line.
for(int n=5;n!=275;n++)   // The thing that actually burns.
 {
 if(random(10)%2!=1)pixel(n,199,random(256));
 }                        // A more likely random() statement
}                         // makes a bigger flame.
void burn(){int t;
for(int y=120;y!=199;y++) // 120 is the max height.
			  // Makes it faster to have this number higher.
 {
 for(int x=5;x!=315;x++)
  {
  t=(getpixel(x,y)+
     getpixel(x+1,y)+      // We average all the pixels around
     getpixel(x-1,y)+      // us, except the one above us.
     getpixel(x,y+1)-1)/4;
  //pixel(x+1,y-1,t);        // We offset 1 up and 1 right, to make the
  pixel(x+1,y-1,t);
  }                        // flame rise, and wind.
 }
}

void main(){
randomize();
startgraph();
setpalette();
while(!kbhit())
 {
 randline();
 burn();
 display();
 }
endgraph();
}