// Simple and tiny graphics library.
// All is done directly to the screen, and has
// no advanced graphics functions like a line
// or a circle. But it's small and easy to use.
// -Zerblinitzky
#ifndef _tgraph_cpp_
#define _tgraph_cpp_
#include <mem.h> //Used for memset, ANSI std.
#include <dos.h> //Used for MK_FP.
		 //This is compiler-specific, so
		 //it might not work.
unsigned char far *screen=(char far*)MK_FP(0xA000,0);
 //Set up a pointer to the screen
void pixel(int x,int y,int c){
*(screen+x+y*320)=c; //Pretty obvious....
}

int getpixel(int x,int y){
return *(screen+x+y*320); //Also pretty obvious....
}

void hline(int x1,int x2,int y,int c){
_fmemset(screen+x1+y*320,c,x2-x1);
}

void vline(int y1,int y2,int x,int c){
for(int k=y1;k!=y2;k++)
 pixel(x,k,c);
}

void cleargraph(int c){
_fmemset(screen,c,64000);
}

void startgraph(){
asm mov ax,0x13 //0x13, mode 13h, see the similarity?
asm int 0x10    //The graphics interrupt
}

void endgraph(){
asm mov ax,0x3  //Pretty basic stuff, same as
asm int 0x10    //startgraph, just mode 3h for text.
}

#endif