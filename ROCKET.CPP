#include "graph.inc"
void setpalette(){int n;
for(n=0;n!=32;n++)
 palette(n+16,n+16,0,0);
for(n=32;n!=256;n++)
 palette(n+16,63,40+n/16,0);
for(n=0;n!=16;n++)
 palette(n,n/2,n/2,n/2);
palette(255,63,63,63);
}

void burn(){int t;
for(int y=50;y!=199;y++)
 {
 for(int x=50;x!=199;x++)
  {
  t=(getpixel(x,y)+
     getpixel(x-1,y)+
     getpixel(x+1,y)+
     getpixel(x,y+1)-1)/4;
  pixel(x,y,t);
  }
 }
}

void main(){char c;
startgraph();
setpalette();
for(int j=0;j!=256;j++)
 directpixel(j,50,j);
//display();
getch();
while(c!='q')
 {
 //cleargfx(0);
 for(int n=199;n>=50;n--)
  {
  if(kbhit())break;
  pixel(n,n,255);
  //directpixel(n,n,255);
  burn();
  display();
  }
 c=getch();
 }
endgraph();
}