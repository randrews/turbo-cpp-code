#include <iostream.h>
#include <conio.h>
#include <math.h>

int func(int a,int b);

int a,b;//,c;
void main()
{
clrscr();
cout << "What's side A: ";
cin >> a;
cout << "What's side B: ";
cin >> b;
//func(a,b);
clrscr();
cout << "Side C: " << func(a,b);
}

int func(int a,int b)
{
a=pow(a,2);
b=pow(b,2);
//c=pow(a+b,0.5);
return pow(a+b,0.5);
}