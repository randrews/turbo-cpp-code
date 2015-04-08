#include <conio.h>
#include <iostream.h>
#include <fstream.h>
#include "graphics.inc"
#include <string.h>

const int d=10;
int x=1,y=1,s[(d*d)],down[100],left[100],clr=0;
int b=0;
char filename[12],c;
ofstream fileout;
ifstream filein;

void sprite(int s[d*d],int x,int y,int t);
void downarrow(int x,int y);
void leftarrow(int x,int y);
void fill();
void transform();
void invert();
void otherinvert();
void horizontal();
void vertical();
void rotate();
void ccwrotate();
void move();
void movedown();
void startup();
void maketemp();
void readfile(char filename[12]);
void redraw();
void input();
void savefile();
void loadfile();

void main()
{
startup();
maketemp();
readfile("temp.dat");
StartGfx();
Loop:
redraw();
if (kbhit()) c=getch();
if (c=='q' ^ c=='Q')
 goto End;
input();
if (x>d) x=d;
if (x<1) x=1;
if (y>d) y=d;
if (y<1) y=1;
if (clr<0) clr=255;
if (clr>255) clr=0;
goto Loop;
End:
EndGfx();
clrscr();
}


void sprite(int s[d*d],int x,int y,int t)
{
for (int n=0;n!=(d*d);n++)
 {
 Pixel (x+n%d,y+(n/d),s[n]);
 if (s[n]==13)
  Pixel (x+n%d,y+(n/d),t);
 }
}

void startup()
{
int c=15,v;
filein.open("down.dat");
for (int n=0;n!=100;n++)
 {
 filein >> v;
 if (v==1) down[n]=c;
 }
filein.close();
filein.open("left.dat");
for (n=0;n!=100;n++)
 {
 filein >> v;
 if (v==1) left[n]=c;
 }
filein.close();
}

void maketemp()
{
strcpy(filename,"temp");
fileout.open(strcat(filename,".dat"));
for (int n=0;n!=(d*d);n++)
 fileout << 13 << " ";
fileout.close();
}

void readfile(char filename[12])
{
filein.open(filename);
for (int n=0;n!=(d*d);n++)
 filein >> s[n];
filein.close();
}

void redraw()
{
ClearGfx(b);
int n;
sprite(s,MAXX-40,MIDY,b);
for (n=0;n!=16;n++)
 sprite(s,MIDX+30+d*(n%4),MIDY-d*(n/4),b);

for (n=0;n!=256;n++)
 Rectangle(5+5*(n%16),120+5*(n/16),9+5*(n%16),124+5*(n/16),n,CLOSED);

for (n=0;n!=d*d;n++)
   Rectangle(11+10*(n%d),11+10*(n/d),20+10*(n%d),20+10*(n/d),s[n],CLOSED);
downarrow(10*x+1,0);
leftarrow(0,10*y+1);
Rectangle(10,10,d*10+11,d*10+11,15,OPEN);

Line(10*x+5,10,x*10+5,10*d+11,15);
Line(10,10*y+5,d*10+11,10*y+5,15);
Rectangle(10*x,10*y,10*x+10,10*y+10,clr,OPEN);

Line(7+5*(clr%16),116,7+5*(clr%16),MAXY,15);
Line(0,122+5*(clr/16),88,122+5*(clr/16),15);
}

void downarrow(int x,int y)
{
for (int n=0;n!=100;n++)
 {
 Pixel (x+n%10,y+n/10,down[n]);
 if (down[n]==0) Pixel (x+n%10,y+n/10,b);
 }
}

void leftarrow(int x,int y)
{
for (int n=0;n!=100;n++)
 {
 Pixel (x+n%10,y+n/10,left[n]);
 if (left[n]==0) Pixel (x+n%10,y+n/10,b);
 }
}



void input()
{
switch(c)
 {
 case 'l':loadfile();break;
 case 'L':loadfile();break;
 case '8':y--;break;
 case '2':y++;break;
 case '4':x--;break;
 case '6':x++;break;
 case '7':clr--;break;
 case '9':clr++;break;
 case '5':s[x-1+d*(y-1)]=clr;break;
 case 's':savefile();break;
 case 'S':savefile();break;
 case 'b':b=clr;break;
 case 'B':b=clr;break;
 case 'a':clr-=16;break;
 case '-':clr-=16;break;
 case 'z':clr+=16;break;
 case '+':clr+=16;break;
 case 'c':clr=s[x-1+d*(y-1)];break;
 case 'f':fill();break;
 case 't':transform();break;
 case 'i':invert();break;
 case 'I':otherinvert();break;
 case 'h':horizontal();break;
 case 'v':vertical();break;
 case 'r':rotate();break;
 case 'R':ccwrotate();break;
 case ';':move();break;
 case '/':movedown();break;
 case ',':rotate();move();ccwrotate();break;
 case '.':rotate();movedown();ccwrotate();break;
 }
}

void fill()
{
for (int n=0;n!=d*d;n++)
 s[n]=clr;
}

void transform()
{
int old=s[x-1+d*(y-1)];
for (int n=0;n!=d*d;n++)
 if (s[n]==old) s[n]=clr;
}

void invert()
{
int z[d*d];
for (int n=d*d;n!=0;n--)
 z[d*d-n]=s[n-1];
for (n=0;n!=d*d;n++)
 s[n]=z[n];
}

void otherinvert()
{
int z[d*d],n;
for (n=0;n!=d*d;n++)
 z[n]=s[d*(d-n%d-1)+(d-n/d-1)];
for (n=0;n!=d*d;n++)
 s[n]=z[n];
}

void vertical()
{
int z[d*d],n;
for (n=0;n!=d*d;n++)
 z[n]=s[d*(n/d)+(d-n%d-1)];
for (n=0;n!=d*d;n++)
 s[n]=z[n];
}

void rotate()
{
int z[d*d],n;
for (n=0;n!=d*d;n++)
 z[n]=s[d*(d-n%d-1)+(n/d)];
// z[n]=s[d*(n%d)+(d-n/d-1)];
for (n=0;n!=d*d;n++)
 s[n]=z[n];
}

void ccwrotate()
{
int z[d*d],n;
for (n=0;n!=d*d;n++)
 z[n]=s[d*(n%d)+(d-n/d-1)];
for (n=0;n!=d*d;n++)
 s[n]=z[n];
}

void move()
{
int z[d*d],n;
for (n=0;n!=d*d;n++)
 {
 if (n>d*(d-1)-1)
  {
  z[n]=s[n%d];
  }
 else
  {
  z[n]=s[n+d];
  }
 }
for (n=0;n!=d*d;n++)
 s[n]=z[n];
}

void movedown()
{
horizontal();
move();
horizontal();
}

void horizontal()
{
invert();
vertical();
}

void loadfile()
{
cout << "Load file: ";
cin >> filename;
readfile(filename);
clrscr();
}

void savefile()
{
cout << "Save as: ";
cin >> filename;
fileout.open(filename);
for (int n=0;n!=d*d;n++)
 fileout << s[n] << " ";
fileout.close();
clrscr();
}