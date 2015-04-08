// GRAPHFUN.INC
// Graphics functions: Some taken from GRAPHICS.INC,
//                      some made from scratch.
#ifndef GRAPHFUN_INC
#define GRAPHFUN_INC
#define OPEN 0
#define CLOSED 1
#include <math.h>
#include "graph.inc"

//void line(int X1, int Y1, int X2, int Y2, int Color);
//int Sign(int Number);     // returns sign of number                 /

//void maketables();


int Sign(int Number)
{
   if (Number < 0) return -1; else return +1;
}

void directline(int X1, int Y1, int X2, int Y2, int Color)
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
	 directpixel(X,Y,Color);
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
	    directpixel(X,Y,Color);
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
	 directpixel(XCount,YCount,Color);
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
      directpixel(XCount,YCount,Color);
   }  // if (!((X1 == X2) || (Y1 == Y2)))
}  // void function line

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

void rectangle(int x1,int y1,int x2,int y2,int color,int oc){int t;
if(x1>x2){t=x1;x1=x2;x2=t;}
if(y1>y2){t=y1;y1=y2;y2=t;}
for(int n=x1;n!=x2+1;n++)
 {pixel(n,y1,color);
  pixel(n,y2,color);}
for(n=y1;n!=y2;n++)
 {pixel(x1,n,color);
  pixel(x2,n,color);}
if(oc==CLOSED)
 {
 for(n=y1;n!=y2;n++)
  for(int N=x1;N!=x2;N++)
   pixel(N,n,color);
 }
}

void directrectangle(int x1,int y1,int x2,int y2,int color,int oc){int t;
if(x1>x2){t=x1;x1=x2;x2=t;}
if(y1>y2){t=y1;y1=y2;y2=t;}
for(int n=x1;n!=x2+1;n++)
 {directpixel(n,y1,color);
  directpixel(n,y2,color);}
for(n=y1;n!=y2;n++)
 {directpixel(x1,n,color);
  directpixel(x2,n,color);}
if(oc==CLOSED)
 {
 for(n=y1;n!=y2;n++)
  for(int N=x1;N!=x2;N++)
   directpixel(N,n,color);
 }
}

void maketables(){
   int   Radian;
   for (int X=0; X <= 629; X++)
   {
      Radian = float(X) / 100;
      SinTab[X] = sin(Radian);
      CosTab[X] = cos(Radian);
   }
}

void Circle(int CX, int CY, int Radius, int Color)
{
   int   X,Y;                // x and y coordinates
   for (int K=1; K <= 629; K++)
   {
      X = Radius * CosTab[K] + CX;
      Y = Radius * SinTab[K] * 0.88 + CY;
      pixel(X,Y,Color);
   }  // for k = 1 to 629
}

void cleargfx(int color){
rectangle(0,0,319,199,color,CLOSED);}

void directcleargfx(int color){
directrectangle(0,0,391,199,color,CLOSED);}

#endif






