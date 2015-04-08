#include <iostream.h>
#include <conio.h>
void main(){char c;int x;
clrscr();
while(c!='q')
 {
 cout << ": ";cin >> c;
 c=x;
 if (x<256) cout << x << " : " << c << "\n";
 }
}