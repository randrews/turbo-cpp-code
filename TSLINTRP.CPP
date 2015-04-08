/*
  TSL (Tiny Scripting Language) Interpreter.
  By Ross Andrews
*/

#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <assert.h>

void interp(char cmnd[10]);

int x=0,y=0,z=0,t=0,temp=0,kill=0,line=0;
ifstream filein;

void main()
{
char c,cmnd[10],tslfile[13];
clrscr();
cout << "Name of .TSL file to execute: ";
gets(tslfile);
//Execution of TSL code begins here
clrscr();
filein.open(tslfile);
assert(!filein.fail());
filein.get(c);
while(!filein.eof())
 {
 if (c==':')
  {
  filein >> cmnd;
  interp(cmnd);
  if (kill>0) goto End;
  line++;
  //cout << cmnd << endl;getch; //Uncomment to see all commands
  }
 filein.get(c);
 }
//getch();
End:
if (kill==1)
 {
 cout << "::ERROR- LINE " << line << "::" ;
 getch();
 }
if (kill==2)
 {
 cout << "::BREAK- LINE " << line << "::";
 getch();
 }
}

void interp(char cmnd[10])
{
kill=1;
if (strcmp(cmnd,"break")==0)      kill=2;
if (strcmp(cmnd,"clrscr")==0)     {clrscr();kill=0;}
if (strcmp(cmnd,"pause")==0)      {getch();kill=0;}
if (strcmp(cmnd,"tab")==0)        {cout << "\t";kill=0;}
if (strcmp(cmnd,"space")==0)      {cout << " ";kill=0;}
if (strcmp(cmnd,"endl")==0)       {cout << endl;kill=0;}
if (strcmp(cmnd,"outx")==0)       {cout << x;kill=0;}
if (strcmp(cmnd,"outy")==0)       {cout << y;kill=0;}
if (strcmp(cmnd,"outz")==0)       {cout << z;kill=0;}
if (strcmp(cmnd,"outt")==0)       {cout << t;kill=0;}
//Now we have the register manip commands...
if (strcmp(cmnd,"enter")==0)      {t=z;z=y;y=x;filein >> x;kill=0;}
if (strcmp(cmnd,"stox")==0)       {filein >> x;kill=0;}
if (strcmp(cmnd,"stoy")==0)       {filein >> y;kill=0;}
if (strcmp(cmnd,"stoz")==0)       {filein >> z;kill=0;}
if (strcmp(cmnd,"stot")==0)       {filein >> t;kill=0;}
if (strcmp(cmnd,"rollup")==0)     {temp=t;t=z;z=y;y=x;x=temp;kill=0;}
if (strcmp(cmnd,"rolldn")==0)     {temp=x;x=y;y=z;z=t;t=temp;kill=0;}
if (strcmp(cmnd,"swapxy")==0)     {temp=x;x=y;y=temp;kill=0}
if (strcmp(cmnd,"swapxz")==0)     {temp=x;x=z;z=temp;kill=0}
if (strcmp(cmnd,"swapxt")==0)     {temp=x;x=t;t=temp;kill=0}
if (strcmp(cmnd,"swapyz")==0)     {temp=y;y=z;z=temp;kill=0}
if (strcmp(cmnd,"swapyt")==0)     {temp=y;y=t;t=temp;kill=0}
if (strcmp(cmnd,"swapzt")==0)     {temp=z;z=t;t=temp;kill=0}
}