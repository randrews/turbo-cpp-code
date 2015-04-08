/* Mahjongg:
   reqd: graph.inc,
	 tile.cpp,
	 mouse.cpp,
	 etc.
   Copyleft 1999
   Zerblinitzky the Great
      also known as
   Ross Andrews
*/


#include "tile.cpp"
#include "mouse.cpp"
#include <stdlib.h>

const int basex=89,basey=35;
//const int basex=90,basey=30;
const int crnr0x=0,crnr0y=0;
const int crnr1x=4,crnr1y=3;
const int crnr2x=5,crnr2y=4;
const int crnr3x=6,crnr3y=5;
const int p0x=basex+crnr0x*10-0,p0y=basey+crnr0y*10-0;
const int p1x=basex+crnr1x*10-3,p1y=basey+crnr1y*10-3;
const int p2x=basex+crnr2x*10-6,p2y=basey+crnr2y*10-6;
const int p3x=basex+crnr3x*10-9,p3y=basey+crnr3y*10-9;
const int tiletypes=1;
const int background=1,tileback=2;
const int lvlx[4]={p0x,p1x,p2x,p3x},
	  lvly[4]={p0y,p1y,p2y,p3y},
	  crnx[4]={crnr0x,crnr1x,crnr2x,crnr3x},
	  crny[4]={crnr0y,crnr1y,crnr2y,crnr3y},
	  ldim[4]={14,6,4,2};
const int origtiles=210;


// Layers of the board:
int *l0,*l1,*l2,*l3;
//

// Number of tiles left in the game:
int tilesleft=origtiles;
//

// State of the mouse:
// 1: Tile highlighted. 0: Nothing highlighted.
int state=0;
int hx,hy;
int gx,gy;
//

// Graphics file and version number:
char gf[]="mahjongg.dat",version[]="1.0.2 b";
//

// Tile graphics array
int *graph[10];
int *cursor;
int *mask;
//

int lookup(int x,int y,int l);


int init(){
l0=new int[14*13];
l1=new int[6*7];
l2=new int[4*5];
l3=new int[2*3];
if(!(l0||l1||l2||l3))return 1;
cursor=newload("cursor.dat","rainbow");
int *tmp=newload(gf,"frame");
if(!tmp)return 2;
mask=newload(gf,"mask");
graph[0]=newload(gf,"tile0");
graph[1]=newload(gf,"tile1");
graph[2]=newload(gf,"tile2");
graph[3]=newload(gf,"tile3");
graph[4]=newload(gf,"tile4");
graph[5]=newload(gf,"tile5");
graph[6]=newload(gf,"tile6");
graph[7]=newload(gf,"tile7");
graph[8]=newload(gf,"tile8");
graph[9]=newload(gf,"tile9");
if(!ifmouse())return 3;
randomize();
for(int x=0;x!=14*13;x++)
 *(l0+x)=random(tiletypes);
for(x=0;x!=6*7;x++)
 *(l1+x)=random(tiletypes);
for(x=0;x!=4*5;x++)
 *(l2+x)=random(tiletypes);
for(x=0;x!=2*3;x++)
 *(l3+x)=random(tiletypes);
//
int zilch[40]={14,15,28,29,30,42,43,44,56,57,
	       26,27,39,40,41,53,54,55,68,69,
	       98,99,112,113,114,126,127,128,140,141,
	       110,111,123,124,125,137,138,139,152,153};
for(x=0;x!=40;x++)
 *(l0+zilch[x])=-1;
//
return 0;
}

void err(int error){
switch(error)
 {
 case 1:cout<<"Error in variable init. Probably not enough RAM.";break;
 case 2:cout<<"Error in graphics load. Probably no MAHJONGG.DAT.";break;
 case 3:cout<<"Error in mouse detect. You need a mouse to play.";break;
 }
exit(error);
}

