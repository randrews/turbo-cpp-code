#include <conio.h>
#include <iostream.h>
void main()
{
int q,p,n,d,b;
double t;
clrscr();
cout << "Amt of paper money: $";
cin >> b;
cout << endl << "Number of Pennies: ";
cin >> p;
cout << endl << "Number of Nickels: ";
cin >> n;
cout << endl << "Number of Dimes: ";
cin >> d;
cout << endl << "Number of Quarters: ";
cin >> q;
t = p + (5 * n) + (10 * d) + (25 * q) + (100 * b);
clrscr();
cout << "Total amt of money: $" << (t/100);
getch();
}

