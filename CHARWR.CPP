#include <conio.h>
#include <stdio.h>

void drawchar(int x,int y,int fg,int bg,char c){
_DH=x;
_DL=y;
_AH=2;
asm int 0x10
_AX=c;
_BH=bg;
_BL=fg;
_CX=1; // Num of times
_AH=9;
asm int 0x10
}

void main(){
asm{
mov ax,0x13
int 0x10
}
drawchar(1,1,8,0,' ');
drawchar(3,3,8,0,'1');
getch();
drawchar(1,1,8,0,'2');
getch();
drawchar(1,1,8,0,'3');
getch();

asm{
mov ax,0x3
int 0x10
}
}