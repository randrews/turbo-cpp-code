#include "graphics.inc"
#include <iostream.h>

int x,c=1;

void rc(int x,int c);

void main()
{
clrscr();
StartGfx();
for (x=50;x!=300;x=x+10)
{
c++;
rc(x,c);
}
cout << "Frodo Lives!";
getch();
EndGfx();
}

void rc(int x, int c)
{
Rectangle(x,100,x+5,105,c,CLOSED);
x=x+10;
}
