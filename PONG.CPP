#include "graph.inc"
#include "mouse.cpp"
#include <iostream.h>
#include <stdlib.h>
char version[]="0.0a";
int mode=1;
int step=1;

void bounce();
void aimove();
void aibounce();

class aipaddle{
public: int length,ty,oty;
	aipaddle(int pl,int py);
	void draw();
	void move();
}

aipaddle::aipaddle(int pl,int py){
length=pl;ty=py;oty=0;
}

void aipaddle::draw(){int n;
for(n=oty;n!=oty+length;n++)
 pixel(319,n,0);
for(n=ty;n!=ty+length;n++)
 pixel(319,n,15);
oty=ty;
}

void aipaddle::move(){
aimove();
}

class paddle{
public: int length,ty,oty;
	paddle(int pl,int py);
	void draw();
	void move();
}

paddle::paddle(int pl,int py){
length=pl;ty=py;oty=0;
}

void paddle::draw(){int n;
for(n=oty;n!=oty+length;n++)
 pixel(0,n,0);
for(n=ty;n!=ty+length;n++)
 pixel(0,n,15);
oty=ty;
}

void paddle::move(){
ty=mousey;
if(ty>179)ty=179;
}

class ball{
public: int x,y;
	int dx,dy;
	int ox,oy;
	ball(int px,int py,int pdx,int pdy);
	void move();
	void draw();
	friend class paddle;
}

ball::ball(int px,int py,int pdx,int pdy){
x=px;y=py;dx=pdx;dy=pdy;
}

void ball::move(){
ox=x;oy=y;
x+=dx;y+=dy;
if(x<1)bounce();
if(x>318)aibounce();
if(y<1||y>198)dy*=-1;
}

void ball::draw(){
pixel(x,y,15);
pixel(ox,oy,0);
}

ball b=ball(50,50,1,1);
paddle p=paddle(20,50);
aipaddle c=aipaddle(20,140);

void bounce(){
if(b.y>p.ty&&b.y<p.ty+p.length){b.dx*=-1;mode=1;}
else
 {
 getch();
 b.x=random(320);
 b.y=random(200);
 }
}

void aimove(){
if(b.y>c.ty+c.length-3)c.ty+=step;
if(b.y<c.ty+3)c.ty-=step;
if(c.ty<0)c.ty=0;if(c.ty+c.length>199)c.ty=199-c.length;
c.draw();
}

void aibounce(){
if(b.y>c.ty&&b.y<c.ty+c.length){b.dx*=-1;mode=0;}
else
 {
 getch();
 b.x=random(320);
 b.y=random(200);
 }
}

void main(){char c;
clrscr();
startgraph();
while(c!=27)
 {
 b.move();
 b.draw();
 p.draw();
 p.move();
 if(mode==1)aimove();
 display();
 if(kbhit())c=getch();
 //if(c=='t')cout<<mousey;
 readmouse();
 }
}
