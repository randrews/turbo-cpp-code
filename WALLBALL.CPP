#include "mouse.cpp"
#include "graph.inc"
#include <stdlib.h>

class paddle{
public:
paddle();
~paddle();
void update();
private:
void chkball();
void fall();
int bx,by,dx,dy,px,py,ox,oy,omx;
int ballsleft,clr,lngth;
};

paddle::paddle(){
ballsleft=5;clr=15;lngth=30;omx=-1;
py=195;
bx=random(320);
by=random(100);
ox=bx,oy=by;
dx=(random(2)==0?-1:1);
dy=(random(2)==0?-1:1);
px=160-lngth/2;
}

paddle::~paddle(){}

void paddle::update(){
chkball();
bx+=dx;by+=dy;
pixel(ox,oy,0);
pixel(bx,by,clr);
ox=bx,oy=by;
readmouse();mousex/=2;
if(mousex+lngth>319)mousex=319-lngth;
if(omx!=mousex)
 {
 px=mousex;
 omx=px;
 for(int n=0;n!=320;n++)
  pixel(n,py,0);
 for(n=px;n!=px+lngth;n++)
  pixel(n,py,clr);
 }
}

void paddle::chkball(){
if(bx==1||bx==318)dx*=-1;
if(by==1)dy*=-1;
if(by==py-1&&(bx>=px&&bx<=px+lngth))dy*=-1;
if(by==199)fall();
}

void paddle::fall(){
ballsleft--;
if(ballsleft==0)exit(0);
bx=random(320);
by=random(100);
dx=(random(2)==0?-1:1);
dy=(random(2)==0?-1:1);
readmouse();
while(mouseb==0)readmouse();
while(mouseb!=0)readmouse();
}

void main(){
randomize();
startgraph();
paddle p=paddle();
while(!kbhit())
 {
 p.update();
 display();
 }
endgraph();
}