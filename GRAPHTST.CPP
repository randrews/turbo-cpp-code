
#include <graphics.h>
#include <iostream.h>
#include <conio.h>

void main()
{
int driver=VGA,mode=0;
initgraph(&driver,&mode,"");
cout << getgraphmode();
getch();
setgraphmode(1);
cout << endl << getgraphmode();
getch();
setgraphmode(2);
cout << endl << getgraphmode();
getch();
}