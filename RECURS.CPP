#include <iostream.h>
#include <conio.h>
int fact(int n);
int r=1;
void main()
{int n;
clrscr();
cout << "Number: ";cin >> n;
//fact(n);
cout << "Factorial: " << fact(n);
getch();
}

int fact(int n){//int r=1;
if (n!=1){ n*=fact(n-1);}//n--;}
return n;
}
/*int fact(int x)
{
if (x!=1)// return 1;
{x*=fact(x-1); return x;}
} */
