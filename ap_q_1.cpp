/*#include<iostream.h>
#include<conio.h>

int translate(int *info,int index){int result=0;
for(int n=0;n!=3;n++)
 {
 if(*(info+n+index)==1)result=(result<<1)+1;
  else result=(result<<1);
 }
return result;
}

const int size=9; // << GIVEN: Size of data >>;
int resultarray[3];
int translateall(int *info,int *result){int tempresult=0;
for(int n=0;n<=size;n+=3)
 {
 tempresult=0;
 for(int s=n;s!=n+3;s++)
  {
  if(*(info+n+s)==1)tempresult=(tempresult<<1)+1;
   else tempresult=(tempresult<<1);
  }
 *(result+n/3)=tempresult;
 }
return *result;
}

void main(){int b[]={1,1,1,1,0,0,0,1,1},*a=&b[0],*p=&resultarray[0];
clrscr();
cout << "One:  " << translate(a,0)
     << "\nTwo:  " << translate(a,3)
     << "\nThree: " << translate(a,6);
cout << "\n\nFour:\n";
translateall(a,p);
for(int n=0;n!=3;n++)cout << *(p+n) << "\n";
getch();
} */

#include <conio.h>
#include <dos.h>

void main(){int x=2700;
sound(x);
getch();
nosound();
}