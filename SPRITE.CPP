#include <conio.h>
#include <iostream.h>
#include "graphics.inc"
#include <stdlib.h>


void sprite(int s[25],int x,int y,int c);
void input();
int s[25],x,tx,y,c,n,a;

void main()
{
randomize();
clrscr();
input();
clrscr();
StartGfx();
for (a=a;a!=0;a--)
 {
 x=random(320);
 y=random(200);
 sprite(s,x,y,c);
 }
getch();
EndGfx();
}

void sprite(int s[25],int x,int y,int c)
{
 for (n=0;n!=26;n++)
 {
 if (s[n]==1)
  Pixel(x+(n%5),y+(n/5+1),c);
 }
}

void input()
{
cout << "What color do you want: ";
cin >> c;
cout << "How many do you want: ";
cin >> a;
cout << "Put in the sprite (5x5) with\nones as pixels on and zeros as off:\n";
for (n=(0);n!=25;n=n)
 {
 cout << "Line " << n/5+1 << ": ";
 cin >> s[n++] >> s[n++] >> s[n++] >> s[n++] >> s[n++];
 }
}