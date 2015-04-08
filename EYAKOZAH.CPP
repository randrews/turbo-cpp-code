#include <conio.h>
#include <iostream.h>
#include "graph.inc"



void main()
{


startgraph();

for(int y=1;y<150;y++)
for(int x=1;x<256;x++)
{


directpixel(x,y,x);




}
getch();
endgraph();
}