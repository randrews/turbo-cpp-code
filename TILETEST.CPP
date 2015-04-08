#include "tile2.cpp"

void main()
{int f[d*d];
StartGfx();ClearGfx(0);
tile(loadtile("atomic.dat","3red"),MIDX,MIDY,13);
for (int n=0;n!=d*d;n++)
 f[n]=*(loadtile("atomic.dat","1red")+n);
tile (f,MIDX,MIDY,0);
//tile(yxinvert(loadtile("atomic.dat","3red")),100,MIDY,13);
getch();
}
