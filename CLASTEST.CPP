#include <conio.h>
#include <iostream.h>
/*int x=5; // Test mult declarations
void printx(){int x=3;
cout<<::x<<'\n';
}
void main(){
clrscr();
printx();
getch();
cout<<x;
getch();
}*/
class foo{
public: int a,b,c;

	friend int operator +(foo x,foo y);
	foo operator =(int v){
	a=v,b=v,c=v;
	return *this;
	}
};
void bar(){
foo r;r.a=1,r.b=2,r.c=3;
//cout<<r.sum(4);
}

int operator +(foo x,foo y){
return x.a+y.a;
}
void main(){
clrscr();
//bar();
foo t,z;
t=2;z=2;
cout<<t.a<<t.b<<t.c;
getch();
}
/*void baz(int x){
cout<<(char)x;}
void baz(char x){
cout<<(int)x;}
void main(){int a=5;char b=5;
clrscr();
baz(a);
getch();}*/