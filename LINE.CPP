// LINE.CPP
// Simple line-drawing mouse thingydoodle.
#include "tile3.cpp"
#include <math.h>
#include "mouse.cpp"

void line(int X1, int Y1, int X2, int Y2, int Color);
void directline(int X1, int Y1, int X2, int Y2, int Color);
int sign(int Number);

void main(){char c;int l=-1,ox=-1,oy,ob,sx,sy;
startgraph();
while(c!='q')
 {
 readmouse();mousex=mousex>>1;
 if(mousex!=ox||mousey!=oy)
  {
  directpixel(ox,oy,0);
  display();
  if(l==1)directline(sx,sy,mousex,mousey,15);
  directpixel(mousex,mousey,15);
  ox=mousex;oy=mousey;
  }
 if(mouseb!=ob)
  {
  ob=mouseb;
  if(mouseb==1)
   {
   switch(l)
    {
    case 1:l*=-1;line(sx,sy,mousex,mousey,15);break;
    case -1:l*=-1;sx=mousex;sy=mousey;break;
    }
   }
  if(mouseb==2)
   {
   line(sx,sy,mousex,mousey,15);
   sx=mousex;sy=mousey;
   display();
   }
  //if(mouseb==1&&l==1){l*=-1;line(sx,sy,mousex,mousey,15);}
  //if(mouseb==1&&l==-1){l*=-1;sx=mousex;sy=mousey;}
  }
 if(kbhit())c=getch();
 }
}

/*void line(int X1, int Y1, int X2, int Y2, int Color)
{
   int XDist,YDist;
   int XDir,YDir;
   int XCount,YCount;
   int XYInc;
   if (X1 == X2)
   {
      int X = X1;
      if (Y1 > Y2)
      {
	 int Temp = Y1; Y1 = Y2; Y2 = Temp;
      }
      for (int Y = Y1; Y <= Y2; Y++)
	 pixel(X,Y,Color);
   }
   else
   {
      if (Y1 == Y2)
      {
	 int Y = Y1;
	 if (X1 > X2)
	 {
	    int Temp = X1; X1 = X2; X2 = Temp;
	 }
	 for (int X = X1; X <= X2; X++)
	    pixel(X,Y,Color);
      }
   }
   if (!((X1 == X2) || (Y1 == Y2)))
   {
      XDist = X2 - X1;
      YDist = Y2 - Y1;
      XDir = sign(XDist);
      YDir = sign(YDist);
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
      }
       }
      else
      {
      XYInc += XDist;
      YCount += YDir;
      if (XYInc >= YDist)
      {
      XYInc -= YDist;
      XCount += XDir;
      }
   }
  }
 pixel(XCount,YCount,Color);
 }
}

void directline(int X1, int Y1, int X2, int Y2, int Color)
{
   int XDist,YDist;
   int XDir,YDir;
   int XCount,YCount;
   int XYInc;
   if (X1 == X2)
   {
      int X = X1;
      if (Y1 > Y2)
      {
	 int Temp = Y1; Y1 = Y2; Y2 = Temp;
      }
      for (int Y = Y1; Y <= Y2; Y++)
	 directpixel(X,Y,Color);
   }
   else
   {
      if (Y1 == Y2)
      {
	 int Y = Y1;
	 if (X1 > X2)
	 {
	    int Temp = X1; X1 = X2; X2 = Temp;
	 }
	 for (int X = X1; X <= X2; X++)
	    directpixel(X,Y,Color);
      }
   }
   if (!((X1 == X2) || (Y1 == Y2)))
   {
      XDist = X2 - X1;
      YDist = Y2 - Y1;
      XDir = sign(XDist);
      YDir = sign(YDist);
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
      }
       }
      else
      {
      XYInc += XDist;
      YCount += YDir;
      if (XYInc >= YDist)
      {
      XYInc -= YDist;
      XCount += XDir;
      }
   }
  }
 directpixel(XCount,YCount,Color);
 }
}

int sign(int Number){
if (Number < 0) return -1; else return +1;}   */