/* NAME:       Ross Andrews
   CLASS:      Fifth Period
	       Computer Sci. 1 Honors
	       Ms. Hackett
   ASSIGNMENT: Averaging program
	       (I was bored.)
*/

#include <iostream.h>
#include <conio.h>

int d=0,r=0;     // d=Denominator, r=Remaining
double a=0,t=0;  // a={Added,Average} t=Total

void InputF();   // Must remember to declare the functions!
void CalcF();
void OutptF();

void main()
{ // This is the main sequence. OOP, remember?
t=0;      // This is sorta neccessary if you're gonna run it twice...
InputF(); // Input Function
CalcF();  // Calculation Function
OutptF(); // Output Function
}

void InputF()
{ // This inputs the variables.
clrscr();
cout << "Enter the number of numbers to be averaged:";
cin >> d; // It'll do more than five! Or less, or five. Doesn't matter.
clrscr();
r=d;
while (r>0) //Here's the loop.
 {
 cout << "Number " << d-r+1 << ": "; // The prompt shows which number it is.
 cin >> a;
 t=a+t;
 r--;
 }
}

void CalcF()
{ // This calcs the average (a=t/d)
a=t/d;
}

void OutptF()
{ // This outputs the average and the total.
cout << "The average is: " << a << endl << "And the total is: " << t;
if (d>0)
 { // It'll stop if d==0.
 getch();
 main();
 }
}