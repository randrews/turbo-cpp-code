#include "bgraph.inc"
#include <conio.h>
#include <iostream.h>
#include <stdio.h>
int *r=new int;
int *g=new int;
int *b=new int;
int tr,tg,tb;
/*void getpal(int c,int *r,int *g,int *b){
outp(0x3c7,c);
*r=inp(0x3c9);
*g=inp(0x3c9);
*b=inp(0x3c9);
}//*/

void main(){
startgraph();
palette(0,32,16,8);
getpal(0,r,g,b);
printf("%i %i %i",*r,*g,*b);
getch();
}