#include<iostream.h>
#include<conio.h>
int table[2][6]={1,2,3,4,11,11,
		 11,11,11,3,1,11};

void main(){clrscr();
for(int n=0;n!=6;n++)
 cout << table[0][n] << " ";
cout << "\n";
for(n=0;n!=6;n++)
 cout << table[1][n] << " ";
getch();
}