#include <iostream.h>
#include <conio.h>
#include <dos.h>
void main(){int x;
clrscr();cout<<"Piano!";
x=-50;
while(1==1)
 {
 sound(x+50);
 delay(250);nosound();
 x=getch();
 if(x=='q')break;
 }
nosound();
}