void drawboard(){
for(int x=0;x!=13*14;x++)
 {
 if(*(l0+x)!=-1)
  {
  tile(graph[*(l0+x)],basex+crnr0x*10+(x%14)*10,
   basey+crnr0y*10+(x/14)*10,tileback);
  for(int n=1;n!=3;n++)
   tile(mask,basex+n+crnr0x*10+(x%14)*10,basey+n+crnr0y*10+(x/14)*10,-1);
  }
 }
for(x=0;x!=6*7;x++)
 {
 if(*(l1+x)!=-1)
  {
  tile(graph[*(l1+x)],basex-3+crnr1x*10+(x%6)*10,
   basey-3+crnr1y*10+(x/6)*10,tileback);
  for(int n=1;n!=3;n++)
   tile(mask,basex-3+n+crnr1x*10+(x%6)*10,basey-3+n+crnr1y*10+(x/6)*10,-1);
  }
 }
for(x=0;x!=4*5;x++)
 {
 if(*(l2+x)!=-1)
  {
  tile(graph[*(l2+x)],basex-6+crnr2x*10+(x%4)*10,
   basey-6+crnr2y*10+(x/4)*10,tileback);
  for(int n=1;n!=3;n++)
   tile(mask,basex-6+n+crnr2x*10+(x%4)*10,basey-6+n+crnr2y*10+(x/4)*10,-1);
  }
 }
for(x=0;x!=2*3;x++)
 {
 if(*(l3+x)!=-1)
  {
  tile(graph[*(l3+x)],basex-9+crnr3x*10+(x%2)*10,
   basey-9+crnr3y*10+(x/2)*10,tileback);
  for(int n=1;n!=3;n++)
   tile(mask,basex-9+n+crnr3x*10+(x%2)*10,basey-9+n+crnr3y*10+(x/2)*10,-1);
  }
 }
}

int level(int x,int y){
if(x>=p0x&&y>=p0y&&x<=p0x+140&&y<=p0x+130)
 {
 if(x>=p3x&&y>=p3y&&x<=p3x+20&&y<=p3y+30)
  {
  return 3;
  }
 if(x>=p2x&&y>=p2y&&x<=p2x+40&&y<=p2y+50)
  {
  return 2;
  }
 if(x>=p1x&&y>=p1y&&x<=p1x+60&&y<=p1y+70)
  {
  return 1;
  }
 if(x>=p0x&&y>=p0y&&x<=p0x+140&&y<=p0x+130)
  {
  return 0;
  }
 }
return -1;
}

int toplevel(int x,int y){int l;
//int t1=lookup(x,y,1),t2=lookup(x,y,2),t3=lookup(x,y,3);
int t1,t2,t3;
switch(level(x,y))
 {
 case 0:l=0;break;
 case 1:t1=lookup(x,y,1);
	if(t1==-1)l=0;
	if(t1>=0)l=1;break;
 case 2:t1=lookup(x,y,1);
	t2=lookup(x,y,2);
	if(t2==-1)l=1;
	if(t1==-1&&t2==-1)l=0;
	if(t2>=0)l=2;break;
 case 3:t1=lookup(x,y,1);
	t2=lookup(x,y,2);
	t3=lookup(x,y,3);
	if(t3==-1)l=2;
	if(t2==-1&&t3==-1)l=1;
	if(t1==-1&&t2==-1&&t3==-1)l=0;
	if(t3>=0)l=3;break;
 }
/*l=0;
for(int n=0;n!=3;n++)
 if(lookup(x,y,n)>-1)l++;*/
return l;
}

/*int ytilec(int x,int y){
int l=level(x,y);
/*for(int n=0;n!=3;n++)
 if(lookup(x,y,n)>-1)l++;/
//x-=3*l;x-=x%10;x+=10;
//y-=3*l;y-=y%10;y+=10;

int t=(y-lvly[l])/10+crny[l];
return t;
}

int xtilec(int x,int y){
int l=level(x,y);
/*for(int n=0;n!=3;n++)
 if(lookup(x,y,n)>-1)l++;/
x-=3*l;x-=x%10;x+=10;
y-=3*l;y-=y%10;y+=10;
int t=(x-lvlx[l])/10+crnx[l];
return t;
}*/

