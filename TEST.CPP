#include <graph.h>
#include <iostream.h>
#include <conio.h>

void main()
{
//int driver=VGA,mode=2;
//initgraph(&driver,&mode,"");
initgraph();
int x=50,y=50;
for(int n=0;n!=100;n++)
 pset(x%10,y/10,n);
getch();
endgraph();
}