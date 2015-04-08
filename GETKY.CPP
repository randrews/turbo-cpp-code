#include <conio.h>
#include <iostream.h>

void main()
{
int c;
Start:
c=getch();
if (c==113)
goto End;
if (c>0)
cout << c << endl;
goto Start;
End:
}