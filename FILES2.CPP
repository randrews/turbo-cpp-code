#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <string.h>

void main()
{
int s[5],n,x;
char filename[12];
ofstream fileout;
ifstream filein;
clrscr();
cout << "File name:";
cin >> filename;
strcat(filename,".dat");
cout << "OK, give me 5 ints:" << endl;
fileout.open(filename);
for (n=0;n!=5;n++)
{
cout << "Int #" << n+1 << ": ";
cin >> x;
fileout << x << " ";
}
fileout.close();
clrscr();
filein.open(filename);
for (n=0;n!=5;n++)
{
filein >> x;
cout << "Number " << n+1 << ": " << x << endl;
}
getch();
filein.close();
}

