#include <math.h>
#include <conio.h>
#include "tgraph12h.cpp"
double deg_rad(double a){return a*M_PI/180;}

class spaceship{
public: int x,y,spd;long double angle;
spaceship();
void draw();
void update();
};

void spaceship::update(){
double ang=deg_rad(angle);
x+=cos(ang)*spd;
y-=sin(ang)*spd;
}

void spaceship::draw(){
hline(x-1,x+2,y,15);
vline(y-1,y+2,x,15);
}

spaceship::spaceship(){
x=160,y=100,spd=0;
angle=30;
//angle*=M_PI/180;
//angle=deg_rad(angle);
}

spaceship enterprise;

void main(){char c;double kba=90.0;
startgraph();
while(c!=27)
 {
 //cleargraph(0);
 if(c=='K')kba++;
 if(c=='M')kba--;
 if(c=='+'){enterprise.spd+=3;c='j';}
 if(c=='-'){enterprise.spd-=3;c='j';}
 enterprise.angle=(double)kba;
 enterprise.draw();
 enterprise.update();
 delay(20);
 if(kbhit())c=getch();
 }
endgraph();
}

