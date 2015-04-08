#include <dos.h>
#include "graphics.inc"
#include <conio.h>
#include <math.h>
const int a=35;
void main(){int dx1=0,dy1=0,x1=50,y1=50,d;char c;
StartGfx(); int dx2=0,dy2=0,x2=MAXX-50,y2=MAXY-50;
while (c!=27)
 {
 while(!kbhit())
  {
  ClearGfx(0);
  x1+=dx1;y1+=dy1;
  x2+=dx2;y2+=dy2;
  //Circle(MIDX,MIDY,5,4);
  Pixel(x1,y1,15);
  Pixel(x2,y2,4);

  d=abs(x2-x1)/a;
  if(x1>x2)dx1-=d;if(x1<x2)dx1+=d;
  d=abs(y2-y1)/a;
  if(y1>y2)dy1-=d;if(y1<y2)dy1+=d;

  d=abs(x2-x1)/a;
  if(x2>x1)dx2-=d;if(x2<x1)dx2+=d;
  d=abs(y2-y1)/a;
  if(y2>y1)dy2-=d;if(y2<y1)dy2+=d;

  if(x1<0)x1=0;if(x1>319)x1=319;
  if(y1<0)y1=0;if(y1>199)y1=199;
  if(x2<0)x2=0;if(x2>319)x2=319;
  if(y2<0)y2=0;if(y2>199)y2=199;
  delay(75);
  }
 c=getch();
 switch (c)
  {
  case '8':dy1-=1;break;
  case '4':dx1-=1;break;
  case '6':dx1+=1;break;
  case '2':dy1+=1;break;
  case '5':dx1=0;dy1=0;break;
  }
 }
}