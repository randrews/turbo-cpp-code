#include <iostream.h>
#include <conio.h>
#include <fstream.h>

void main()
{
ofstream fileout;
ifstream filein;
int x,n;
fileout.open("frodo.dat");
clrscr();
cout << "Put in five numbers: " << endl;
for (n=0;n!=5;n++)
{
cout << "Number: ";
cin >> x;
fileout << x << " ";
}
fileout.close();
filein.open("frodo.dat");
for (n=0;n!=5;n++)
{
filein >> x;
cout << x << " ";
}
filein.close();
getch();
}