#include <stdio.h>

char x [5] = { 0xf0, 0x0f, 0xc7, 0xc8 };

main ()
{
       void (*f)() = x;
	      f();
}