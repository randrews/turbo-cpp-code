#include "tile.cpp"
const int mx=30,my=20;
int x=0,y=0,ox,oy;
int map[30][20];

int startup();
void drawmap();
int direction(char c);
void input(char c);
void drawsqr();

void main(){char c;
if(startup()==1)
 {
 while(c!='q')
  {
  ox=x;oy=y;
  c=getch();
  if(direction(c)!=1)input(c);
  if(x<0)x=mx-1;if(x>mx-1)x=0;
  if(y<0)y=my-1;if(y>my-1)y=0;
  drawsqr();
  }
 }
}

void drawsqr(){
blank(x*10,y*10,map[x][y]);
blank(ox*10,oy*10,map[ox][oy]);
Rectangle(x*10,y*10,x*10+9,y*10+9,15,OPEN);
}

int direction(char c){int r=0;
switch(c)
 {
 case 'G':x--;
 case 'H':y--;r=1;break;
 case 'I':y--;x++;r=1;break;
 case 'O':x--;
 case 'P':y++;r=1;break;
 case 'Q':x++;y++;r=1;break;
 case 'K':x--;r=1;break;
 case 'M':x++;r=1;break;
 }
return r;
}

void input(char c){
switch(c)
 {
 case ' ':
 case 'L':map[x][y]+=1;break;
 }
}

int startup(){
StartGfx();ClearGfx(0);
for(int n=0;n!=my;n++)
 for(int N=0;N!=mx;N++)
  map[N][n]=4;
//drawmap();
return 1;
}

void drawmap(){
for(int n=0;n!=my;n++)
 for(int N=0;N!=mx;N++)
  blank(N*10,n*10,map[N][n]);
}

