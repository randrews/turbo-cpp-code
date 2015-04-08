/* NAME: Ross Andrews
   CLASS: Ms. Hackett
	  5th Period
   ASSIGN: Another average prog, this one has initials.
	   (Send in the subroutines!!!)
*/

#include <iostream.h>
#include <conio.h>

int InptGr(int n);

int Average(int t, int n);

int t=0,a,c,n;
char *initials=" ";
void main()
{
clrscr();
cout << "Type your initials: ";
cin >> initials;
cout << "Type number of grades: ";
cin >> n;
InptGr(n);
clrscr();
cout << "Initials: " << initials;
cout << endl << "Average: " << Average(t,n);
getch();
}

int InptGr(int n)
{
for (c=0; c!=n; c++)
 {
 cout << "Grade #" << c+1 << ": ";
 cin >> a;
 t=a+t;
 }
return t;
}

int Average(int t, int n)
{
return t/n;
}



