#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#include "c:\tc\bin\bgraph.inc"
#include "c:\tc\bin\mouse.cpp"

#define up 40
#define dn 4
#define SCND 128

void burnup(){int d;
for(int x=1;x!=319;x++)
 for(int y=1;y!=199;y++)
  {
  d=getpixel(x-1,y-1)+getpixel(x,y-1)+getpixel(x+1,y-1)
   +getpixel(x-1,y)+getpixel(x,y)+getpixel(x+1,y)
   +getpixel(x-1,y+1)+getpixel(x,y+1)+getpixel(x+1,y+1);
  d/=9;
  if(getpixel(x,y)<d)pixel(x,y,d);
  }
}

void burndn(){int d;
for(int x=1;x!=319;x++)
 for(int y=1;y!=199;y++)
  {
  d=getpixel(x-1,y-1)+getpixel(x,y-1)+getpixel(x+1,y-1)
   +getpixel(x-1,y)+getpixel(x,y)+getpixel(x+1,y)
   +getpixel(x-1,y+1)+getpixel(x,y+1)+getpixel(x+1,y+1);
  d/=9;
  if(getpixel(x,y)>d)pixel(x,y,d);
  }
}

void sink(){
for(int x=1;x!=319;x++)
 for(int y=1;y!=199;y++)
  if(getpixel(x,y)>0)
   (*(buffer+x+y*320))--;
}

void buildup(){
for(int j=0;j!=up;j++)
 {
 for(int n=0;n!=64;n++)
  {
  pixel(random(318)+1,random(198)+1,192+random(64));
  for(int k=0;k!=320/up;k++)
   dhline(j*320/up,(j+1)*320/up,0,255);
  }
 burnup();
 }
}

void builddn(){
for(int n=0;n!=dn;n++)
 {
 burndn();
 burnup();
 }
}

void main(){int long n;char c;int x,y;
startgraph();
randomize();
for(n=0;n!=256;n++)
 palette(n,(256-n)/8,n/4,n/8);
while(c!=27)
 {
 while(!kbhit())
  {readmouse();
  if(mouseb==1)
   {
   for(n=0;n!=64;n++)
    {
    x=random(318)+1;y=random(198)+1;
    pixel(x,y,255);
    pixel(x,y-1,SCND);pixel(x,y+1,SCND);
    pixel(x-1,y,SCND);pixel(x+1,y,SCND);
    }
   burnup();
   }
  if(mouseb==2)
   burndn();
  if(mouseb==3)
   sink();
  display();
  }
 c=getch();
 clrgraph(0);
 if(c==27)break;
 buildup();
 builddn();
 display();
 }
}
