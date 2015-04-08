#include <iostream.h>
#include <conio.h>

void main()
{
int list[5],p;
clrscr();
for (p=5;p!=0;p--)
{
cout << "Item #" << 5-p+1 << ": ";
cin >> list[5-p];
}
clrscr();
for (p=0;p!=5;p++)
cout << "Item " << p+1 << " is: " << list[p] << endl;
getch();
}