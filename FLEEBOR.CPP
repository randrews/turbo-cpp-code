//FLEEBOR.CPP
//A little mouse hack. Text mode.


#include "mouse.cpp"
#include <conio.h>
#include <iostream.h>

void main(){char c=' ';int x,y,b=0;
window(1,1,80,25);
textbackground(0);
textcolor(15);
clrscr();
gotoxy(1,1);cout << 'Q';
if(ifmouse())showmouse();
while(c!='q')
 {
 while(!kbhit())
  {
  readmouse();
  b=mouseb;x=(mousex>>3)+1;y=(mousey>>3)+1;
  if(mouseb!=0)
   {
   gotoxy(x,y);
   switch(b)
    {
    case 1:hidemouse();
	   cout<<c;
	   showmouse();
	   break;
    case 2:gettext(x,y,x,y,&c);break;
    }
   gotoxy(x,y);
   }
  if(b==1&&x==1)
   {
   if(y==1){c='q';break;}
   }
  }
 if(c!='q')c=getch();
 hidemouse();
 cout << c;
 showmouse();
 }
}