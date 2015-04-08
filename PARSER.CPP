#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <fstream.h>

void main()
{
ifstream filein;
char c,cmnd[10];
clrscr();
filein.open("ztslcode.tsl");
filein.get(c);
while(!filein.eof())
 {
 if (c==':')
  {
  filein >> cmnd;
  cout << cmnd << endl;
  }
 filein.get(c);
 }
getch();
}