#include <iostream.h>
#include <conio.h>

class base{
public: int a;
	virtual void b();
};

void base::b(){cout<<"base class\n";}

class derived: public base{
public: int a,c;
	void b();
	void d();
};

void derived::b(){cout<<"derived class\n";}
void derived::d(){cout<<"derived::d()\n";}

void main(){
base B;
derived D;
derived *i=&D;
clrscr();
i->b();
i->d();
getch();
}