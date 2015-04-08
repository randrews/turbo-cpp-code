#include <iostream.h>
#include <conio.h>
#include <math.h>
void main()
{
float A=0;
float B=0;
float C=0;
clrscr();
cout << "Pythagorean Theorem:" << endl;
cout << "C=(A^2 + B^2)^(1/2)" << endl;
cout << "What is A?" << endl;
cin >> A;
cout << endl;
cout << "What is B?" << endl;
cin >> B;
clrscr();
C = pow(B,2) + pow(A,2);
C = pow(C,.5);
cout << C;
getch();
}