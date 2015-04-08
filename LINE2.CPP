#include <math.h>
#ifndef _tgraph_cpp_
#include "bgraph.inc"
#endif

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
