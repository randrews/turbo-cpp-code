#include "tile.cpp"
#include <stdlib.h>

int gr[15][100];
char gf[13]="wargame.dat";
int *redarmy=&gr[0][0],*bluearmy=&gr[1][0],*water=&gr[2][0],
    *grass=&gr[3][0],*trees=&gr[4][0],*swamp=&gr[5][0],
    *whiteobj=&gr[6][0],*redobj=&gr[7][0],*blueobj=&gr[8][0],
    *mountain=&gr[9][0],*boot=&gr[10][0],*sword=&gr[11][0],
    *ground=&gr[12][0],*rednavy=&gr[13][0],*bluenavy=&gr[14][0];
void main(){int *gp,n;
gp=loadtile(gf,"redarmy");
for (n=0;n!=d*d;n++)
 gr[0][n]=*(gp+n);
gp=loadtile(gf,"bluearmy");
for (n=0;n!=d*d;n++)
 gr[1][n]=*(gp+n);
gp=loadtile(gf,"water");
for (n=0;n!=d*d;n++)
 gr[2][n]=*(gp+n);
gp=loadtile(gf,"grass");
for (n=0;n!=d*d;n++)
 gr[3][n]=*(gp+n);
gp=loadtile(gf,"trees");
for (n=0;n!=d*d;n++)
 gr[4][n]=*(gp+n);
gp=loadtile(gf,"swamp");
for (n=0;n!=d*d;n++)
 gr[5][n]=*(gp+n);
gp=loadtile(gf,"whiteobj");
for (n=0;n!=d*d;n++)
 gr[6][n]=*(gp+n);
gp=loadtile(gf,"redobj");
for (n=0;n!=d*d;n++)
 gr[7][n]=*(gp+n);
gp=loadtile(gf,"blueobj");
for (n=0;n!=d*d;n++)
 gr[8][n]=*(gp+n);
gp=loadtile(gf,"mountain");
for (n=0;n!=d*d;n++)
 gr[9][n]=*(gp+n);
gp=loadtile(gf,"boot");
for (n=0;n!=d*d;n++)
 gr[10][n]=*(gp+n);
gp=loadtile(gf,"sword");
for (n=0;n!=d*d;n++)
 gr[11][n]=*(gp+n);
gp=loadtile(gf,"ground");
for (n=0;n!=d*d;n++)
 gr[12][n]=*(gp+n);
gp=loadtile(gf,"rednavy");
for (n=0;n!=d*d;n++)
 gr[13][n]=*(gp+n);
gp=loadtile(gf,"bluenavy");
for (n=0;n!=d*d;n++)
 gr[14][n]=*(gp+n);
StartGfx();
ClearGfx(21);
tile(mountain,50,50,-1);
tile(grass,75,75,-1);tile(redarmy,75,75,-1);
tile(trees,100,100,-1);tile(bluearmy,100,100,-1);
tile(ground,0,0,-1);
tile(grass,10,0,-1);
tile(trees,20,0,-1);
tile(swamp,30,0,-1);
tile(water,40,0,-1);
for(n=50;n!=120;n+=10)
 tile(water,n,0,-1);
tile(whiteobj,50,0,-1);
tile(redobj,60,0,-1);
tile(blueobj,70,0,-1);
tile(redarmy,80,0,-1);
tile(bluearmy,90,0,-1);
tile(rednavy,100,0,-1);
tile(bluenavy,110,0,-1);
tile(boot,120,0,-1);
tile(sword,130,0,-1);
getch();
backgrnd(water,-1);
getch();
}

