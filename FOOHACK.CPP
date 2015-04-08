// FOOHACK.CPP
// Another litle mouse hack. Mode 0x13.

#include "tile3.cpp"
#include "mouse.cpp"
#include <conio.h>
#include <iostream.h>

void main(){char c;unsigned int d=0,ox,oy,od;int w=0;
startgraph();
//showmouse();
for(int n=0;n!=256;n++)
 pixel(n,0,n);
display();
while(c!='q')
 {
 readmouse();mousex=(mousex>>1);
 //	if(mouseb==1)cout << (mousex>>1) << "\n" << mousey << "\n";
 pixel(ox,oy,od);
 od=getpixel(mousex,mousey);
 pixel(mousex,mousey,15);
 ox=mousex;oy=mousey;
 display();
 if(mouseb==2)d=od;//d=getpixel(mousex,mousey);
 if(mouseb==1&&mousey!=0)
  {
  if(w==1)
   {
   pixel(mousex-1,mousey-1,d);
   pixel(mousex+1,mousey-1,d);
   pixel(mousex-1,mousey+1,d);
   pixel(mousex+1,mousey+1,d);
   pixel(mousex,mousey-1,d);
   pixel(mousex,mousey+1,d);
   pixel(mousex-1,mousey,d);
   pixel(mousex+1,mousey,d);
   //pixel(mousex,mousey,d);
   od=d;
   }
  else{od=d;}//pixel(mousex,mousey,d);}
  }
 if(mouseb==3)
  {
  for(int N=1;N!=199;N++)
   for(n=0;n!=319;n++)
    pixel(n,N,d);
  display();mouseb=0;
  }
 switch(c)
  {
  case 'w':if(w==0)w=1;else w=0;break;
  case 'r':for(n=0;n!=256;n++)
	    pixel(n,0,n);
	   display();mouseb=0;break;
  }
 if(mouseb!=0){display();blank(310,0,d);}
 if(kbhit())c=getch();else c='~';
 }
}

