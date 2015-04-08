#include <conio.h>
#include <math.h>
#include <dos.h>

#define interval 10

void line(int X1, int Y1, int X2, int Y2, int Color);

void startgraph(){
asm mov ax,0x4f02
asm mov bx,0x101
asm int 0x10
}

void pixel(int x,int y,int c){
_BH=0;
asm mov cx,x
asm mov dx,y
_AL=c;
asm mov ah,0x0c
asm int 0x10//*/
}

float degrad(float deg){
return deg*3.141/180;
}

int findx(int x1,float deg,int l){
return x1+l*cos(degrad(deg));
}

int findy(int y1,float deg,int l){
return y1-l*sin(degrad(deg));
}

void endgraph(){
asm mov ax,0x3
asm int 0x10
}

void main(){int sx=320,sy=240,x,y,l=10,d=0;char c;
	    int spd=0;int ox,oy,osx,osy;
	    int dx,dy;
startgraph();
/*for(d=0;n!=360/interval;n++)
 {
 x=findx(sx,d*interval,l);
 y=findy(sy,d*interval,l);
 line(sx,sy,x,y,15);
 }
getch();//*/
while(c!=27)
 {
 if(kbhit()){c=getch();line(sx,sy,x,y,0);}
  if(c=='M')d-=interval;
  if(c=='K')d+=interval;
  if(c=='+')spd++;
  if(c=='-')spd--;
  //if(spd>0)spd-=0.01;
  if(c!=27)c=0;
 ox=x;oy=y;
 osx=sx;osy=sy;
 x=findx(sx,d,l);
 y=findy(sy,d,l);
 dx=findx(sx,d,spd);
 dy=findy(sy,d,spd);
 sx+=dx;sy+=dy;
 line(sx,sy,x,y,4);
 line(osx,osy,sx,sy,0);
 delay(5);
 }
endgraph();
}

int Sign(int Number)
{
   if (Number < 0) return -1; else return +1;
}

void line(int X1, int Y1, int X2, int Y2, int Color)
{
   int XDist,YDist;          // x and y distances                      /
   int XDir,YDir;            // x and y directions                     /
   int XCount,YCount;        // x and y counters                       /
   int XYInc;                // x and y incrementor                    /



   if (X1 == X2)
   {
      int X = X1;
      if (Y1 > Y2)
      {
	 int Temp = Y1; Y1 = Y2; Y2 = Temp;
      }  // if (y1 > y2)
      for (int Y = Y1; Y <= Y2; Y++)
	 pixel(X,Y,Color);
   }  // if (x1 == x2)
   else
   {
      if (Y1 == Y2)
      {
	 int Y = Y1;
	 if (X1 > X2)
	 {
	    int Temp = X1; X1 = X2; X2 = Temp;
	 }  // if (x1 > x2)
	 for (int X = X1; X <= X2; X++)
	    pixel(X,Y,Color);
//	 memset(VGAMEM + X1 + Y * 320, Color, X2 - X1 + 1);
      }  // if (y1 == y2)
   }  // else

   if (!((X1 == X2) || (Y1 == Y2)))
   {
      XDist = X2 - X1;
      YDist = Y2 - Y1;
      XDir = Sign(XDist);
      YDir = Sign(YDist);
      XDist = abs(XDist);
      YDist = abs(YDist);
      XCount = X1;
      YCount = Y1;
      XYInc = 0;
      while ((XCount != X2) || (YCount != Y2))
      {
	 pixel(XCount,YCount,Color);
	 if (YDist < XDist)
	 {
	    XYInc += YDist;
	    XCount += XDir;
	    if (XYInc >= XDist)
	    {
	       XYInc -= XDist;
	       YCount += YDir;
	    }  // if (xyinc >= xdist)
	 }  // if (ydist < xdist)
	 else
	 {
	    XYInc += XDist;
	    YCount += YDir;
	    if (XYInc >= YDist)
	    {
	       XYInc -= YDist;
	       XCount += XDir;
	    }  // if (xyinc >= ydist)
	 }  // else
      }  // while ((xcount != x2) || (ycount != y2))
      pixel(XCount,YCount,Color);
   }  // if (!((X1 == X2) || (Y1 == Y2)))
}  // void function line