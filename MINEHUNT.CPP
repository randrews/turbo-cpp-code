#include "tile3.cpp"
#include <stdlib.h>
#include <math.h>

int field[30][20];
// 1 for no mine, 2 for mine; + for covered, - for uncovered.
int graphics[5][100];
int *player,*covered,*uncovered,*goal,*mine;
char gf[]="mine2.dat",version[]="1.0b";
int b=0;
int x=0,y=0;
int score=1,nummns;
int p=0;
char c;

void startup();
void redraw();
void input();
int evaluate();

void main(){int gameover=1;
startup();
do
 {
 c=getch();
 input();
 gameover=evaluate();
 redraw();
 } while (gameover==0);
if (gameover==1)
 {
 redraw();
 for(int n=0;n!=600;n++)
 {
 switch(field[n%30][n/30])
  {
  case 2 :
  case -2:layer(uncovered,mine,n%30*10,n/30*10,-1);break;
  }
 }
 tile(player,x*10,y*10,-1);
 display();
 do{c=getch();}while(c!='q');
 endgraph();
 cout << "Kaboom!";
 }
if(gameover==2)
 {
 for(int n=0;n!=600;n++)
 {
 switch(field[n%30][n/30])
  {
  case 2 :
  case -2:layer(uncovered,mine,n%30*10,n/30*10,-1);break;
  }
 }
 tile(player,x*10,y*10,-1);
 display();
 do{c=getch();}while(c!='q');
 endgraph();
 cout << "You won!";
 }
cout << "\n\nScore: " << score << " from a possible " << 600-nummns;
cout << "\nThanks for playing!";
getch();}

void startup(){int mines;
clrscr();
cout << "Minehunt version " << version << "\nBy Ross Andrews.";
cout << "\n\nEmail: nzulch@swbell.net\n       zerblinitzky@yahoo.com";
cout << "\n\nNumber of mines (5<x<100, enter 0 for random): ";cin >> mines;
//StartGfx();ClearGfx(b);
startgraph();
randomize();
// Load graphics:
// 1: player, 2: covered, 3: uncovered, 4: goal, 5: mine.
int *gp=loadtile(gf,"player");
for (int n=0;n!=d*d;n++)
 graphics[0][n]=*(gp+n);
//gp=loadtile(gf,"covered");
gp=loadtile("wargame.dat","grass");
for (n=0;n!=d*d;n++)
 graphics[1][n]=*(gp+n);
//gp=loadtile(gf,"uncovered");
gp=loadtile("wargame.dat","ground");
for (n=0;n!=d*d;n++)
 graphics[2][n]=*(gp+n);
//gp=loadtile(gf,"goal");
gp=loadtile("wargame.dat","redobj");
for (n=0;n!=d*d;n++)
 graphics[3][n]=*(gp+n);
gp=loadtile(gf,"mine");
for (n=0;n!=d*d;n++)
 graphics[4][n]=*(gp+n);
player=&graphics[0][0];
covered=&graphics[1][0];
uncovered=&graphics[2][0];
goal=&graphics[3][0];
mine=&graphics[4][0];
// Now build the board:
// First clear it...
for(n=0;n!=20;n++)
 {
 for(int N=0;N!=30;N++)
  field[N][n]=1;
 }
if (mines==0) mines=random(100)+1;
if (mines>100) mines=100;
if (mines<0) mines=5;
nummns=mines;
// Now mineify it!
int mx=random(30),my=random(20);
for(;mines!=0;mines--)
 {
 while(field[mx][my]!=1||(mx==0&&my==0)||(mx==29&&my==19))
  {
  mx=random(30);my=random(20);
  }
 field[mx][my]=2;
 }
field[0][0]=-1;
// First redraw
evaluate();
redraw();
}

int evaluate(){p=0;
if(x!=0)p+=abs(field[x-1][y])-1;
if(x!=29)p+=abs(field[x+1][y])-1;
if(y!=0)p+=abs(field[x][y-1])-1;
if(y!=19)p+=abs(field[x][y+1])-1;
if(x!=0&&y!=0)p+=abs(field[x-1][y-1])-1;
if(x!=0&&y!=19)p+=abs(field[x-1][y+1])-1;
if(x!=29&&y!=0)p+=abs(field[x+1][y-1])-1;
if(x!=29&&y!=19)p+=abs(field[x+1][y+1])-1;
if(field[x][y]==1)
 {
 field[x][y]*=-1;
 score+=1;
 }
if(field[x][y]==2) return 1;
if(x==29 && y==19) return 2;
return 0;}

void redraw(){
for(int n=0;n!=600;n++)
 {
 switch(field[n%30][n/30])
  {
  case 1 :
  case 2 :tile(covered,n%30*10,n/30*10,-1);break;
  case -1:
  case -2:tile(uncovered,n%30*10,n/30*10,-1);break;
  }
 }
for(n=0;n<p;n++)
 tile(mine,310,n*10,-1);
for(;n!=10;n++)
 blank(310,n*10,b);
// Test platform:
/*for(n=0;n!=600;n++)
 {
 switch(field[n%30][n/30])
  {
  case 2 :
  case -2:tile(mine,n%30*10,n/30*10,-1);break;
  }
 }*/
// End test platform
tile(player,x*10,y*10,-1);
//tile(goal,290,190,0);
layer(uncovered,goal,290,190,0);
display();
}

void input(){
switch(c)
 {
 case 'q':exit(0);
 case 'G':x--;
 case 'H':y--;break;
 case 'I':y--;x++;break;
 case 'O':x--;
 case 'P':y++;break;
 case 'Q':x++;y++;break;
 case 'K':x--;break;
 case 'M':x++;break;
 case 'p':cout << p;getch();break;
 }
if (x<0) x=0;if (x>29) x=29;
if (y<0) y=0;if (y>19) y=19;
}


