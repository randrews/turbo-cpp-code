#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <fstream.h>
#include <stdio.h>

void main()
{
char name[12],d;
FILE *fp,*filename;
clrscr();
cout << "File name: ";
cin >> filename;
Start:
cout << "File to be added: ";
cin >> fp;
cout << "Name of tile: ";
cin >> name;
fp=fopen("temp.tmp","a");

}