#include <conio.h>
#include <iostream.h>
#include <math.h>

void main(){
double a,b,c;
Start:
clrscr();
cout << "A: ";
cin >> a;
if (a==0) goto End;
cout << "B: ";
cin >> b;
cout << "C: ";
cin >> c;
cout << "Discriminant: " << b*b-4*a*c << endl;
cout << "Solutions: " << (b*(-1)+sqrt(b*b-4*a*c))/(2*a) << endl
<< "           " << (b*(-1)-sqrt(b*b-4*a*c))/(2*a);
getch();
goto Start;End:}