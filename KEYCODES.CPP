#include <conio.h>
#include <iostream.h>

void main(){char c;
while(c!=27)
 {
 c=getch();cout<<c<<' '<<(int)c<<'\n';
 }
getch();
}