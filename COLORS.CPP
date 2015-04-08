#include <conio.h>
#include "graph.inc"
void main(){int side=24,c=8;
startgraph();
for(int y=0;y!=256/side;y++)
 {
 for(int x=0;x!=side;x++)
  {
  //pixel(x+50,y+50,c);
  if(c<=255)
   rectangle(x*5+50,y*5+50,x*5+54,y*5+54,c,CLOSED);
  else {c=15;}
  c++;
  }
 }
display();getch();
}