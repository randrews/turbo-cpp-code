//#include "mouse.cpp"
#include "bgraph.inc"
#include <conio.h>
#include <iostream.h>

void pixmap2(int x,int y,char *pix){
int dx=*pix++ -'0',dy=*pix++-'0';
for(int n=0;n!=dy;n++)
 //dpixel(x+n%d,y+n/d,*(pix+n));
 _fmemcpy(screen+x+(y+n)*320,pix+n*dx,dx);
}

void main(){char *pix=
"95rrrwwwbbbrrrwwwbbbrrrwwwbbbrrrwwwbbbrrrwwwbbbrrrwwwbbbrrrwwwbbbrrrwwwbbbrrrwwwbbb";
startgraph();
palette('r',63,0,0);
palette('w',63,63,63);
palette('b',0,0,63);
//dclrgraph('r');
pixmap2(50,50,pix);
getch();
endgraph();
}




