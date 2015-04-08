#ifndef MOUSE_CPP
#define MOUSE_CPP
unsigned int mousex,mousey,mouseb;

char ifmouse();
void showmouse();
void hidemouse();
void readmouse();
void setmousexy(unsigned int x,unsigned int y);
void setminmaxx(unsigned int min,unsigned int max);
void setminmaxy(unsigned int min,unsigned int max);

char ifmouse(){
unsigned int result;
asm mov ax,0
asm int 0x33
asm mov result,ax
return result;
}

void showmouse(){
asm mov ax,0x1
asm int 0x33
}

void hidemouse(){
asm mov ax,0x2
asm int 0x33
}

void readmouse(){
asm mov ax,0x3
asm int 0x33
asm mov mouseb,bx
asm mov mousex,cx
asm mov mousey,dx
}

void setmousexy(unsigned int x,unsigned int y){
asm mov ax,0x4
asm mov cx,x
asm mov dx,y
asm int 0x33
}

void setminmaxx(unsigned int min,unsigned int max){
asm mov ax,0x7
asm mov cx,min
asm mov dx,max
asm int 0x33
}

void setminmaxy(unsigned int min,unsigned int max){
asm mov ax,0x8
asm mov cx,min
asm mov dx,max
asm int 0x33
}
#endif
