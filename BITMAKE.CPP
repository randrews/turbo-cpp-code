#include <iostream.h>
#include <conio.h>
#include "tile.cpp"
#define gf "font.dat"
#define filename "font.bit"
#define tile "1"
void main(){int *lp,*rp=new int[5],t,r=0,*ga=new int[5],n;
lp=newload(gf,tile);
clrscr();
for(r=0;r!=5;r++)
 {
 for(n=0;n!=5;n++)
  *(rp+n)=*(lp+n+5*r);
 t=0;
 for(n=0;n!=d;n++)
  {
  t=t<<1;t+=*(rp+n);
  }
 *(ga+r)=t;
 }
for(n=0;n!=d;n++)
 cout<<*(ga+n)<<' ';
ofstream fileout;
ifstream filein;
char f,ftile[12];int dummy;
filein.open(filename);
if (!filein.fail())
 {
 fileout.open("temp.dat");
 filein.get(f);
 while(!filein.eof())
  {
  if (f==':')
   {
   filein >> ftile;
   if (strcmp(ftile,tile)==0)
    {
    for (int n=0;n!=5;n++)
     filein >> dummy;
    } else fileout << ": " << ftile;
   } else fileout.put(f);
  filein.get(f);
  }
 filein.close();fileout.close();
 filein.open("temp.dat");
 fileout.open(filename);
 filein.get(f);
 while(!filein.eof())
  {
  fileout.put(f);filein.get(f);
  }
 filein.close();
 } else fileout.open(filename);
fileout << " : " << tile << "\n";
for (n=0;n!=5;n++)
 fileout << *(ga+n) << " ";
fileout << "\n";
fileout.close();
getch();
}