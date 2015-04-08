#include <graphics.h>
#include <conio.h>
#include <iostream.h>

void main()
{
int d=DETECT,m;
initgraph(&d,&m,"c:..\\bgi");
for (int n=0;n!=100;n++)
putpixel(50+n%16,50+n/16,n);
cout << getdrivername() << " " << getgraphmode();
getch();
}