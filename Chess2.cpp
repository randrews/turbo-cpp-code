#include "graph.inc"
#include <iostream.h>
#define basex 50
#define basey 50
class piece{
public:
 char type; // Lowercase: black Uppercase: white
 char side; // w / b / e
 int sqrcol;
 void disp(int x,int y);
 void assignpic(int *picp);
 piece operator = (piece rvalue);
 friend void initpics();
private:
 int pic[8];
};

piece piece::operator = (piece rvalue){
type=rvalue.type;
side=rvalue.side;
for(int n=0;n!=8;n++)
 pic[n]=rvalue.pic[n];
return *this;
}

void piece::disp(int x,int y){
int c,b=sqrcol;
if(side=='w')c=1;
else c=2;
for(int Y=0;Y!=8;Y++)
 {
 for(int X=0;X!=8;X++)
  {
  if((pic[Y]>>(7-X))%2==1)
   pixel(x+X,y+Y,c);
  else
   pixel(x+X,y+Y,b);
  }
 }
}

void piece::assignpic(int *picp){
for(int n=0;n!=8;n++)
 pic[n]=*(picp+n);
}
piece empty;
// Done with class decls.
piece board[8][8];
//          x  y
void initboard(){
int pawnpic[]={24,60,60,24,24,24,126,255};
int rookpic[]={90,126,60,60,60,60,126,255};
int knightpic[]={28,62,63,58,56,56,124,254};
int bishoppic[]={16,52,44,60,24,24,60,126};
int queenpic[]={16,124,56,56,56,56,124,254};
int kingpic[]={8,28,8,28,28,28,62,127};
int emptypic[]={0,0,0,0,0,0,0,0};
char layout[]={'r','n','b','q','k','b','n','r'};
palette(1,63,63,63);
//Make the empty piece
empty.assignpic(emptypic);
empty.side='e';
empty.type=' ';
// Board assign
board[0][7].assignpic(rookpic);
board[0][0].assignpic(rookpic);
board[1][7].assignpic(knightpic);
board[1][0].assignpic(knightpic);
board[2][7].assignpic(bishoppic);
board[2][0].assignpic(bishoppic);
board[3][7].assignpic(queenpic);
board[3][0].assignpic(queenpic);
board[4][7].assignpic(kingpic);
board[4][0].assignpic(kingpic);
board[5][7].assignpic(bishoppic);
board[5][0].assignpic(bishoppic);
board[6][7].assignpic(knightpic);
board[6][0].assignpic(knightpic);
board[7][7].assignpic(rookpic);
board[7][0].assignpic(rookpic);
for(int n=0;n!=8;n++)
 {
 for(int j=2;j<=5;j++)
  board[n][j].assignpic(emptypic);
 board[n][1].assignpic(pawnpic);
 board[n][6].assignpic(pawnpic);
 board[n][0].side='b';
 board[n][1].side='b';
 board[n][6].side='w';
 board[n][7].side='w';
 board[n][1].type='p';
 board[n][6].type='p';
 }
for(int j=0;j!=8;j++)
 {
 board[j][0].type=layout[j];
 board[j][7].type=layout[j];
 }
for(j=0;j<8;j+=2)
 {
 board[j][0].sqrcol=4;
 board[j][2].sqrcol=4;
 board[j][4].sqrcol=4;
 board[j][6].sqrcol=4;
 board[j][1].sqrcol=3;
 board[j][3].sqrcol=3;
 board[j][5].sqrcol=3;
 board[j][7].sqrcol=3;
 }
for(j=1;j<8;j+=2)
 {
 board[j][0].sqrcol=3;
 board[j][2].sqrcol=3;
 board[j][4].sqrcol=3;
 board[j][6].sqrcol=3;
 board[j][1].sqrcol=4;
 board[j][3].sqrcol=4;
 board[j][5].sqrcol=4;
 board[j][7].sqrcol=4;
 }
/*for(int y=0;y!=8;y++)
 {
 for(int x=0;x!=8;x++)
  cout<<board[x][y].type;
 cout<<'\n';
 }
//
//Test
/*
piece test;
for(int n=0;n!=8;n++)
 test.pic[n]=40;
test.disp(50,50);
//*/
}

void drawboard(){
for(int x=0;x!=8;x++)
 for(int y=0;y!=8;y++)
  board[x][y].disp(basex+x*8,basey+y*8);
}

void godkey(){
//cout << m;
}
int vpawn(int x,int y,int ox,int oy)
{ int z=0;
  if (x==ox && y==oy-1) z=1;
  return z;
}

int vrook(int x,int y,int ox,int oy) {return 1;}
int vknight(int x,int y,int ox,int oy) {return 1;}
int vqueen(int x,int y,int ox,int oy) {return 1;}
int vking(int x,int y,int ox,int oy) {return 1;}

int validate(int x,int y,int ox,int oy)
{int w=0;
switch (board[x][y].type)
  { case 'p': w=vpawn(x,y,ox,oy);
    case 'r': w=1;break;
    case 'k': w=1;break;
    case 'q': w=1;break;
    case 'b': w=1;break;
    case 'n': w=1;break;
  }
return w;
}


int input(char c,int *x,int *y){
switch(c)
 {
 //case 'q':exit(0);
 case 'G':(*x)--;
 case 'H':(*y)--;break;
 case 'I':(*y)--;(*x)++;break;
 case 'O':(*x)--;
 case 'P':(*y)++;break;
 case 'Q':(*x)++;(*y)++;break;
 case 'K':(*x)--;break;
 case 'M':(*x)++;break;
 case 'L':return 1;
 case '`':return 1;
 case ' ':return 1;
 case '\r':return 1;
 case 'g':godkey();break;
 //case 'p':cout << p;getch();break;
 }
if (*x<0) *x=0;if (*x>7) *x=7;
if (*y<0) *y=0;if (*y>7) *y=7;
return 0;
}

void handleclicks(int *x,int *y,int *currplyr,
		  int *mode,int *ox,int *oy){
char plyr;
int tempx=*ox,tempy=*oy;
if(*currplyr==1)plyr='w';else plyr='b';
if(*mode==0)
 {
 if(board[*x][*y].side==plyr)
  {
   /*if (validate(*x,*y,*ox,*oy))*/
   {*mode=1;*ox=*x;*oy=*y; return;}
  }
 }
else
 {
 if(board[*x][*y].side!=plyr)
  {
  if(validate(*x,*y,*ox,*oy))
   {
   board[*x][*y]=board[*ox][*oy];
   board[*ox][*oy]=empty;
   *mode=0;
   if(*currplyr==1)*currplyr=2;
    else *currplyr=1;
   }
  }
 }
}

void loop(){int x=0,y=0,currplyr=1,mode=0,ox,oy;char c;
while(c!=27)
 {
 if (input(c,&x,&y))handleclicks(&x,&y,&currplyr,&mode,&ox,&oy);
 drawboard(); // First draw
 rectangle(basex+8*x,basey+8*y,basex+7+8*x,basey+7+8*y,currplyr);
 display();
 c=getch();
 if(c=='g')
  {
  cout<<mode;
  getch();
  }
 }
}


void main(){
startgraph();
palette(3,4,4,4);
palette(4,8,8,8);
palette(1,63,63,63);
palette(2,32,32,32);
// Palette: 1: White piece, 2: Black piece
//          3: Black square, 4: White square
initboard();
loop();
endgraph();
/*clrscr();
int x=45;
for(int n=0;n!=8;n++)
 cout<<(x>>(7-n))%2<<' ';
getch();//*/
}