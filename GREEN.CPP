#include <conio.h>
#include "bgraph.inc"
#include "mouse.cpp"
void avg();
void burnup();
void burndn();
void main(){char c;int n;
startgraph();
for(n=0;n!=256;n++)
 //palette(n,n/6,n/4,n/8);//*/
 palette(n,(256-n)/8,n/4,n/8);
 /*for(n=0;n!=256;n++)
 palette(n,n,n,0);//*/
//
/*for(n=0;n!=256;n++)
 {vline(50,100,25+n,n);
 dvline(50,100,25+n,n);}//*/
//pixel(50,50,255);
//pixel(0,0,255);
//getch();
//display();
//

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
 palette(n+192,n+32,n+32,n+32);
//*/
palette(0,24,8,0);
int p=0;
#define s 10
while(c!=27)
 {
 display();
 if(kbhit())c=getch();
 readmouse();
 dpixel(mousex/=2,mousey,192);
 p=*(buffer+mousex+mousey*320);
 if(mouseb==2)
  {
  if(p>0)pixel(mousex,mousey,p-s);
  burndn();
  }
 if(mouseb==1)
  {
  if(p<255)pixel(mousex,mousey,p+s);
  burnup();
  }
 if(mouseb==3)burnup();
 if(c=='+')burnup();
 if(c=='-')burndn();
 if(c!=27)c='q';
 }
//getch();
endgraph();
}

/*void burnup(){int t;
for(int y=1;y!=199;y++)
 {
 for(int x=0;x!=320;x++)
  {
  t=(getpixel(x,y)+
     getpixel(x,y-1)+
     getpixel(x+1,y)+      // We average all the pixels around
     getpixel(x-1,y)+
     getpixel(x,y+1)
     )/5;      // us, except the one above us.
  if(getpixel(x,y)<t)
  //pixel(x,y-1,t);
  pixel(x,y,t);
  //if(getpixel(x,y)!=0)pixel(x,y,getpixel(x,y)-1);
  }
 }
}*/

void burnup(){int t;
for(int y=mousey-5;y!=mousey+5;y++)
 {
 for(int x=mousex-5;x!=mousex+5;x++)
  {
  t=(getpixel(x,y)+
     getpixel(x,y-1)+
     getpixel(x+1,y)+      // We average all the pixels around
     getpixel(x-1,y)+
     getpixel(x,y+1)
     )/5;      // us, except the one above us.
  if(getpixel(x,y)<t)
  //pixel(x,y-1,t);
  pixel(x,y,t);
  //if(getpixel(x,y)!=0)pixel(x,y,getpixel(x,y)-1);
  }
 }
}

void burndn(){int t;
for(int y=mousey-5;y!=mousey+5;y++)
 {
 for(int x=mousex-5;x!=mousex+5;x++)
  {
  t=(getpixel(x,y)+
     getpixel(x,y-1)+
     getpixel(x+1,y)+      // We average all the pixels around
     getpixel(x-1,y)+
     getpixel(x,y+1)
     )/5;      // us, except the one above us.
  if(getpixel(x,y)>t)
  //pixel(x,y-1,t);
  pixel(x,y,t);
  //if(getpixel(x,y)!=0)pixel(x,y,getpixel(x,y)-1);
  }
 }
}

void avg(){int d;
for(int x=1;x!=319;x++)
 for(int y=1;y!=199;y++)
  {
  d=getpixel(x-1,y-1)+getpixel(x,y-1)+getpixel(x+1,y-1)
   +getpixel(x-1,y)+getpixel(x,y)+getpixel(x+1,y)
   +getpixel(x-1,y+1)+getpixel(x,y+1)+getpixel(x+1,y+1);
  d/=7;//if(d!=0)d-=2;
  pixel(x,y,d);
  }
}