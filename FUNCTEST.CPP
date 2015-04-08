#include <conio.h>
#include <stdio.h>

#include <iostream.h>
//using namespace  std ;

// define a function pointer data type 'PFN' for functions that
// take a single 'int' argument and have a return type of 'void'

typedef   void (*PFN)(int);

// create some functions whose signatures and return types match
// the PFN data type spec:

void  f( int m ) { cout << "m == " << m << endl; }
void  g( int n ) { cout << "n == " << n << endl; }

// Here's a function that has a PFN function pointer argument:

void  h( PFN pfn, int i )
{
   // Calls the function that 'pfn' points to
   (*pfn)( i );
}

int main()
{
   h( f, 123 );
   h( g, -777 );
   getch();
return 1;
}

