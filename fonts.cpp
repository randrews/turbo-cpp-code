#include <dos.h>
#include "graph.inc"
// graphic text global vars ------------------------------------------------------
int CharHeight;
int CharWidth;
unsigned char far *FontPtr;	// pointer to current font
unsigned char far *F8x8Ptr;     // pointers to the two VGA ROM fonts
unsigned char far *F8x14Ptr;

// get the address of the two VGA ROM fonts and save them.
// make the 8x8 font active

void starttext()
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

void setfont(int font_id)
{
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

void drawchar(int c, int x, int y, int forecolour, int backcolour)
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
