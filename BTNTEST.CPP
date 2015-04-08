#include "graph.inc"
#include "mouse.cpp"
#include "button.cpp"
int r=0,g=0,b=0;

void clack(int cb){cb;
if(cb==1)palette(0,r--,g,b);
if(cb==2)palette(0,r,g--,b);
if(cb==3)palette(0,r,g,b--);
(r<0?r=0:1);
(g<0?g=0:1);
(b<0?b=0:1);
}

void click(int cb){cb;
if(cb==1)palette(0,r++,g,b);
if(cb==2)palette(0,r,g++,b);
if(cb==3)palette(0,r,g,b++);
(r>63?r=63:1);
(g>63?g=63:1);
(b>63?b=63:1);
}

void clock(int cb){cb;
gotoxy(1,1);
printf("R: %i\nG: %i\nB: %i\n",r,g,b);
do{readmouse();}
while(mouseb==cb);
mousex/=2;
}

void over(){}

void draw(int x1,int y1,int x2,int y2){
rectangle(x1,y1,x2,y2,15);
}

/*void check(int cx,int cy,int cb){
if(cx>x1&&cx<x2&&cy>y1&&cy<y2)
 {
 if(cb==0)(*over);
  else(*click)(cb);
 }
}*/

void main(){int ox=-1,oy,ob;char c;
//readmouse();
button tip=button(80,80,20,20,clack,over,draw);
button tap=button(50,50,20,20,click,over,draw);
button top=button(110,50,20,20,clock,over,draw);
startgraph();
palette(4,0,0,0);palette(1,63,0,0);
palette(2,0,63,0);palette(3,0,0,63);
tip.draw();
tap.draw();
top.draw();
while(c!=27){
readmouse();
if(ox!=mousex||oy!=mousey||mouseb!=0)
 {
 ox=mousex;oy=mousey;ob=mouseb;
 mousex/=2;
 tap.check(mousex,mousey,mouseb);
 tip.check(mousex,mousey,mouseb);
 top.check(mousex,mousey,mouseb);
 for(int n=0;n!=64;n++)
  {
  if(n<r)pixel(150+n,150,1);
   else pixel(150+n,150,0);
  if(n<g)pixel(150+n,155,2);
   else pixel(150+n,155,0);
  if(n<b)pixel(150+n,160,3);
   else pixel(150+n,160,0);
  }
 display();
 directpixel(mousex,mousey,15);
 }
if(kbhit())c=getch();
}
endgraph();
}