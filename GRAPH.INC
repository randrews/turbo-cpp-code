#include <mem.h>
#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define OPEN 0
#define CLOSED 1

#ifndef GRAPH_INC
#define GRAPH_INC

#define palette_mask  0x3c6  // tells the vga card we'll be messing
			     //w/ the palette
#define palette_write 0x3c8  // tells it we'll be writing values
#define palette_data  0x3c9  // this is the port we'll write to

//#define ___testing___

unsigned char far *screen;		// pointer to the VGA video memory
unsigned char far *off_screen;	// pointer to our off screen buffer
int screen_width, screen_height; 
unsigned int screen_size;
int old_mode;

int startgraph();
void display();
void enter_mode13h();
void endgraph();
void pixel(int x,int y,int colour);
void directpixel(int x,int y,int c);
void rectangle(int startx,int starty,int endx,int endy,int color);

#ifdef ___testing___

void main(){int n;
startgraph();
rectangle(0,0,100,100,4);
rectangle(0,100,100,199,5);
getch();
display();getch();
endgraph();}

#endif

void pixel(int x, int y, int colour)
{

	*(off_screen + y*screen_width + x)=colour;
}

void directpixel(int x, int y, int c)
{
	*(screen+ y*screen_width + x)=c;
}

int getpixel(int x, int y)
{
	return *(off_screen + y*screen_width + x);
}

void enter_mode13h(void)
{
	union REGS in, out;

	// get old video mode
	in.h.ah=0xf;
	int86(0x10, &in, &out);
	old_mode=out.h.al;

	// enter mode 13h
	in.h.ah=0;
	in.h.al=0x13;
	int86(0x10, &in, &out);
}

void endgraph(void)
{
	union REGS in, out;

	// change to the video mode we were in before we switched to mode 13h
	in.h.ah=0;
	in.h.al=old_mode;
	int86(0x10, &in, &out);
	delete off_screen;
}

int startgraph(void)
{
	off_screen=(char far*)farmalloc(64000);

	if ( off_screen || !off_screen)
		{
		screen=(char far*)MK_FP(0xa000, 0);
		screen_width=320;
		screen_height=200;
		screen_size=64000;
		enter_mode13h();
		_fmemset(off_screen, 0, screen_size);
		return 0;
		}
	else
		{
		// no mem! Return error code!
		endgraph();
		printf("Out of mem!\n");
		return 1;
		}
}

void palette(int color,int red,int green,int blue){
outp(palette_mask,0xff);
outp(palette_write,color);
outp(palette_data,red);
outp(palette_data,green);
outp(palette_data,blue);
}



#define INPUT_STATUS_0 0x3da

// copy the off screen buffer to video memory
void display(void)
{
	// wait for vertical re-trace
	while ( inportb(INPUT_STATUS_0) & 8 );
	while ( !(inportb(INPUT_STATUS_0) & 8) );

	// copy everything to video memory
	_fmemcpy(screen, off_screen, screen_size);
}

void rectangle(int startx,int starty,int endx,int endy,int color)
{
for(int n=startx;n!=endx;n++)
 {
 pixel(n,starty,color);
 pixel(n,endy,color);
 }
for(n=starty;n!=endy;n++)
 {
 pixel(startx,n,color);
 pixel(endx,n,color);
 }
pixel(endx,endy,color);
}
//void rectangle(int x1,int y1,int x2,int y2,int color)

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
  _fmemset(off_screen+x1+n*screen_width,color,x2-x1);
  //for(int N=x1;N!=x2;N++)
  // pixel(N,n,color);
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
  _fmemset(screen+x1+n*screen_width,color,x2-x1);
  //for(int N=x1;N!=x2;N++)
  // directpixel(N,n,color);
 }
}

void circle(int CX, int CY, int Radius, int Color)
{
   for (int K=1; K <= 629; K++)
   {
      //X = Radius * CosTab[K] + CX;
      //Y = Radius * SinTab[K] * 0.88 + CY;
      //pixel(X,Y,Color);
      pixel(CX+Radius*cos(K),CY+Radius*sin(K)*0.88,Color);
   }  // for k = 1 to 629
}

void directcircle(int CX, int CY, int Radius, int Color)
{
   for (int K=1; K <= 629; K++)
   {
      //X = Radius * CosTab[K] + CX;
      //Y = Radius * SinTab[K] * 0.88 + CY;
      //directpixel(X,Y,Color);
      directpixel(CX+Radius*cos(K),CY+Radius*sin(K)*0.88,Color);
   }  // for k = 1 to 629
}

void ellipse(int cx,int cy,int xr,int yr,int color){
for(int n=0;n!=628;n++)
 {
 pixel(cx+xr*cos(n),cy+yr*sin(n)*0.88,color);
 }
}

