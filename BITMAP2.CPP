#include <iostream.h>
#include <conio.h>
#include "tile.cpp"
#define gf "font.bit"
#define filename "font.bit"
#define tile "9"
void main(){
startgraph();
fontload();
//charout('9',50,50,15,0);
/*strout("abcdefghijklmnopqrstuvwxyz ",50,50,41,4);
directstrout("ABCDEFGHIJKLMNOPQRSTUVWXYZ ",50,60,42,5);
strout("1234567890.",50,55,51,3);
getch();*/
strout(" ___\n |||\n |||\n\\|||/\n \\_/\n  ",100,100,15,0);
strout("Hi, everybody!",50,50,12,0);
strout("HI, DR. NICK!!",50,55,10,0);
display();
getch();
}