#include <conio.h>
#include <iostream.h>
#include <fstream.h>
#include "graphics.inc"
#include <string.h>

const int d=5;
int x=0,y=0,s[(d*d)],down[100],left[100];
int b=0;
char filename[12],c;
ofstream fileout;
ifstream filein;

void sprite(int s[d*d],int x,int y,int t);
void startup();
void maketemp();
void readfile(char filename[12]);
void redraw();
void input();
void ProgExit();
void loadfile();

void main()
{
startup();
maketemp();
readfile("temp.dat");
clrscr();
cout << "Do you need help? Y/N: ";
cin >> c;
if (c=='y' ^ c=='Y')
 {
 clrscr();
 cout << "This program edits sprites for games and stores them" << endl
 << "as files containing number values for the color of the pixels." << endl
 << endl << "S : Save file\nL : Load file\n7 : Color left\n9 : Color right"
 << endl << "Q : Quit\nArrow Keys : Move cursor"
 << endl << endl << "Num Lock must be on for the program to work properly."
 << endl << endl << "Purple pixels are transparent in engine.";
 getch();
 }
StartGfx();
Loop:
redraw();
c=getch();
if (c=='q' ^ c=='Q')
 goto End;
input();
if (x>d) x=d;
if (x<0) x=0;
if (y>d) y=d;
if (y<0) y=0;
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
/*down[2]=c;down[7]=c;down[10]=c;
down[12]=c;down[14]=c;down[16]=c;
down[17]=c;down[18]=c;down[22]=c;
left[2]=c;left[8]=c;left[10]=c;
left[11]=c;left[12]=c;left[13]=c;
left[14]=c;left[18]=c;left[22]=c;*/
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

sprite(s,MAXX-40,MIDY,b);
for (int n=0;n!=d*d;n++)
 sprite(s,MIDX+50+5*(n%d),MIDY-5*(n/d),b);

Rectangle(56,56,107,107,15,OPEN);
for (n=0;n!=d*d;n++)
 Rectangle(57+10*(n%d),57+10*(n/d),66+10*(n%d),66+10*(n/d),s[n],CLOSED);

sprite(down,51+10*x,55,b);
sprite(left,51,64+10*y,b);


}

void input()
{
switch(c)
 {
 case 'l':loadfile();break;
 case 'L':loadfile();break;
 case '8':y=y-1;break;
 case '2':y=y+1;break;
 case '4':x=x-1;break;
 case '6':x=x+1;break;
 }
}

void loadfile()
{
cout << "File name: ";
cin >> filename;
readfile(filename);
clrscr();
}

