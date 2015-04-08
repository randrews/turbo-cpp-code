#include <dos.h>
#include <conio.h>

int oldmode;

void startgraph();
void endgraph();

void main(){
getch();
startgraph();
getch();
endgraph();}

void startgraph(){
union REGS in,out;
in.h.ah=0xf;
int86(0x10,&in,&out);
oldmode=out.h.al;
in.h.ah=0;
in.h.al=0x13;
int86(0x10,&in,&out);}

void endgraph(){
union REGS in,out;
in.h.ah=0;
in.h.al=oldmode;
int86(0x10,&in,&out);}