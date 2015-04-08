// SCRIBBLE.CPP
// Jiminny Jillickers, Radioactive Man! A real drawing program! Groovy!

#include "tile.cpp"
#include "mouse.cpp"
#define gf "scribble.dat"

int tools[7][100];
int cursor[100];

void graphinit();
void drawtools();
void usetool();
int findrad();

int ox=-1,oy,ob=0,sx,sy,color=0,tool=0,use=0;

void main(){char c;
graphinit();
while(c!=27)
 {
 readmouse();mousex/=2;
 if(mousex!=ox||mousey!=oy)
  {
  display();
  if(use==1)
   {
   switch(tool)
    {
    case 2:directline(sx,sy,mousex,mousey,color);break;
    case 3:directrectangle(sx,sy,mousex,mousey,color,OPEN);break;
    case 4:directrectangle(sx,sy,mousex,mousey,color,CLOSED);break;
    case 5:directcircle(sx,sy,findrad(),color);break;
    case 6:directellipse(sx,sy,abs(sx-mousex),abs(sy-mousey),color);break;
    }
   }
  directtile(&cursor[0],mousex,mousey,-1);
  ox=mousex;oy=mousey;
  }
 if((mouseb!=ob&&tool>1)||
    (mouseb!=0&&(tool<=1)||(mousex<=15&&mousey<=15)))
  {
  switch(mouseb)
   {
   case 1:if(mousey<=15&&mousex<=15)
	   {
	   color=mousex+16*mousey;
	   drawtools();
	   }
	  if(mousey<=12&&mousey>=3&&mousex>=20&&mousex<=90)
	   {
	   tool=(mousex-20)/10;
	   drawtools();
	   }
	  if(mousey>15)
	   usetool();
	  if(tool<=1)display();
	  break;
   case 2:if(use==0){color=getpixel(mousex,mousey);drawtools();}
	  if(use==1){use=0;drawtools();}break;
   }
  ob=mouseb;
  }
 if(kbhit()){c=getch();if(c=='r')drawtools();}
 }
}

void usetool(){int t,tsx,tsy,tmx,tmy;
switch(tool)
 {
 case 1:pixel(mousex,mousey+1,color);
	pixel(mousex,mousey-1,color);
	pixel(mousex-1,mousey,color);
	pixel(mousex-1,mousey-1,color);
	pixel(mousex-1,mousey+1,color);
	pixel(mousex+1,mousey,color);
	pixel(mousex+1,mousey-1,color);
	pixel(mousex+1,mousey+1,color);
 case 0:pixel(mousex,mousey,color);break;
 case 2:if(use==0){sx=mousex;sy=mousey;use=1;}
	else if(use==1){line(sx,sy,mousex,mousey,color);use=0;}
	break;
 case 3:if(use==0){sx=mousex;sy=mousey;use=1;}
	else if(use==1){rectangle(sx,sy,mousex,mousey,color,OPEN);use=0;}
	break;
 case 4:if(use==0){sx=mousex;sy=mousey;use=1;}
	else if(use==1){rectangle(sx,sy,mousex,mousey,color,CLOSED);use=0;}
	break;
 case 5:if(use==0){sx=mousex;sy=mousey;use=1;}
	else if(use==1){circle(sx,sy,findrad(),color);use=0;}
	break;
 case 6:if(use==0){sx=mousex;sy=mousey;use=1;}
	else if(use==1){ellipse(sx,sy,abs(sx-mousex),abs(sy-mousey),color);
			use=0;}
	break;
 }
}

int findrad(){int tsx,tsy,tmx,tmy;
if(mousex<sx){tmx=sx;tsx=mousex;}
 else{tmx=mousex;tsx=sx;}
if(mousey<sy){tmy=sy;tsy=mousey;}
 else{tmy=mousey;tsy=sy;}
return sqrt(pow(tmy-tsy,2)+pow(tmx-tsx,2));
}

void graphinit(){
startgraph();
int *gp=loadtile(gf,"cursor");
for(int n=0;n!=d*d;n++)
 cursor[n]=*(gp+n);
gp=loadtile(gf,"freehand");
for(n=0;n!=d*d;n++)
 tools[0][n]=*(gp+n);
gp=loadtile(gf,"widehand");
for(n=0;n!=d*d;n++)
 tools[1][n]=*(gp+n);
gp=loadtile(gf,"line");
for(n=0;n!=d*d;n++)
 tools[2][n]=*(gp+n);
gp=loadtile(gf,"rectangle");
for(n=0;n!=d*d;n++)
 tools[3][n]=*(gp+n);
gp=loadtile(gf,"fillrect");
for(n=0;n!=d*d;n++)
 tools[4][n]=*(gp+n);
gp=loadtile(gf,"circle");
for(n=0;n!=d*d;n++)
 tools[5][n]=*(gp+n);
gp=loadtile(gf,"ellipse");
for(n=0;n!=d*d;n++)
 tools[6][n]=*(gp+n);
drawtools();
}

void drawtools(){
rectangle(0,0,319,15,18,CLOSED);
for(int n=0;n!=16;n++)
 for(int N=0;N!=16;N++)
  pixel(n,N,n+16*N);
for(n=0;n!=7;n++)
 tile(&tools[n][0],20+n*10,3,-1);
tile(&tools[tool][0],20+tool*10,3,4);
blank(305,3,color);
display();
}