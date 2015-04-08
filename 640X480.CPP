#include <mem.h>
#include <dos.h>
#include <iostream.h>
#include <conio.h>

unsigned char *screen=(unsigned char*)MK_FP(0xA000,0);

void pixel(int x,int y,int color,int plane){
_BH=0;
asm mov cx,x
asm mov dx,y
_AL=color;
asm mov ah,0x0c
asm int 0x10//*/
/*outportb(0x3c4, 0x02);
outportb(0x3c5,1 << (x & 3));
*(screen+80*y+x/4+plane)=color;//*/

plane;
}

#define CRTC_ADDR 0x3d4
void setvis(int visStart){
outport(0x3d4, 0x0C);		/* set high byte */
outport(0x3d5, visStart >> 8);
outport(0x3d4, 0x0D);		/* set low byte */
outport(0x3d5, visStart & 0xff);
}

void main(){
asm{
 mov ax,0x4f02
// mov al,0x13
 mov bx,0x101
 int 0x10
 }
/*outport(0x3c4, 0x0604);
outport(0x3d4, 0xE317);
outport(0x3d4, 0x0014);
outport(0x3c4, 0x0F02);
memset(screen+1, 0, 0xffff); // Start and Clear*/
for(int x=10;x!=266;x++)
 for(int y=10;y!=20;y++)
  pixel(x,y,x-10,3); // Mr. Pixel
/*setvis(0);
getch();
setvis(1);
getch();
setvis(2);
getch();
setvis(3);*/
getch();
asm{
 mov ax,0x3
 int 0x10
 }
}


//int j=*(screen+0+0*320);

/*asm mov ax,0x13
asm int 0x10
//outport(0x3c4, 0x0604);
//outport(0x3d4, 0xE317);
//outport(0x3d4, 0x0014);
cout<<"Hi!";
pixel(10,10,15);
getch();
asm mov ax,0x3
asm int 0x10*/