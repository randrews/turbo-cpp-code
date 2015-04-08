#include "graph.inc"

void main(){int n;
startgraph();
  // The Spectrum palette... Oooh, Aaah....
/*for(n=0;n!=256;n++)
 palette(n,0,63,0);
for(n=0;n!=64;n++)
 {
 palette(n+1,63-n,0,n);
 palette(255-n,63-n,0,n);
 palette(n+65,n,0,63-n);
 palette(192-n,n,0,63-n);
 }
palette(0,0,0,0);*/
for(n=0;n!=256;n++)
 palette(n,0,0,0);
for(n=0;n!=32;n++)
 palette(n,63,n*2,0);
for(n=32;n!=64;n++)
 palette(n,(63-n)*2,63,0);
for(n=64;n!=96;n++)
 palette(n,0,63,n*2);
for(n=96;n!=128;n++)
 palette(n,0,(63-n)*2,63);
for(n=128;n!=160;n++)
 palette(n,n*2,0,63);
for(n=0;n!=32;n++)
 palette(n+160,(63-n),n,(63-n));
for(n=0;n!=32;n++)
 palette(n+192,n+32,n+32,n+32);
//*/
palette(0,0,0,0);

for(int x=0;x!=256;x++)
 for(n=0;n!=10;n++)
  pixel(x+50,n+50,x);

display();
getch();
endgraph();
}