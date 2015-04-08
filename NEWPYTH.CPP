#include <iostream.h>
#include <conio.h>
#include <math.h>
void main()
{
double a,b,c;
a=0;
b=a;
c=b;
clrscr();
cout << "Input side A length or 0:" << endl;
cin >> a;
cout << "Input side B length or 0:" << endl;
cin >> b;
cout << "input side C length or 0:" << endl;
cin >> c;
if (a * b > 0)
c = pow(pow(a,2)+pow(b,2),.5);
if (a * c > 0)
b = pow(pow(c,2)-pow(a,2),.5);
if (b * c > 0)
a = pow(pow(c,2)-pow(b,2),.5);
clrscr();
cout << "Side A length: " << a << endl;
cout << "Side B length: " << b << endl;
cout << "Side C length: " << c << endl;
getch();
}

