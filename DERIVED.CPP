#include <iostream.h>
#include <conio.h>
class base{
public: int x;
	virtual void hi();
	virtual void xd(){cout<<x<<'\n';};
	base(){x=0;};
	base(int xp){x=xp;};
};

class base2{
public: int y;
};

class derived: public base,base2{
public: //int x;
	void hi();
	virtual void xd(){cout<<x<<' '<<y<<'\n';};
	derived(){x=0;y=0;};
	derived(int xp,int yp){x=xp;y=yp;};
};

class derived2: public derived{
public: int z;
	derived2(){x=0;z=0;};
	derived2(int xp,int yp){x=xp;z=yp;};
	void hi();
};

void derived2::hi(){cout<<"Hey!\n";}

//base::base(){x=0;}
//base::base(int xp){x=xp;}
//derived::derived(int xp){x=xp;}

//void derived::xd(){cout<<x<<'\n';}
//void base::xd(){cout<<x<<'\n';}

void derived::hi(){
cout<<"Ho!\n";}

void base::hi(){
cout<<"Hi!\n";}

void main(){clrscr();
base *x=new base[5];
(x+2)->hi();x->xd();
x=new derived2(3,6);
x->hi();x->xd();

getch();
}