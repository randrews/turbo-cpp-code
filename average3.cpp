/* NAME: Ross Andrews
   CLASS: Ms. Hackett
	  5th Period
   ASSIGN: Another average prog, this one has initials.
	   (I like parameters. They are fun.)
*/

#include <iostream.h>
#include <conio.h>

void InptGr(int n); // Declare the function

int t=0,a,c,n; // t==Total, a==Added, c==Counter, n==Number of grades
char *initials=" "; // We can use this instead of apstring.inc . The '*' makes the difference.

void main()
{
clrscr();
cout << "Type your initials: ";
cin >> initials;
cout << "Type number of grades: ";
cin >> n;
InptGr(n); // This just calls the Grade Input function
clrscr();
cout << "Initials: " << initials;
cout << endl << "Average: " << t/n;
getch();
}

void InptGr(int n)
{
for (c=0; c!=n; c++) // Simple 'For' loop.
 {
 cout << "Grade #" << c+1 << ": "; // It disps the number of the grade in the prompt
 cin >> a;
 t=a+t;
 }
}