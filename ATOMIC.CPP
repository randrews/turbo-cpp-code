#include "tile.cpp"
#include <dos.h>
#include <math.h>
#include <stdlib.h>

int x=0,y=0,b=24,board[100];
int corner[d*d],wall[d*d],kaboom[d*d];
int red1[d*d],red2[d*d],red3[d*d];
int blue1[d*d],blue2[d*d],blue3[d*d];
char gf[]="atomic.dat",version[]="1.0b";
int clr=4,p=1; // CLR: Color of square, P: Added to board
	     // (1 for red, -1 for blue player).

const int WcX=110,NcY=60,EcX=200,ScY=150;
const int WX=120,EX=190,NY=70,SY=140;

void redraw();
void input(char c);
void startup();
void evaluate();

void main()
{char c;
startup();
while (c!='q')
 {
 c=getch();
 input(c);
 evaluate();
 redraw();
 }
exit(0);
}

void startup()
{
clrscr();
cout << "Atomic v. " << version << "\nBy Ross Andrews.";
cout << "\n\nEmail: nzulch@swbell.net\n       zerblinitzky@yahoo.com";
getch();
StartGfx();
ClearGfx(b);
for (int n=0;n!=100;n++) // Init board
 board[n]=0;
for (n=0;n!=d*d;n++)
 corner[n]=*(loadtile(gf,"corner")+n); //Load graphics from atomic.dat
for (n=0;n!=d*d;n++)
 wall[n]=*(loadtile(gf,"wall")+n);
for (n=0;n!=d*d;n++)
 kaboom[n]=*(loadtile(gf,"kaboom")+n);
for (n=0;n!=d*d;n++)
 red1[n]=*(loadtile(gf,"1red")+n);
for (n=0;n!=d*d;n++)
 red2[n]=*(loadtile(gf,"2red")+n);
for (n=0;n!=d*d;n++)
 red3[n]=*(loadtile(gf,"3red")+n);
for (n=0;n!=d*d;n++)
 blue1[n]=*(loadtile(gf,"1blue")+n);
for (n=0;n!=d*d;n++)
 blue2[n]=*(loadtile(gf,"2blue")+n);
for (n=0;n!=d*d;n++)
 blue3[n]=*(loadtile(gf,"3blue")+n);
redraw(); // First redraw
}

void redraw()
{//Draws the board.
//ClearGfx(b); // Uncomment for old, flickery method.
tile(corner,WcX,NcY,b);// Corners
tile(vertical(corner),EcX,NcY,b);
tile(horizontal(corner),WcX,ScY,b);
tile(yxinvert(corner),EcX,ScY,b);
for(int n=0;n!=8;n++) // Walls
 tile(wall,WX+n*10,NcY,b);
for(n=0;n!=8;n++)
 tile(horizontal(wall),WX+n*10,ScY,b);
for(n=0;n!=8;n++)
 tile(ccwrotate(wall),WcX,NY+n*10,b);
for(n=0;n!=8;n++)
 tile(cwrotate(wall),EcX,NY+n*10,b);
/*for(n=0;n!=64;n++)
 Rectangle(WX+10*(n%8),NY+10*(n/8),WX+9+10*(n%8),NY+9+10*(n/8),15,OPEN);*/
for (n=0;n!=64;n++)
 {
 switch (board[n])
  {
  case 0:for(int N=0;N!=d*d;N++)
	 Pixel(WX+10*(n%8)+N%10,NY+10*(n/8)+N/10,b);break;
	 // Comment for old, flickery method.
  case 1:tile(red1,WX+10*(n%8),NY+10*(n/8),b);break;
  case 2:tile(red2,WX+10*(n%8),NY+10*(n/8),b);break;
  case 3:tile(red3,WX+10*(n%8),NY+10*(n/8),b);break;
  case -1:tile(blue1,WX+10*(n%8),NY+10*(n/8),b);break;
  case -2:tile(blue2,WX+10*(n%8),NY+10*(n/8),b);break;
  case -3:tile(blue3,WX+10*(n%8),NY+10*(n/8),b);break;
  }
 }
Rectangle(WX+10*x,NY+10*y,WX+9+10*x,NY+9+10*y,clr,OPEN);
}

void input(char c)
{
switch (c)
 {
 case 'v':cout << "Atomic v. " << version;getch();break;
 case 'H':y--;break;
 case 'P':y++;break;
 case 'K':x--;break;
 case 'M':x++;break;
 case 'L':
 case ' ':{
	  if (board[y*8+x]*p>=0)
	   {
	   board[y*8+x]+=p;p*=-1;
	   if (p==-1) clr=1;else clr=4;
	   }
	  break;
	  }
 }
if (x<0) x=0; if (x>7) x=7;
if (y<0) y=0; if (y>7) y=7;
}

