#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <string.h>
#include "apstring.inc"
#include <assert.h>

char tile[100];
char tofile[12],fromfile[12];

ofstream fileout;
ifstream filein;

void loadfile(char fn[12]);
void savefile(char filename[12],char name[12]);
void xferfile(char fromfile[12],char tofile[12]);

void main()
{
char c;
Start:
clrscr();
cout << "What file will you be using: ";
cin >> tofile;
fileout.open(tofile);
fileout.close();
fileout.open("dummy.dat");
fileout.close();
cout << "Add what tile: ";
cin >> fromfile;
xferfile(fromfile,tofile);
cout << "Add another (Y/N): ";
cin >> c;
if (c=='y' ^ c=='Y') goto Start;
}

void loadfile(char fn[12])
{
filein.open(fn);
assert(! filein.fail());
for (int n=0;n!=100;n++)
filein >> tile[n];
filein.close();
}

void savefile(char filename[12],char name[12])
{
apstring dummy;
filein.open(filename);
fileout.open("dummy.dat");
filein >> dummy;
while(! filein.eof())
 {
 fileout << dummy << " ";
 filein >> dummy;
 }
fileout.close();
filein.close();
fileout.open(filename);
fileout << name << " ";
for(int n=0;n!=100;n++)
fileout << tile[n] << " ";
}



/*void savefile(char filename[12],char name[12])
{
apstring dummy;
fileout.open(filename);
assert(! fileout.fail());
fileout << "end";
fileout.close();
filein.open(filename);
assert(! filein.fail());
fileout.open("temp.zap");
filein >> dummy;
while (dummy != "end")
 {
 fileout << dummy << " ";
 filein >> dummy;
 }
fileout << "end";
filein.close();
fileout.close();
fileout.open(filename);
assert(! fileout.fail());
filein.open("temp.zap");
filein >> dummy;
while (dummy != "end")
 {
 fileout << dummy << " ";
 filein >> dummy;
 }
fileout << name << " ";
for(int n=0;n!=100;n++)
fileout << tile[n] << " ";
fileout << "end";
fileout.close();
filein.close();
}*/

void xferfile(char fromfile[12],char tofile[12])
{
char name[12];
loadfile(fromfile);
cout << "Name of tile (max 12 chars): ";
cin >> name;
savefile(tofile,name);
}