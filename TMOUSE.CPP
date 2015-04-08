// Tiny mouse library. No sort of error checking,
// and all the important bits are done in good old,
// unreadable assembly! But it has a cursor class,
// isn't too long.
// -Zerblinitzky

#ifndef _tmouse_cpp_
#define _tmouse_cpp_
#define _graph_ // for using mode 13h, cursor class will
		// automagically divide x coord by two.
		// Comment if you don't like.
unsigned int mousex,mousey,mouseb;

void readmouse(){ // Checks mouse status, then changes the
asm mov ax,0x3    // mousex, mousey, and mouseb variables
asm int 0x33      // to match. In mode 13h, mousex will be
asm mov mouseb,bx // twice the actual coord. Who knows why?
asm mov mousex,cx
asm mov mousey,dx
}

void showmouse(){ // Shows the hardware-controlled cursor.
asm mov ax,0x1    // Simple, but ugly.
asm int 0x33
}

void hidemouse(){ // Hides the hardware-controlled cursor.
asm mov ax,0x2
asm int 0x33
}

int getclick(){   // Gets one single click from the mouse.
		  // Returns the value of the button clicked.
while(mouseb==0)readmouse();
while(mouseb!=0)readmouse();
return mouseb;
}

// And, for the C++ inclined...
class cursor{
public: cursor();
	void update();
	int getclick();
	int x,y,b;
};

cursor::cursor(){
update();
}

void cursor::update(){int tb,tx,ty; // Temp variables
asm mov ax,0x3
asm int 0x33
asm mov tb,bx
asm mov tx,cx
asm mov ty,dx
#ifdef _graph_
x=tx>>1;
y=ty;
b=tb;
#endif
}

int cursor::getclick(){
return getclick();
}

#endif

