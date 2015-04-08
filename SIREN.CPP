#include <dos.h>
#include <conio.h>

void main()
{int x=0;
while(!kbhit())
 {
 sound(x);
 delay(5);
 x++;if (x>400) x=1;
 }
nosound();
}