#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.inc"


void main()
{
int s, x,y;

startgraph();

 while(!kbhit())
 {
 s=random(16000)+2000;
 sound(s);
 s=(rand()%100);
 //x=(s*4)%320;
 //y=(s*4)/320;
 circle(s, s, s, s);
 delay(5);
 display();
 }

nosound();
endgraph();


}

