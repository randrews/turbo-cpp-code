#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#include "c:\tc\bin\bgraph.inc"
#include "c:\tc\bin\mouse.cpp"

#define up 25
#define dn 4
#define SCND 128
#define SW 150
#define SH 90

void block(int x,int y,int c){
x*=2;
if(y%2==1)x++;
y*=2;
pixel(x,y,c);
pixel(x+1,y,c);
pixel(x,y+1,c);
pixel(x+1,y+1,c);
}

int getblock(int x,int y){
x*=2;
if(y%2==1)x++;
y*=2;
return getpixel(x,y);
}

void burnup(){int d;
for(int x=1;x!=SW;x++)
 for(int y=1;y!=SH+1;y++)
  {
  d=getblock(x-1,y-1)+getblock(x,y-1)+getblock(x+1,y-1)
   +getblock(x-1,y)+getblock(x,y)+getblock(x+1,y)
   +getblock(x-1,y+1)+getblock(x,y+1)+getblock(x+1,y+1);
  d/=9;
  if(getblock(x,y)<d)block(x,y,d);
  }
}

void burndn(){int d;
for(int x=1;x!=SW;x++)
 for(int y=1;y!=SH+1;y++)
  {
  d=getblock(x-1,y-1)+getblock(x,y-1)+getblock(x+1,y-1)
   +getblock(x-1,y)+getblock(x,y)+getblock(x+1,y)
   +getblock(x-1,y+1)+getblock(x,y+1)+getblock(x+1,y+1);
  d/=9;
  if(getblock(x,y)>d)block(x,y,d);
  }
}

void sink(){
for(int x=1;x!=SW;x++)
 for(int y=1;y!=SH;y++)
  if(getblock(x,y)>0)
   //(*(buffer+x+y*320))--;
   block(x,y,getblock(x,y)-1);
}

void buildup(){
for(int j=0;j!=up;j++)
 {
 for(int n=0;n!=32;n++)
  {
  block(random(SW-1)+1,random(SH-1)+1,192+random(64));
  for(int k=0;k!=(SW+1)/up;k++)
   dhline(j*(SW*2+1)/up,(j+1)*(SW*2+1)/up,0,255);
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
    x=random(SW-1)+1;y=random(SH-1)+1;
    block(x,y,255);
    //block(x,y-1,SCND);//pixel(x,y+1,SCND);
    //block(x-1,y,SCND);//pixel(x+1,y,SCND);
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
