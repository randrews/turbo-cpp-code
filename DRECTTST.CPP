#include "graph.inc"
#define ___TESTING___
void dirtyrect(int x1,int y1,int x2,int y2)
{int t;
// Fix params
//x2++;y2++;
if(x1>x2){t=x1;x1=x2;x2=t;}
if(y1>y2){t=y1;y1=y2;y2=t;}
// wait for vertical re-trace
while (inportb(INPUT_STATUS_0)& 8);
while (!(inportb(INPUT_STATUS_0)&8));
// copy everything to video memory
//_fmemcpy(screen, off_screen, screen_size);
for(int n=0;n!=y2-y1;n++)
 {
 _fmemcpy(screen+x1+(y1+n)*320, off_screen+x1+(y1+n)*320, x2-x1);
 }
}
#ifdef ___TESTING___
void main(){
startgraph();
getch();
directcleargfx(2);
getch();
cleargfx(1);
dirtyrect(0,0,320,200);
getch();
endgraph();
}
#endif