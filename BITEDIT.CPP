#include "graph.inc"
#include <iostream.h>
#include <math.h>
char c;
int pic[8][8];
int x=0,y=0;

void startup(){
startgraph();
palette(1,63,63,63);
palette(2,0,0,32);
for(int n=0;n!=8;n++)
 for(int N=0;N!=8;N++)
  pic[n][N]=0;
}

void drawscrn(){
rectangle(49,49,130,130,4);
for(int n=0;n!=8;n++)
 for(int N=0;N!=8;N++)
  rectangle(50+10*n,50+10*N,59+10*n,59+10*N,pic[n][N],CLOSED);
rectangle(50+x*10,50+y*10,59+x*10,59+y*10,2);
}

void print(){int v;
endgraph();
for(int y=0;y!=8;y++)
 {
 v=0;
 for(int x=0;x!=8;x++)
  {
  if(pic[x][y]==1)
   v+=pow(2,7-x);
  }
 cout<<v<<' ';
 }
getch();
startgraph();
palette(1,63,63,63);
palette(2,0,0,32);
drawscrn();
}

void input(){
switch(c)
 {
 case 'G':x--;
 case 'H':y--;break;
 case 'I':y--;x++;break;
 case 'O':x--;
 case 'P':y++;break;
 case 'Q':x++;y++;break;
 case 'K':x--;break;
 case 'M':x++;break;
 case 'L':if(pic[x][y]==1)pic[x][y]=0;
	  else pic[x][y]=1;break;
 case 'p':print();
 case 'c':for(int x=0;x!=8;x++)
	   for(int y=0;y!=8;y++)
	    pic[x][y]=0;
	  break;
 case 'f':for(x=0;x!=8;x++)
	   for(y=0;y!=8;y++)
	    pic[x][y]=1;
	  break;
 }
if (x<0) x=7;if (x>7) x=0;
if (y<0) y=7;if (y>7) y=0;
}

void main(){
startup();
while(c!='q')
 {
 drawscrn();
 display();
 c=getch();
 input();
 }
}