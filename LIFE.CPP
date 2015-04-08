#include "tile.cpp"
int glider[d*d];
void drawscrn();
void generation();
void main(){char c;
StartGfx();
drawscrn();
while(c!='q')
 {
 while(!kbhit())
  generation();
 c=getch();
 }
}

void drawscrn(){
ClearGfx(0);
for (int n=0;n!=d*d;n++)
 glider[n]=*(loadtile("life.dat","glider")+n);
tile(glider,150,150,0);
Line(100,100,125,125,15);
Pixel(50,50,15);Pixel(50,51,15);Pixel(50,52,15);
}

void generation(){int x,y,s,p;
for (int long n=0;n!=64000;n++)
 {
 x=n%320;y=n/320;p=GetPixel(x,y);
 s=GetPixel(x+1,y+1)+GetPixel(x+1,y)+GetPixel(x+1,y-1)+
   GetPixel(x,y+1)+GetPixel(x,y-1)+
   GetPixel(x-1,y+1)+GetPixel(x-1,y)+GetPixel(x-1,y-1);
 Pixel(x,y,0);
 if(p==0 && s==45) Pixel(x,y,15);
 if(p==15 && s==45) Pixel(x,y,15);
 if(p==15 && s==30) Pixel(x,y,15);
 }
}