int ytilec(int x,int y,int t){
//int t=level(x,y);
y-=(y-lvly[t])%10;//+basey;
x-=(x-lvlx[t])%10;//+basex;
int l=(y-lvly[t])/10+crny[t];
return l;
}

int xtilec(int x,int y,int t){
//int t=level(x,y);
y-=(y-lvly[t])%10;//+basey;
x-=(x-lvlx[t])%10;//+basex;
int l=(x-lvlx[t])/10+crnx[t];
return l;
}


int* lyrpnt(int l){int *lp;
switch(l)
 {
 case 0:lp=l0;break;
 case 1:lp=l1;break;
 case 2:lp=l2;break;
 case 3:lp=l3;break;
 }
return lp;
}

int lookup(int x,int y,int l){
int *lp=lyrpnt(l),ld=ldim[l],tx,ty;
tx=xtilec(x,y,l)-crnx[l];ty=ytilec(x,y,l)-crny[l];
if(l>level(x,y))return -1;
//if(l<=level(x,y)){x+=l*2+2;y+=l*2+2;}
return *(lp+tx+ty*ld);
}

int toptile(int x,int y){int t;
/*int l=toplevel(x,y),*lp=lyrpnt(l),ld=ldim[l],
    tx=xtilec(x,y)-crnx[l],ty=ytilec(x,y)-crny[l];
t=*(lp+tx+ty*ld);*/
int l=toplevel(x,y);t=lookup(x,y,l);
return t;
}

int nbrleft(int x,int y){int t;
int l=toplevel(x,y);
if(xtilec(x,y,l)>crnx[l])
 {
 t=lookup(x-10,y,l);
 }
else t=-1;
return t;
}

int nbrright(int x,int y){int t;
int l=toplevel(x,y);
if(xtilec(x,y,l)<crnx[l]+ldim[l]-1)
 {
 t=lookup(x+10,y,l);
 }
else t=-1;
return t;
}

int tilefree(int x,int y){int a;
if(nbrleft(x,y)==-1||nbrright(x,y)==-1)a=1;
 else a=0;
return a;
}

void testfuncs(){
if(mousex>=basex&&mousex<=basex+140
   &&mousey>=basey&&mousey<=basey+130)
 {
 //
 //if(mouseb==1)
 cout<<"X: "  <<xtilec(mousex,mousey,toplevel(mousex,mousey))
     <<"\nY: "<<ytilec(mousex,mousey,toplevel(mousex,mousey))
     <<"\nL: "<<toplevel(mousex,mousey)
     <<"\nN: "<<nbrleft(mousex,mousey)
     <<' '<<nbrright(mousex,mousey)
     <<"\nF: "<<tilefree(mousex,mousey)
     <<"\n\n0: "<<lookup(mousex,mousey,0)
     <<"\n1: "<<lookup(mousex,mousey,1)
     <<"\n2: "<<lookup(mousex,mousey,2)
     <<"\n3: "<<lookup(mousex,mousey,3);
 if(state==1)
 cout<<"\n\nG: "<<toptile(gx,gy)
     <<"\nMo: "<<lookup(mousex,mousey,toplevel(mousex,mousey))
     <<"\nHx: "<<hx
     <<"\tHy: "<<hy
     <<"\nMx: "<<mousex
     <<"\tMy: "<<mousey
     <<"\nMtx: "<<xtilec(mousex,mousey,toplevel(mousex,mousey))
     <<"\tMty: "<<ytilec(mousex,mousey,toplevel(mousex,mousey))
     <<"\nGtx: "<<xtilec(gx,gy,toplevel(gx,gy))
     <<"\tGty: "<<ytilec(gx,gy,toplevel(gx,gy));
 getch();
 clrscr();
 display();
 //
 }
}

