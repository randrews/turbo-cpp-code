#include <conio.h>
#include <iostream.h>
#include <math.h>

void main()
{int a=1,q;
do
 {
 clrscr();
 cout << "Angle measure: ";cin >> a;
 cout << "Final measure: ";
 if (a<0)
  {
  a=360-abs(a%360);
  cout << a;
  }
  else cout << a%360;
 if (a%360<90) q=1;
 if (a%360<180 && a%360>90) q=2;
 if (a%360<270 && a%360>180) q=3;
 if (a%360<360 && a%360>270) q=4;
 cout << "\nQuadrant: " << q;
 cout << "\nRef angle: ";
 switch(q)
  {
  case 1:cout << a%360;break;
  case 2:cout << 180-a%360;break;
  case 3:cout << a%360-180;break;
  case 4:cout << 360-a%360;break;
  }
 getch();
 } while (a!=0);
}