#include <conio.h>
#include <iostream.h>
#include <fstream.h>
#include "graphics.inc"
#include <string.h>

const int d=10;
int x=1,y=1,s[(d*d)],clr=0;
int b=0,libfile=0;
char filename[13],c;
ofstream fileout;
ifstream filein;

void sprite(int s[d*d],int x,int y,int t);
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
void redraw();
void input();
void savefile();
void loadfile();
void listtiles();
void killtile();

void main()
{
startup();
do
 {
 if (kbhit())
  {
  input();
  redraw();
  }
 }
 while (c!='q');
}

void input()
{
c=getch();
switch(c)
 {
 case 'l':loadfile();break;
 case 'H':y--;break;
 case 'P':y++;break;
 case 'K':x--;break;
 case 'M':x++;break;
 case 'G':clr--;break;
 case 'I':clr++;break;
 case 'L':s[x-1+d*(y-1)]=clr;break;
 case 's':savefile();break;
 case 'n':cout <<"Name libfile: ";cin>>filename;libfile=1;clrscr();break;
 case 'N':libfile=0;cout << "Libfile unnamed.";getch();clrscr();break;
 case 'T':listtiles();break;
 case 'k':killtile();break;
 case 'b':b=clr;break;
 case 'a':clr-=16;break;
 case '-':clr-=16;break;
 case 'z':clr+=16;break;
 case '+':clr+=16;break;
 case 'c':clr=s[x-1+d*(y-1)];break;
 case 'f':fill();break;
 case 't':transform();break;
 case 'i':invert();break;
 case 'o':otherinvert();break;
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

void redraw()
{
if (x>d) x=d;if (x<1) x=1;
if (y>d) y=d;if (y<1) y=1;
if (clr<0) clr=255;if (clr>255) clr=0;
ClearGfx(b);
int n;
sprite(s,MAXX-40,MIDY,b);
for (n=0;n!=16;n++)
 sprite(s,MIDX+30+d*(n%4),MIDY-d*(n/4),b);
for (n=0;n!=256;n++)
 Rectangle(5+5*(n%16),120+5*(n/16),9+5*(n%16),124+5*(n/16),n,CLOSED);
for (n=0;n!=d*d;n++)
   Rectangle(10+10*(n%d),10+10*(n/d),20+10*(n%d),20+10*(n/d),s[n],CLOSED);
Rectangle(9,9,d*10+11,d*10+11,15,OPEN);
Line(10*x+5,10,x*10+5,10*d+11,15);
Line(10,10*y+5,d*10+11,10*y+5,15);
Rectangle(10*x,10*y,10*x+10,10*y+10,clr,OPEN);
Line(7+5*(clr%16),116,7+5*(clr%16),MAXY,15);
Line(0,122+5*(clr/16),88,122+5*(clr/16),15);
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
{int v;
for (int n=0;n!=d*d;n++)
 s[n]=13;
StartGfx();
redraw();
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

void listtiles()
{char tile[13],f='a';
if (!libfile)
 {
 cout << "Lib file: ";cin >> filename;
 }
filein.open(filename);
if (!filein.fail())
 {
 filein >> tile;filein >> tile;
 cout << tile << "\n";
 while (!filein.eof())
  {
  filein.get(f);
  if (f==':')
   {
   filein >> tile; cout << tile << "\n";
   }
  }
 filein.close();
 getch();
 clrscr();
 }
}

void loadfile()
{char word[13],tile[13];
if (!libfile)
 {
 cout << "Lib file: ";cin >> filename;
 }
cout << "Tile name: ";cin >> tile;
filein.open(filename);
if (!filein.fail())
 {
 while ((strcmp(word,tile)!=0) && (!filein.eof())) filein >> word;
 for (int n=0;n!=d*d;n++) filein >> s[n];
 }
filein.close();
clrscr();
}

void killtile()
{char f,tile[13],ftile[13];int dummy;
if (!libfile)
 {
 cout << "Lib file: ";cin >> filename;
 }
cout << "Tile name: ";cin >> tile;
filein.open(filename);
if (!filein.fail())
 {
 fileout.open("temp.dat");
 filein.get(f);
 while (!filein.eof())
  {
  if (f==':')
   {
   filein >> ftile;
   if (strcmp(ftile,tile)==0)
    {
    for (int n=0;n!=d*d;n++)
     filein >> dummy;
    } else fileout << ": " << ftile;
   } else fileout.put(f);
  filein.get(f);
  }
 filein.close();fileout.close();
 filein.open("temp.dat");fileout.open(filename);
 filein.get(f);
 while (!filein.eof())
  {
  fileout.put(f);filein.get(f);
  }
 fileout.close();
 cout << tile << " deleted.";
 getch();
 }
filein.close();
clrscr();
}

void savefile()
{char f,tile[13],ftile[13];int dummy;
if (!libfile)
 {
 cout << "Lib file: ";cin >> filename;
 }
cout << "Tile name: ";cin >> tile;
filein.open(filename);
if (!filein.fail())
 {
 fileout.open("temp.dat");
 filein.get(f);
 while(!filein.eof())
  {
  if (f==':')
   {
   filein >> ftile;
   if (strcmp(ftile,tile)==0)
    {
    for (int n=0;n!=d*d;n++)
     filein >> dummy;
    } else fileout << ": " << ftile;
   } else fileout.put(f);
  filein.get(f);
  }
 filein.close();fileout.close();
 filein.open("temp.dat");
 fileout.open(filename);
 filein.get(f);
 while(!filein.eof())
  {
  fileout.put(f);filein.get(f);
  }
 filein.close();
 } else fileout.open(filename);
fileout << " : " << tile << "\n";
for (int n=0;n!=d*d;n++)
 fileout << s[n] << " ";
fileout << "\n";
fileout.close();
clrscr();
}
