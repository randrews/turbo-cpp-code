#include "bgraph.inc"
#include "line2.cpp"
#include "mouse.cpp"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
/*void burnup(){int t;
for(int y=1;y!=199;y++)
 {
 for(int x=1;x!=319;x++)
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
void burnup(){int d;
for(int x=1;x!=319;x++)
 for(int y=1;y!=199;y++)
  {
  d=getpixel(x-1,y-1)+getpixel(x,y-1)+getpixel(x+1,y-1)
   +getpixel(x-1,y)+getpixel(x,y)+getpixel(x+1,y)
   +getpixel(x-1,y+1)+getpixel(x,y+1)+getpixel(x+1,y+1);
  d/=9;//if(d!=0)d-=2;
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
  d/=9;//if(d!=0)d-=2;
  if(getpixel(x,y)>d)pixel(x,y,d);
  }
}

void sink(){
for(int x=1;x!=319;x++)
 for(int y=1;y!=199;y++)
  if(getpixel(x,y)>0)
   (*(buffer+x+y*320))--;
}

/*void burndn(){int t;
for(int y=1;y!=199;y++)
 {
 for(int x=1;x!=319;x++)
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
}//*/
#define up 40
#define dn 4
void buildup(){
for(int j=0;j!=up;j++)
 {
 for(int n=0;n!=64;n++)
  {
  pixel(random(318)+1,random(198)+1,192+random(64));
  //line(random(318)+1,random(198)+1,
  //     random(318)+1,random(198)+1,random(64)+192);
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

void main(){int long n;char c;int x,y;int upcount=0,dncount=0;
startgraph();
randomize();
for(n=0;n!=256;n++)
 palette(n,(256-n)/8,n/4,n/8);
/*while(!kbhit())
 {readmouse();
 if(mouseb==1)
  {
  for(n=0;n!=64;n++)
   {
#define SCND 128
   x=random(318)+1;
   y=random(198)+1;
   pixel(x,y,255);
   pixel(x,y-1,SCND);
   pixel(x,y+1,SCND);
   pixel(x-1,y,SCND);
   pixel(x+1,y,SCND);
   }
  burnup();
  upcount++;
  }
 if(mouseb==2){burnup();burndn();dncount++;}
 if(mouseb==3){sink();upcount=dncount=0;}
 display();
 }
 endgraph();
 printf("%i %i",upcount,dncount);
 getch();//*/
while(c!=27){
 while(!kbhit())
  {readmouse();
 if(mouseb==1)
  {
  /*for(n=0;n!=64;n++)
   {
#define SCND 128
   x=random(318)+1;
   y=random(198)+1;
   pixel(x,y,255);
   pixel(x,y-1,SCND);
   pixel(x,y+1,SCND);
   pixel(x-1,y,SCND);
   pixel(x+1,y,SCND);
   }//*/
  burnup();
  upcount++;
  }
 if(mouseb==2){burndn();dncount++;}
 if(mouseb==3){sink();upcount=dncount=0;}
 display();
  }
 c=getch();
 clrgraph(0);
 if(c==27)break;
 buildup();
 builddn();
 display();
 }//*/
}