void directellipse(int cx,int cy,int xr,int yr,int color){
for(int n=0;n!=628;n++)
 {
 directpixel(cx+xr*cos(n),cy+yr*sin(n)*0.88,color);
 }
}


void cleargfx(int color){
//rectangle(0,0,319,199,color,CLOSED);
_fmemset(off_screen, color, screen_size);
}

void directcleargfx(int color){
//directrectangle(0,0,391,199,color,CLOSED);
_fmemset(screen, color, screen_size);
}




/*#include <dos.h>
#include <mem.h>
#include <alloc.h>

char far* buffer=new char[64000];
//char far* buffer=(char far*)farmalloc(64000);
void mcga();
void pixel(int x,int y,char c);
void display();
void cleargfx(char c);

void mcga()
{
_AX=0x13;
geninterrupt(0x10);
}

void pixel(int x,int y,char c)
{
pokeb(FP_SEG(buffer),x+y*320,c);
}

void cleargfx(char c)
{
_fmemset(buffer,c,64000);
}

void display()
{
_fmemcpy(MK_FP(0xa000,0),buffer,64000);
}*/

// graphic text global vars ------------------------------------------------------
int CharHeight;
int CharWidth;
unsigned char far *FontPtr;	// pointer to current font
unsigned char far *F8x8Ptr;     // pointers to the two VGA ROM fonts
unsigned char far *F8x14Ptr;

// get the address of the two VGA ROM fonts and save them.
// make the 8x8 font active

void startfont()
{
	struct REGPACK reg;

	reg.r_ax=0x1130;    // 30 get info on current set, 11 character info
	reg.r_bx=0x0300;    // get 8x8 font info

	intr(0x10, &reg);

	// es:bp points to 8x8 font
	F8x8Ptr=(char far *)MK_FP(reg.r_es, reg.r_bp);

	reg.r_ax=0x1130;  // 30 get info on current set, 11 font info
	reg.r_bx=0x0200;	// get 8x14 font info

	intr(0x10, &reg);

	// es:bp points to 8x14 font
	F8x14Ptr=(char far *)MK_FP(reg.r_es, reg.r_bp);

	// make the 8x8 font the active font
	FontPtr=F8x8Ptr;
	CharWidth=8;
	CharHeight=8;

}

void setfont(int font_id) // 0: 8x8
{                         // 1: 8x14
	if ( font_id == 0 )
		{
		FontPtr=F8x8Ptr;
		CharWidth=8;
		CharHeight=8;
		}
	else
		{
		if ( font_id == 1 )
			{
			FontPtr=F8x14Ptr;
			CharWidth=8;
			CharHeight=14;
			}
		else
			{
			// user defined font, not implemented

			}

		}
}

// c is the character to draw
// must call text_init first!
// this code assumes all fonts are 8 pixels wide, stored as a bitmapped byte

void directdrawchar(int x, int y, int c, int forecolour, int backcolour)
{
	unsigned char far *p, far *fnt;
	int width, height, adj;
	unsigned char mask;

	// make p point to the screen
	p=screen + y*screen_width + x;
	adj=screen_width - CharWidth;

	// make fnt point to the start of the character we want to draw.
	// characters are 1 byte wide, and height bytes tall
	fnt=FontPtr + c*CharHeight;

	height=CharHeight;
	while ( height-- )
		{
		width=CharWidth;
		mask=128; 			// bit mask: 10000000
		while ( width-- )		// assumes width of 8
			{
			if ( (*fnt) & mask )	 // is this bit set?
				{
				// draw pixel
				*p++=forecolour;
				}
			else
				{
				// draw background colour
				*p++=backcolour;
				}

			mask>>=1;  // shift mask to check next bit
			}

		p+=adj;  // next line on screen
		fnt++;   // next line of font
		}
}


void drawchar(int x, int y, int c, int forecolour, int backcolour)
{
	unsigned char far *p, far *fnt;
	int width, height, adj;
	unsigned char mask;

	// make p point to the screen
	p=off_screen + y*screen_width + x;
	adj=screen_width - CharWidth;

	// make fnt point to the start of the character we want to draw.
	// characters are 1 byte wide, and height bytes tall
	fnt=FontPtr + c*CharHeight;

	height=CharHeight;
	while ( height-- )
		{
		width=CharWidth;
		mask=128; 			// bit mask: 10000000
		while ( width-- )		// assumes width of 8
			{
			if ( (*fnt) & mask )	 // is this bit set?
				{
				// draw pixel
				*p++=forecolour;
				}
			else
				{
				// draw background colour
				*p++=backcolour;
				}

			mask>>=1;  // shift mask to check next bit
			}

		p+=adj;  // next line on screen
		fnt++;   // next line of font
		}
}


//#include "fonts.cpp"
#endif


