#include <conio.h>
#include <iostream.h>
#include <math.h>
void main()
{
double d=0;
clrscr();
cout << "Input Diameter: ";
cin >> d;
clrscr();
cout << "Area: "<< 3.14159*pow((d/2),2) << endl;
cout << "Circumference: "<< 3.14159*d;
getch();
}

