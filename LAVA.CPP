#include "graph.inc"
//#include "palette.cpp"
#include <stdlib.h>

int d=5;

void setpalette(){int n;
for(n=0;n!=64;n++)
 {
 palette(n+1,63-n,0,n);
 palette(255-n,63-n,0,n);
 palette(n+65,n,0,63-n);
 palette(192-n,n,0,63-n);
 }
palette(0,63,0,0);
for(n=0;n!=256;n++)
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
palette(0,0,0,0);//*/
/*for(n=0;n!=128;n++)
 {
 palette(n,n/2,0,0);
 }
for(n=128;n!=256;n++)
 {
 palette(n,(255-n)/2,0,0);
 }//*/
//palette(0,0,0,0);
}

void block(int x,int y,int c){
for(int n=0;n!=d;n++)
 {
 _fmemset(off_screen+x+(y+n)*320,c,d);
 }
}

void drawbox(){
for(int n=0;n!=256;n++)
 {
 pixel(n,110,n);
 }
for(int x=0;x<320;x+=d)
 {
 for(int y=0;y<200;y+=d)
  {
  block(x,y,random(256));
  }
 }
}

void lava(){
for(int y=0;y<200;y+=d)
 {
 for(int x=0;x<320;x+=d)
  {
  block(x,y,getpixel(x,y)+1);
  }
 }
}

void main(){char c;
startgraph();randomize();
setpalette();
drawbox();
while(c!='q')
 {
while(!kbhit())
 {
 lava();
 display();
 }
c=getch();
switch(c)
 {
 case '+':
 case 'a':d++;break;
 case 'z':
 case '-':if(d!=1)d--;break;
 }
if(c!='q'){c='n';
	   drawbox();}
 }
endgraph();
}