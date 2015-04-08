// Simple and tiny graphics library.
// All is done directly to the screen, and has
// no advanced graphics functions like a line
// or a circle. But it's small and easy to use.
// -Zerblinitzky

// Made slight improvments. Now uses buffer, as
// well as palette assignments and pixmaps.
//
// Pixmaps are easy to use, and are essentially
// just like tiles, only a bit faster and half
// the size. A string is declared with the first
// char being the row length and the second char
// being the column length, and all the rest of
// them being pixel values. So, for a 5*5 pixmap
// of a white square with a red dot in the center,
// you would use the following bit of code:
// palette('w',63,63,63);
// palette('b',0,0,0);
// palette('r',63,0,0);
// char *pix="55wwwwwwbbbwwbrbwwbbbwwwwww";
// pixmap(50,50,pix);
// It would map like this:
// w w w w w
// w b b b w
// w b r b w
// w b b b w
// w w w w w
// Of course, the largest pixmaps you could make
// with this are 9*9, but how much larger do you
// want anyway?
#ifndef _tgraph_cpp_
#define _tgraph_cpp_
#include <mem.h> //Used for memset, ANSI std.
#include <dos.h> //Used for MK_FP.
#include <alloc.h>
		 //This is compiler-specific, so
		 //it might not work.
unsigned char far *screen=(char far*)MK_FP(0xA000,0);
unsigned char far *buffer=(char far*)farmalloc(64000);
 //Set up a pointer to the screen

void dpixel(int x,int y,int c){
*(screen+x+y*320)=c; //Pretty obvious....
}

void pixel(int x,int y,int c){
*(buffer+x+y*320)=c;
}

int dgetpixel(int x,int y){
return *(screen+x+y*320); //Also pretty obvious....
}

int getpixel(int x,int y){
return *(buffer+x+y*320); //Also pretty obvious....
}

void dhline(int x1,int x2,int y,int c){
_fmemset(screen+x1+y*320,c,x2-x1);
}

void hline(int x1,int x2,int y,int c){
_fmemset(buffer+x1+y*320,c,x2-x1);
}

void dvline(int y1,int y2,int x,int c){
for(int k=y1;k!=y2;k++)
 dpixel(x,k,c);
}

void vline(int y1,int y2,int x,int c){
for(int k=y1;k!=y2;k++)
 pixel(x,k,c);
}

void palette(int c,int r,int g,int b){
outp(0x3c8,c);
outp(0x3c9,r);
outp(0x3c9,g);
outp(0x3c9,b);
}

void getpal(int c,int *r,int *g,int *b){
outp(0x3c7,c);
*r=inp(0x3c9);
*g=inp(0x3c9);
*b=inp(0x3c9);
}

void dpixmap(int x,int y,char *pix){
int dx=*pix++-'0',dy=*pix++-'0';
for(int n=0;n!=dy;n++)
 //dpixel(x+n%d,y+n/d,*(pix+n));
 _fmemcpy(screen+x+(y+n)*320,pix+n*dx,dx);
}

void pixmap(int x,int y,char *pix){
int dx=*pix++-'0',dy=*pix++-'0';
for(int n=0;n!=dy;n++)
 //dpixel(x+n%d,y+n/d,*(pix+n));
 _fmemcpy(buffer+x+(y+n)*320,pix+n*dx,dx);
}

void dclrgraph(int c){
_fmemset(screen,c,64000);
}

void clrgraph(int c){
_fmemset(buffer,c,64000);
}

void startgraph(){
asm mov ax,0x13 //0x13, mode 13h, see the similarity?
asm int 0x10    //The graphics interrupt
clrgraph(0);
}

void endgraph(){
asm mov ax,0x3  //Pretty basic stuff, same as
asm int 0x10    //startgraph, just mode 3h for text.
}

void display(){
while (inportb(0x3da)&8);
while (!(inportb(0x3da)&8));
_fmemcpy(screen,buffer,64000);
}

#endif