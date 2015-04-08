#include <iostream.h>
#include <conio.h>
#include <stdio.h>
void main(){int x;
clrscr();
while(x!=0)
 {
 cout<<"Enter graph mode: ";
 cin>>x;
 asm mov ax,x
 asm int 0x10
 }
}