void evaluate()
{
int doagain=0,olddo;
int topedge[6]={1,2,3,4,5,6};
int btmedge[6]={57,58,59,60,61,62};
int rtedge[6]={15,23,31,39,47,55};
int ltedge[6]={8,16,24,32,40,48};
int middle[36]={9,10,11,12,13,14,
		17,18,19,20,21,22,
		25,26,27,28,29,30,
		33,34,35,36,37,38,
		41,42,43,44,45,46,
		49,50,51,52,53,54};

int exp,n,s,e,w;
do
 {
 olddo=doagain;
 if (abs(board[0])>=2) // Corners:
  {
  doagain++;
  board[0]=0;
  tile(kaboom,WX,NY,b);
  delay(50);
  if (board[1]*p*-1<=0) board[1]*=-1;board[1]-=p;
  if (board[8]*p*-1<=0) board[8]*=-1;board[8]-=p;
  }
 if (abs(board[7])>=2)
  {
  doagain++;
  board[7]=0;
  tile(kaboom,EX,NY,b);
  delay(50);
  if (board[6]*p*-1<=0) board[6]*=-1;board[6]-=p;
  if (board[15]*p*-1<=0) board[15]*=-1;board[15]-=p;
  }
 if (abs(board[56])>=2)
  {
  doagain++;
  board[56]=0;
  tile(kaboom,WX,SY,b);
  delay(50);
  if (board[48]*p*-1<=0) board[48]*=-1;board[48]-=p;
  if (board[57]*p*-1<=0) board[57]*=-1;board[57]-=p;
  }
 if (abs(board[63])>=2)
  {
  doagain++;
  board[63]=0;
  tile(kaboom,EX,SY,b);
  delay(50);
  if (board[62]*p*-1<=0) board[62]*=-1;board[62]-=p;
  if (board[55]*p*-1<=0) board[55]*=-1;board[55]-=p;
  }
 for(int N=0;N!=6;N++) // For loop for right edge.
  {
  exp=rtedge[N];
  if (abs(board[exp])>=3)
   {
   n=exp-8;s=exp+8;w=exp-1;
   doagain++;
   board[exp]=0;
   tile(kaboom,EX,NY+10*(exp/8),b);
   delay(50);
   if (board[n]*p*-1<=0) board[n]*=-1;board[n]-=p;
   if (board[s]*p*-1<=0) board[s]*=-1;board[s]-=p;
   if (board[w]*p*-1<=0) board[w]*=-1;board[w]-=p;
   }
  }
 for(N=0;N!=6;N++) // For loop for left edge.
  {
  exp=ltedge[N];
  if (abs(board[exp])>=3)
   {
   n=exp-8;s=exp+8;e=exp+1;
   doagain++;
   board[exp]=0;
   tile(kaboom,WX,NY+10*(exp/8),b);
   delay(50);
   if (board[n]*p*-1<=0) board[n]*=-1;board[n]-=p;
   if (board[s]*p*-1<=0) board[s]*=-1;board[s]-=p;
   if (board[e]*p*-1<=0) board[e]*=-1;board[e]-=p;
   }
  }
 for(N=0;N!=6;N++) // For loop for btm edge.
  {
  exp=btmedge[N];
  if (abs(board[exp])>=3)
   {
   n=exp-8;w=exp-1;e=exp+1;
   doagain++;
   board[exp]=0;
   tile(kaboom,WX+10*(exp%8),SY,b);
   delay(50);
   if (board[n]*p*-1<=0) board[n]*=-1;board[n]-=p;
   if (board[w]*p*-1<=0) board[w]*=-1;board[w]-=p;
   if (board[e]*p*-1<=0) board[e]*=-1;board[e]-=p;
   }
  }
 for(N=0;N!=6;N++) // For loop for top edge.
  {
  exp=topedge[N];
  if (abs(board[exp])>=3)
   {
   s=exp+8;w=exp-1;e=exp+1;
   doagain++;
   board[exp]=0;
   tile(kaboom,WX+10*(exp%8),NY,b);
   delay(50);
   if (board[s]*p*-1<=0) board[s]*=-1;board[s]-=p;
   if (board[w]*p*-1<=0) board[w]*=-1;board[w]-=p;
   if (board[e]*p*-1<=0) board[e]*=-1;board[e]-=p;
   }
  }
 for(N=0;N!=36;N++) // For loop for middle.
  {
  exp=middle[N];
  if (abs(board[exp])>=4)
   {
   n=exp-8;s=exp+8;w=exp-1;e=exp+1;
   doagain++;
   board[exp]=0;
   tile(kaboom,WX+10*(exp%8),NY+10*(exp/8),b);
   delay(50);
   if (board[n]*p*-1<=0) board[n]*=-1;board[n]-=p;
   if (board[s]*p*-1<=0) board[s]*=-1;board[s]-=p;
   if (board[w]*p*-1<=0) board[w]*=-1;board[w]-=p;
   if (board[e]*p*-1<=0) board[e]*=-1;board[e]-=p;
   }
  }

 if (olddo==doagain) doagain=0; // Check for any change in doagain
 else
  {
  doagain=1;
  n=0;s=0;
  for (N=0;N!=64;N++)
   {
   if (board[N]<0) s++;
   if (board[N]>0) n++;
   }
  if (n==0)
   {
   cout << "Blue Wins!";
   getch();
   exit(0);
   }
  if (s==0)
   {
   cout << "Red wins!";
   getch();
   exit(0);
   }
  }
 } while (doagain==1);
}