void highlight(int c){
int l=toplevel(hx,hy),
//t=toplevel(mousex,mousey),
thx,thy;
// 1: Make highlight at mouse.
// 2: Maintain highlight already made at (hx,hy)
if(c==2)
 {
 thx=lvlx[l]+10*(xtilec(hx,hy,toplevel(hx,hy))-crnx[l]);
 thy=lvly[l]+10*(ytilec(hx,hy,toplevel(hx,hy))-crny[l]);
 rectangle(thx,thy,thx+9,thy+9,13,OPEN);
 }
if(c==1)
 {
 //l=level(mousex,mousey);
 //mousex+=2*t;mousey+=2*t;
 //hx=lvlx[t]+10*(xtilec(mousex,mousey)-crnx[t]);
 //hy=lvly[t]+10*(ytilec(mousex,mousey)-crny[t]);
 //hx=(mousex-lvlx[l])/10*10+basex;hy=(mousey-lvly[l])/10*10+basey;
 hx=mousex;hy=mousey;
 highlight(2);display();
 }
}

void zorchtile(){
int l=toplevel(gx,gy),*lp=lyrpnt(l),ld=ldim[l],
    tx=xtilec(gx,gy,toplevel(gx,gy))-crnx[l],
    ty=ytilec(gx,gy,toplevel(gx,gy))-crny[l];
*(lp+tx+ty*ld)=-1;
l=toplevel(mousex,mousey);lp=lyrpnt(l);ld=ldim[l];
    tx=xtilec(mousex,mousey,toplevel(mousex,mousey))-crnx[l];
    ty=ytilec(mousex,mousey,toplevel(mousex,mousey))-crny[l];
*(lp+tx+ty*ld)=-1;
cleargfx(background);drawboard();display();
state=0;tilesleft--;
}

void cogitate(){
/*if(mouseb==1)
 {

 }
if(mouseb==2)state=0;*/
switch(mouseb)
 {
 case 1:if(state==0&&tilefree(mousex,mousey)==1
	   &&toptile(mousex,mousey)!=-1)
	 {
	 highlight(1);state=1;
	 gx=mousex,gy=mousey;
	 }
	if(state==1&&tilefree(mousex,mousey)==1
	   &&(xtilec(mousex,mousey,toplevel(mousex,mousey))!=
	      xtilec(gx,gy,toplevel(gx,gy))
	   ||ytilec(mousex,mousey,toplevel(mousex,mousey))!=
	     ytilec(gx,gy,toplevel(gx,gy)))
	   &&(toptile(mousex,mousey)==toptile(gx,gy)))
	 {
	 zorchtile();
	 //zorchtile(mousex,mousey);
	 //zorchtile(gx,gy);
	 }
	break;
 case 2:state=0;break;
 case 3:testfuncs();break;
 }
}

void loop(){int ox=0,oy=0,ob;char c;
while(c!='q'&&tilesleft>0)
 {
 while(!kbhit())
  {
  readmouse();mousex/=2;
  if(ox!=mousex||oy!=mousey)
   {
   ox=mousex,oy=mousey;
   drawboard();
   if((toptile(gx,gy)<0||toptile(gx,gy)>9)|| //Error cntrl
      (tilefree(gx,gy)!=1))state=0;
   if(state==1)highlight(2);
   display();
   directsafetile(cursor,mousex,mousey,-1);
   }
  if(mouseb!=ob)//testfuncs();
   {
   ob=mouseb;
   cogitate();
   }
  }
 c=getch();
 }
}

void main(){int error=init();
if(error!=0)err(error);
/*//test
startgraph();
tile(cursor,40,50,-1);
cleargfx(1);
for(int x=0;x!=10;x++)
 tile(graph[x],50+10*x,50,-1);
display();
getch();
//*/

/**(l0+33)=-1;
*(l3+2)=-1;
*(l2+9)=-1;*/

//drawboard();display();
//getch();
clrscr();
cout<<"Mahjongg v. "
    <<version
    <<"\nBy Ross Andrews.";
getch();
startgraph();cleargfx(background);
loop();
endgraph();
cout<<"Thanks for playing!";exit(0);
}