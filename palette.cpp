#include <conio.h>
#define palette_mask  0x3c6  // tells the vga card we'll be messing
			     //w/ the palette
#define palette_write 0x3c8  // tells it we'll be writing values
#define palette_data  0x3c9  // this is the port we'll write to

typedef struct RGB_Type
 {
 unsigned char red;
 unsigned char green;
 unsigned char blue;
 } RGB_color, *RGB_color_ptr;

//You've got your structure set up, now what do you do with it? Well,
//you'll probably want your palette to consist of shades of red
//(or not, it's up to you). But we'll pretend you're using red.

//first make a procedure set_pal():


void set_pal(int index, RGB_color_ptr color)
{
outp(palette_mask, 0xff);     // tell it we'll be messing w/ it
outp(palette_write, index);   // which color we'll be updating
outp(palette_data, color->red);
outp(palette_data, color->green);
outp(palette_data, color->blue);
}

void palette(int color,int red,int green,int blue){
outp(palette_mask,0xff);
outp(palette_write,color);
outp(palette_data,red);
outp(palette_data,green);
outp(palette_data,blue);
}


//ok, you've got your procedure to change the palette,
//now let's make one that will send the values to it:


void init_colors(void) // set up smooth running color palette
{
int i, count;
RGB_color_ptr col;
                     
for (i = 1; i < 255; i++)
 {
 col->red = i*(3/2);   // there are 63 possible intensities for each color
 col->green = i; // so we'll loop through and set from 1 to 62 for
 col->blue = 0;  // shades of red.
 set_pal(i, col);
 }

col->red = 43;//20;
col->green = 60;//60;
col->blue = 0;//20;
for (i = 63; i < 255; i++) // this will set _ALL_ other colors to black
set_pal(i, col);   // I'll explain why we do this later
}