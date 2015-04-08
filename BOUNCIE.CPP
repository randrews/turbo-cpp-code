#include "graph.inc"
#include <stdlib.h>

class dot{
public:
int x,y;
int dx,dy;
int basecol;
int color;
void colcyc();
void move();
void disp(dot r);
};

void dot::colcyc(){
color--;
if(color<basecol)color+=64;
}

void dot::move(){
x+=dx;y+=dy;
if(x>318||x<1)dx*=-1;
if(y>198||y<1)dy*=-1;
}

void dot::disp(dot r){
pixel(x,y,color);
line(x,y,r.x,r.y,color);
}

void setpal(){int n;
/*for(n=0;n!=256;n++)
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
 palette(n+192,n+32,n+32,n+32);*/
for(n=0;n!=32;n++)
 {
 palette(n,n*2,0,0);
 palette(32+n,(63-n)*2,0,0);
 }
for(n=64;n!=96;n++)
 {
 palette(n,0,n*2,0);
 palette(n+32,0,(63-n)*2,0);
 }
for(n=128;n!=160;n++)
 {
 palette(n,0,0,n*2);
 palette(n+32,0,0,(63-n)*2);
 }
for(n=192;n!=224;n++)
 {
 palette(n,n*2,n*2,n*2);
 palette(n+32,(63-n)*2,(63-n)*2,(63-n)*2);
 }
palette(0,0,0,0);
}
dot red,green,blue,white;
void init(){
randomize();
red.basecol=0;
green.basecol=64;
blue.basecol=128;
white.basecol=192;
red.color=random(64);
green.color=64+random(64);
blue.color=128+random(64);
white.color=192+random(64);
red.x=random(320);
red.y=random(199);
green.x=random(320);
green.y=random(199);
blue.x=random(320);
blue.y=random(199);
white.x=random(320);
white.y=random(199);
red.dx=1;
red.dy=1;
green.dx=-1;
green.dy=1;
blue.dx=-1;
blue.dy=-1;
white.dx=1;
white.dy=-1;
startgraph();
setpal();
}

void main(){
init();
//for(int n=0;n!=256;n++)
// pixel(n+50,50,n);
while(!kbhit())
 {
 red.disp(green);
 green.disp(blue);
 blue.disp(white);
 white.disp(red);
 red.colcyc();
 green.colcyc();
 blue.colcyc();
 white.colcyc();
 red.move();
 green.move();
 blue.move();
 white.move();
 display();
 //getch();
 }
endgraph();
}