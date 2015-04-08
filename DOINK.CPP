// PRETTY.CPP
// Something pretty. Grew out of...

// GCURSOR.CPP
// An attempt to cheat at making a spiffy graphical cursor.

#include <conio.h>
#include "mouse.cpp"
#include "tile3.cpp"

void graphicsgo();

int cursor[4][100],*gp;
const int step=1;

void main(){char c;int ox=-1,oy=-1,ob=4;
		   //int clr=0;
graphicsgo();
while(c!='q')
 {
 readmouse();
 mousex/=2;
 if(ox!=mousex||oy!=mousey||ob!=mouseb)
  {
  ox=mousex;oy=mousey;
  display();
  directtile(&cursor[mouseb][0],mousex,mousey,-1);
  /*switch(mouseb)
   {
   case 1:pixel(mousex,mousey,clr);break;
   case 2:clr=getpixel(mousex,mousey);break;
   case 3:pixel(mousex,mousey,clr++);break;
   }*/
  if(mouseb!=0)tile(&cursor[mouseb][0],mousex,mousey,-1);
  }
 if(kbhit())c=getch();
 }
}

void graphicsgo(){
gp=loadtile("cursor.dat","sword0");
for(int n=0;n!=d*d;n++)
 cursor[0][n]=*(gp+n);
gp=loadtile("cursor.dat","sword1");
for(n=0;n!=d*d;n++)
 cursor[1][n]=*(gp+n);
gp=loadtile("cursor.dat","sword2");
for(n=0;n!=d*d;n++)
 cursor[2][n]=*(gp+n);
gp=loadtile("cursor.dat","sword3");
for(n=0;n!=d*d;n++)
 cursor[3][n]=*(gp+n);
startgraph();
}