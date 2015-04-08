#include "graph.inc"
#include "mouse.cpp"
#include "slider.cpp"
#include "button.cpp"

void drw(int x1,int y1,int len,int wid,int step,int pos,char h_or_v){
rectangle(x1,y1,x1+len,y1+wid,0,CLOSED);
rectangle(x1,y1,x1+len,y1+wid,15);
switch(h_or_v)
 {
 case 'h': line(x1+pos/step,y1,x1+pos/step,y1+wid,15);
	   break;
 case 'v': line(x1,y1+pos/step,x1+wid,y1+pos/step,15);
	   break;
 }
 //line(x1+pos/step,y1,x1+pos/step,y1+wid,15);
}

slider red=slider(50,50,64,5,1,0,'h',drw);
slider blue=slider(50,60,64,5,1,0,'h',drw);
slider green=slider(50,70,64,5,1,0,'h',drw);

void main(){int ox,oy,ob=-1;
startgraph();
palette(1,63,0,0);
palette(2,0,63,0);
palette(3,0,0,63);
readmouse();
red.draw();
blue.draw();
green.draw();
while(!kbhit())
 {
 readmouse();
 if(mousex!=ox||mousey!=oy||mouseb!=ob)
  {
  ox=mousex,oy=mousey,ob=mouseb;mousex/=2;
  red.check(mousex,mousey,mouseb);
  blue.check(mousex,mousey,mouseb);
  green.check(mousex,mousey,mouseb);
  palette(0,red.pos,green.pos,blue.pos);
  display();
  palette(15,63-red.pos,63-green.pos,63-blue.pos);
  directpixel(mousex,mousey,15);
  }
 }
}