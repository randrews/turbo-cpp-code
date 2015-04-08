#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>

void main()
{
ofstream fileout;
ifstream filein;
char tofile[12],fromfile[12],name[12],d;
FILE *fp;
clrscr();
cout << "Copy to file: ";
gets(tofile);
Start:
cout << "Copy from file: ";
gets(fromfile);
cout << "Name: ";
gets(name);
fp=fopen("temp.tmp","w+");
fclose(fp);
if(!(fp=fopen(tofile,"r+"))) fp=fopen(tofile,"w+");
fileout.open("temp.tmp");
filein.open(tofile);
 filein.get(d);
 while(!filein.eof())
  {
  fileout.put(d);
  filein.get(d);
  }
filein.close();
filein.open(fromfile);
fileout.close();
fileout.open(tofile);
fileout << "\n" << name << "\n";
 filein.get(d);
 while(!filein.eof())
  {
  fileout.put(d);
  filein.get(d);
  }
filein.close();
filein.open("temp.tmp");
 filein.get(d);
 while(!filein.eof())
  {
  fileout.put(d);
  filein.get(d);
  }
fileout.close();
filein.close();
cout << "Add another (Y/N): ";
cin >> d;
if(d=='y' ^ d=='Y') goto Start;
}