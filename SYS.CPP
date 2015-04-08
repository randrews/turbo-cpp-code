#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//#include <iostream.h>

void main(){char *cmd;
/*textcolor(LIGHTGREEN);
textbackground(BLUE);
clrscr();//*/
asm mov ax, 0x14
asm int 0x10
gets(cmd);
system(cmd);
getch();
}