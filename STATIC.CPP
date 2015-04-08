#include "graph.inc"
#include <stdlib.h>
#define prob 4

void main(){
startgraph();randomize();
for(int n=0;n<=prob;n++)
 palette(n,0,0,0);
palette(1,40,40,40);
palette(2,30,30,30);
while(!kbhit())
 {
 for(int x=0;x!=320;x++)
  for(int y=0;y!=200;y++)
   pixel(x,y,random(prob));
 display();
 }
endgraph();
}