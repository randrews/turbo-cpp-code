#include <iostream.h>
#include <conio.h>

const char doubles[26]={'s','b','c','f','r',
			'g','h','j','o','k',
			'l','a','z','m','p',
			'q','w','t','d','y',
			'i','b','e','c','u','x'};
void main(){char c;
clrscr();
while(c!=27)
 {
 c=getch();
 if(c>='a'&&c<='z')
  cout<<doubles[c-'a'];
 else if(c=='\n')cout<<'\n';
 else cout<<c;
 }
}