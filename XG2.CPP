/*
 * LIB.C v1.2
 *
 * by Robert Schmidt
 * (C)1993 Ztiff Zox Softwear
 *
 * Simple graphics library to accompany the article
 * 
 *			INTRODUCTION TO MODE X.
 * 
 * This library provides the basic functions for initializing and using
 * unchained (planar) 256-color VGA modes.  Currently supported are:
 *
 *	- 320x200
 *	- 320x240
 *
 * Functions are provided for:
 *
 *	- initializing one of the available modes
 *	- setting the start address of the VGA refresh data
 *	- setting active and visible display pages
 *	- writing and reading a single pixel to/from video memory
 *
 * The library is provided as a demonstration only, and is not claimed
 * to be particularly efficient or suited for any purpose.  It has only
 * been tested with Borland C++ 3.1 by the author.  Comments on success
 * or disaster with other compilers are welcome.
 *
 * This file is public domain.  Do with it whatever you'd like, but
 * please don't distribute it without the article.
 *
 * Thanks go out to various helpful netters who spotted the 0xE7 bug
 * in the set320x240x256() function!
 */


/*
 * We 'require' a large data model simply to get rid of explicit 'far'
 * pointers and compiler specific '_fmemset()' functions and the likes.
 */

#ifndef __COMPACT__
# ifndef __LARGE__
#  ifndef __HUGE__
#   error Large data model required!  Try compiling with 'bcc -ml lib.c'.
#  endif
# endif
#endif

#include <dos.h>
#include <mem.h>
#include <math.h>
#define OPEN 0
#define CLOSED 1
/*
 * Comment out the following #define if you don't want the testing main()
 * to be included.
 */

#define TESTING//*/

/*
 * Define the port addresses of some VGA registers.
 */

#define CRTC_ADDR	0x3d4	/* Base port of the CRT Controller (color) */

#define SEQU_ADDR	0x3c4	/* Base port of the Sequencer */
#define GRAC_ADDR	0x3ce	/* Base port of the Graphics Controller */


/*
 * Make a far pointer to the VGA graphics buffer segment.  Your compiler
 * might not have the MK_FP macro, but you'll figure something out.
 */

typedef unsigned char UCHAR;
UCHAR *vga = (UCHAR *) MK_FP(0xA000, 0);
//int pages;
/*
 * width and height should specify the mode dimensions.  widthBytes
 * specify the width of a line in addressable bytes.
 */

unsigned width, height, widthBytes;

/*
 * actStart specifies the start of the page being accessed by
 * drawing operations.  visStart specifies the contents of the Screen
 * Start register, i.e. the start of the visible page.
 */

unsigned actStart, visStart;

/*
 * set320x200x256_X()
 *	sets mode 13h, then turns it into an unchained (planar), 4-page
 *	320x200x256 mode.
 */

//int findpages();

void startgraph(void)
	{

	union REGS r;

	/* Set VGA BIOS mode 13h: */

	//r.x.ax = 0x0013;
	r.x.ax = 0x12;
	int86(0x10, &r, &r);

	/* Turn off the Chain-4 bit (bit 3 at index 4, port 0x3c4): */

	outport(SEQU_ADDR, 0x0604);

	/* Turn off word mode, by setting the Mode Control register
	   of the CRT Controller (index 0x17, port 0x3d4): */

	outport(CRTC_ADDR, 0xE317);

	/* Turn off doubleword mode, by setting the Underline Location
	   register (index 0x14, port 0x3d4): */

	outport(CRTC_ADDR, 0x0014);

	/* Clear entire video memory, by selecting all four planes, then
	   writing 0 to entire segment. */

	outport(SEQU_ADDR, 0x0F02);
	memset(vga+1, 0, 0xffff); /* stupid size_t exactly 1 too small */
	vga[0] = 0;

	/* Update the global variables to reflect dimensions of this
	   mode.  This is needed by most future drawing operations. */

	width   = 320;
	height	= 200;
	//pages=findpages();
	/* Each byte addresses four pixels, so the width of a scan line
	   in *bytes* is one fourth of the number of pixels on a line. */

	widthBytes = width / 4;

	/* By default we want screen refreshing and drawing operations
       to be based at offset 0 in the video segment. */

	actStart = visStart = 0;

	}

/*
 * setActiveStart() tells our graphics operations which address in video
 * memory should be considered the top left corner.
 */

void setActiveStart(unsigned offset)
	{
	actStart = offset;
	}

/*
 * setVisibleStart() tells the VGA from which byte to fetch the first
 * pixel when starting refresh at the top of the screen.  This version
 * won't look very well in time critical situations (games for
 * instance) as the register outputs are not synchronized with the
 * screen refresh.  This refresh might start when the high byte is
 * set, but before the low byte is set, which produces a bad flicker.
 */

void setVisibleStart(unsigned offset)
	{
	visStart = offset;
	outport(CRTC_ADDR, 0x0C);		/* set high byte */
	outport(CRTC_ADDR+1, visStart >> 8);
	outport(CRTC_ADDR, 0x0D);		/* set low byte */
	outport(CRTC_ADDR+1, visStart & 0xff);
	}

