#include <conio.h>
#include <iostream.h>

void main()
{
int list[5],x=0;
clrscr();
cout << "Input 5 values with spaces: ";
cin >> list[x] >> list[x++] >> list[x++] >> list[x++] >> list[x++];
clrscr();
x=0;
cout << list[x] << endl << list[x++] << endl << list[x++] << endl <<
list[x++] << endl << list[x++];
getch();
}
