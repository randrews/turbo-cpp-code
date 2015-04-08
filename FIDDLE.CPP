#include "graph.inc"
#include "palette.cpp"
void main(){RGB_color_ptr col;
startgraph();
for(int n=0;n!=255;n++)
 {
 col->red  =n/4;
 col->blue =n/4;
 col->green=n/4;
 set_pal(n,col);
 }
palette(0,27,0,0);
for(n=0;n!=255;n++)
 pixel(n+50,50,n);
display();
getch();
}