/*
 * setXXXPage() sets the specified page by multiplying the page number
 * with the size of one page at the current resolution, then handing the
 * resulting offset value over to the corresponding setXXXStart()
 * function.  The first page is number 0.
 */

void actpage(int page)
	{
	setActiveStart(page * widthBytes * height);
	}

void vispage(int page)
	{
	setVisibleStart(page * widthBytes * height);
	}

void pixel(int x, int y, UCHAR color)
	{

	/* Each address accesses four neighboring pixels, so set
	   Write Plane Enable according to which pixel we want
	   to modify.  The plane is determined by the two least
	   significant bits of the x-coordinate: */

	outportb(0x3c4, 0x02);
	outportb(0x3c5, 0x01 << (x & 3));

	/* The offset of the pixel into the video segment is
	   offset = (width * y + x) / 4, and write the given
	   color to the plane we selected above.  Heed the active
	   page start selection. */

	vga[(unsigned)(widthBytes * y) + (x / 4) + actStart] = color;

	}

UCHAR getpixel(int x, int y)
	{

	/* Select the plane from which we must read the pixel color: */

	outport(GRAC_ADDR, 0x04);
	outport(GRAC_ADDR+1, x & 3);

	return vga[(unsigned)(widthBytes * y) + (x / 4) + actStart];

	}

void set320x240x256_X(void)
	{

	/* Set the unchained version of mode 13h: */

	//set320x200x256_X();
	startgraph();
	/* Modify the vertical sync polarity bits in the Misc. Output
	   Register to achieve square aspect ratio: */

	outportb(0x3C2, 0xE3);

	/* Modify the vertical timing registers to reflect the increased
	   vertical resolution, and to center the image as good as
	   possible: */

	outport(0x3D4, 0x2C11);		/* turn off write protect */
	outport(0x3D4, 0x0D06);		/* vertical total */
	outport(0x3D4, 0x3E07);		/* overflow register */
	outport(0x3D4, 0xEA10);		/* vertical retrace start */
	outport(0x3D4, 0xAC11);		/* vertical retrace end AND wr.prot */
	outport(0x3D4, 0xDF12);		/* vertical display enable end */
	outport(0x3D4, 0xE715);		/* start vertical blanking */
	outport(0x3D4, 0x0616);		/* end vertical blanking */

	/* Update mode info, so future operations are aware of the
	   resolution */

	height = 240;

	//pages=findpages();
	}

int findpages(){return 65536L/(widthBytes*height);}

/*
 * The library testing routines follows below.
 */


#ifdef TESTING

#include <stdio.h>
#include <conio.h>

void set80x25(void)
	{
	union REGS r;
	r.x.ax = 0x0003;
	int86(0x10, &r, &r);
	}

void doTest(void)
	{
	int p, x, y, pages;

	/* This is the way to calculate the number of pages available. */

	//pages = 65536L/(widthBytes*height);
	pages=findpages();
	for (p = 0; p < pages; ++p)
		{
		actpage(p);

		/* On each page draw a single colored border, and dump the palette
		   onto a small square about the middle of the page. */

		for (x = 0; x <= width; ++x)
			{
			pixel(x, 0, p+1);
			pixel(x, height-1, p+1);
			}

		for (y = 0; y <= height; ++y)
			{
			pixel(0, y, p+1);
			pixel(width-1, y, p+1);
			}

		for (x = 0; x < 16; ++x)
			for (y = 0; y < 16; ++y)
				pixel(x+(p+3)*16, y+(p+3)*16, x + y*16);

		}

	/* Each pages will now contain a different image.  Let the user cycle
	   through all the pages by pressing a key. */

	for (p = 0; p < pages; ++p)
		{
		vispage(p);
		getch();
		}

	}


/*
 * Library test (program) entry point.
 */

int main(void)
	{
	puts("First, have a look at the 320x200 mode.  I will draw some rubbish");
	puts("on all of the four pages, then let you cycle through them by");
	puts("hitting a key on each page.");
	puts("Press a key when ready...");
	getch();

	//set320x200x256_X();
	startgraph();
	doTest();

	set80x25();
	puts("Then, check out Mode X, 320x240 with 3 (and a half) pages.");
	puts("Press a key when ready...");
	getch();

	set320x240x256_X();
	doTest();

	set80x25();
	puts("Where to next?  It's your move!");
	return 0;
	}

#endif



int Sign(int Number)
{
   if (Number < 0) return -1; else return +1;
}

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
  //_fmemset(off_screen+x1+n*screen_width,color,x2-x1);
  for(int N=x1;N!=x2;N++)
   pixel(N,n,color);
 }
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

void ellipse(int cx,int cy,int xr,int yr,int color){
for(int n=0;n!=628;n++)
 {
 pixel(cx+xr*cos(n),cy+yr*sin(n)*0.88,color);
 }
}

void cleargfx(int color){
rectangle(0,0,319,199,color,CLOSED);
}
