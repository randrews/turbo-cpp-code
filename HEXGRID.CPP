#include "tgraph.cpp"
#include <conio.h>

void initgrid(){
startgraph();
}

void closegrid(){
endgraph();
}

void block(int x,int y,int c){
x*=2;
if(y%2==1)x++;
y*=2;
pixel(x,y,c);
pixel(x+1,y,c);
pixel(x,y+1,c);
pixel(x+1,y+1,c);
}

void main(){
initgrid();
block(50,50,15);
block(50,51,15);
block(0,99,4);
for(int n=0;n!=100;n++)
 block(25,n,n);
getch();
closegrid();
}//*/