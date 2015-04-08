#include <iostream.h>
#include <conio.h>

void main()
{
char c;
clrscr();
Start:
if (kbhit())
{
c=getch(); if (c=='H') cout << "Up";
cout << c;
}
//cout << 'w';
goto Start;
}