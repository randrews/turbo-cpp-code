#include <iostream.h>
#include <conio.h>

void main(){int x,v[16];
clrscr();
cout<<"Num: ";cin>>x;
if(x<0){v[15]=1;x*=-1;}else v[15]=0;
for(int n=0;n!=15;n++)
 {
 if((x>>n)%2==1)v[n]=1;
  else v[n]=0;
 }
cout<<"L: ";
for(n=0;n!=8;n++)
 cout<<v[n]<<' ';
cout<<'\n'<<"H: ";
for(;n!=16;n++)
 cout<<v[n]<<' ';
getch();
}