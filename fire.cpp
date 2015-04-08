#include "graph.inc"
#include <stdlib.h>
//#include "palette.cpp"
int pxl;
const int DONTBURN=0,//5, //Number off each edge to skip.
	  BURNFADE=1;//3; //Fade factor.
unsigned char *cl; //Pointer to start of current line.
char c;

void init_colors(){
for(int n=0;n!=64;n++)
 {
 palette(n,n,0,0);
 }
for(n=64;n!=256;n++)
 {
 palette(n,63,0,0);
 }
}

void main(){startgraph();randomize();init_colors();
display();
while(!kbhit()){
for(int y = 0; y < 200; y++)
 {
 cl = off_screen + y * 320;
 for(int x = DONTBURN; x < 320 - DONTBURN; x++)
  {
  pxl = ((*(cl+x)+*(cl+x-1)+*(cl+x+1)
  +*(cl+x+320))>>2) - BURNFADE;
  *(cl+x) = (pxl<0 ? 0 : pxl); //Don't write < 0.
  }
 }
for(int l=0;l!=320;l++)
 {
 if(random(3)==1)pixel(l,199,random(128));
 }
display();}
}