#include "tile2.cpp"
//#include "graphics.inc"
#include <stdlib.h>

const int mx=30,my=20;
int movetable[2][6]={1,2,3,4,11,11,11,11,11,3,1,11};
typedef struct
 {
 int strength,movement;
 int type;//1:army, 2:navy, 0:nonexistant
 } army;
int b=21;char c;
int x=0,y=0;
int rox,roy,mpo;
int t=0,p=-1,pm=0,ox,oy;
int libfile=0,mapthere=-1;
ofstream fileout;
char gf[]="wargame.dat",version[]="0.7a";
char filename[13];
army red[20],blue[20];
int numarm,numnav,numobj,obj;
int k,redarm,rednav,
    bluearm,bluenav;
int turns=0,rscore=0,bscore=0;
int armyloc[mx][my];//0:empty, -1-20:blue armies +1-20:red armies,
		    //21:red obj, 22:blue obj, 23:white obj.
int map[mx][my],flipmap[mx][my],gr[15][100];

/*
0=empty, 1=grass,
2=trees, 3=swamp,
4=water, 5=mountain.
*/
int *ground=&gr[0][0],*grass=&gr[1][0],*trees=&gr[2][0],
    *swamp=&gr[3][0],*water=&gr[4][0],*mountain=&gr[5][0],
    *whiteobj=&gr[6][0],*redobj=&gr[7][0],*blueobj=&gr[8][0],
    *redarmy=&gr[9][0],*bluearmy=&gr[10][0],
    *rednavy=&gr[11][0],*bluenavy=&gr[12][0],
    *sword=&gr[13][0],*boot=&gr[14][0];

void loadtiles();
void startup();
void mapdraw();
void gamedraw();
void gameinputl();
void gameinputm();
void gameloop();
void gamesetup();
void drawsetup();
void setupinput();
void loadmap();
void editor();
void editdraw();
void editinput();
void savemap();
void listmaps();
void killmap();
void combat();

void main(){char eg;
randomize();
loadtiles();
clrscr();
cout << "Wargame version " << version << "\nBy Ross Andrews."
     << "\n\nEmail:\nnzulch@swbell.net\nzerblinitzky@yahoo.com\n";
while(eg!='q'&&eg!='Q')
 {
 cout << "\n<E>ditor <G>ame or <Q>uit: ";cin >> eg;
 if(eg=='e'||eg=='E'||eg=='g'||eg=='G')
  {
  if(eg=='e'||eg=='E')
   editor();
  if(eg=='g'||eg=='G')
   gameloop();
  EndGfx();
  }
 }
cout << "Thanks for playing!";
}

void gameloop(){numarm=21,numobj=11,numnav=51;
c='y',mapthere=-1;char rm;
startup();
while(numarm>20||numarm<0)
 {
 cout << "Number of armies per side (max 20): ";cin >> numarm;
 }
while(numnav+numarm>20||numnav<0||numnav+numarm<=0)
 {
 cout << "Number of navies (armies+navies<=20): ";
 cin >> numnav;
 }
while(numobj>10||numobj<1)
 {
 cout << "Number of objectives (max 10): ";cin >> numobj;
 }
while(turns<=0)
 {
 cout << "Number of turns: ";cin >> turns;
 }
while(rm!='y'&&rm!='Y'&&rm!='n'&&rm!='N')
 {
 cout << "Random map (Y/N): ";cin >> rm;
 }
if(rm=='y'||rm=='Y')
 for(int n=0;n!=my;n++)
  for(int N=0;N!=mx;N++)
   {
   map[N][n]=random(10);
   if(map[N][n]>5)map[N][n]=0;
   }
else
 {
 while(mapthere!=1)
  {
  cout << "File to load from: ";cin >> filename;
  libfile=1;cout << "\n";
  listmaps();cout << "\n";
  loadmap();
  }
 }
for(int n=0;n<numarm;n++)
 {
 red[n].strength=10;blue[n].strength=10;
 red[n].movement=10;blue[n].movement=10;
 red[n].type=1;blue[n].type=1;
 }
for(;n<numarm+numnav;n++)
 {
 red[n].strength=10;blue[n].strength=10;
 red[n].movement=5; blue[n].movement=5;
 red[n].type=2;blue[n].type=2;
 }
for(;n!=20;n++)
 {
 red[n].strength=0;blue[n].strength=0;
 red[n].movement=0; blue[n].movement=0;
 red[n].type=0;blue[n].type=0;
 }
rscore=0;bscore=0;
gamesetup();
cout << "Game starts: Hit 'd' to end turn.";
getch();clrscr();ClearGfx(b);gamedraw();
while(turns>0)
 {c='y';
 cout << "Red player:\nTurns left: " <<turns
 << "\nScore: "<< rscore;
 getch();clrscr();ClearGfx(b);gamedraw();
 while(c!='d')
  {
  pm=1;
  while(pm==1&&c!='d')
   {
   gamedraw();
   c=getch();
   gameinputl();
   }
  rox=x;roy=y;mpo=red[armyloc[x][y]-1].movement;
  while(pm==2&&c!='d')
   {
   gamedraw();
   c=getch();
   gameinputm();
   }
  }
 for(n=0;n!=my;n++)
   for(int N=0;N!=mx;N++)
    if(armyloc[N][n]==21)rscore+=1;
 for(n=0;n<numarm;n++)
  blue[n].movement=10;
 for(;n<numarm+numnav;n++)
  blue[n].movement=5;
 c='y';
 cout << "Blue player:\nTurns left: " <<turns
 << "\nScore: "<< bscore;
 getch();clrscr();ClearGfx(b);gamedraw();
 while(c!='d')
  {
  pm=-1;
  while(pm==-1&&c!='d')
   {
   gamedraw();
   c=getch();
   gameinputl();
   }
  rox=x;roy=y;mpo=blue[armyloc[x][y]*-1-1].movement;
  while(pm==-2&&c!='d')
   {
   gamedraw();
   c=getch();
   gameinputm();
   }
  }
 turns--;
 for(n=0;n!=my;n++)
  for(N=0;N!=mx;N++)
   if(armyloc[N][n]==22)bscore+=1;
 for(n=0;n<numarm;n++)
  red[n].movement=10;
 for(;n<numarm+numnav;n++)
  red[n].movement=5;
 }
cout << "Red score  : " << rscore << "\nBlue score : " << bscore;
if(rscore==bscore) cout << "\n\nTie!";
if(rscore>bscore)  cout << "\n\nRed Wins!";
if(rscore<bscore)  cout << "\n\nBlue Wins!";
getch();
}

void gameinputm()
{int r=0,tx=x,ty=y;
p=armyloc[x][y];
ox=x;oy=y;
 switch(c)
 {
 case 'G':tx--;//Directions
 case 'H':ty--;break;
 case 'I':ty--;tx++;break;
 case 'O':tx--;
 case 'P':ty++;break;
 case 'Q':tx++;ty++;break;
 case 'K':tx--;break;
 case 'M':tx++;break;
 case ' ':
 case 'L':pm/=2;break;
 case 'u':r=1;
	  if(pm<0)blue[armyloc[x][y]*-1-1].movement=mpo;
	  if(pm>0)red[armyloc[x][y]-1].movement=mpo;
	  armyloc[rox][roy]=armyloc[x][y];armyloc[x][y]=0;
	  x=rox;y=roy;
	  break;
 }
if(tx<0||tx>mx||ty<0||ty>my)r=1;
if(armyloc[tx][ty]!=0){r=2;x=tx;y=ty;combat();}
if(pm<0&&r==0)
 {
 if(blue[p*-1-1].movement-movetable[blue[p*-1-1].type-1][map[tx][ty]]<0)r=1;
 }
if(pm>0&&r==0)
 {
 if(red[p-1].movement-movetable[red[p-1].type-1][map[tx][ty]]<0)r=1;
 }
if(r==0)
 {
 x=tx;y=ty;armyloc[x][y]=p;armyloc[ox][oy]=0;
 if(pm>0)
  red[armyloc[x][y]-1].movement-=
  movetable[red[armyloc[x][y]-1].type-1][map[x][y]];
 if(pm<0)
  blue[armyloc[x][y]*-1-1].movement-=
  movetable[blue[armyloc[x][y]*-1-1].type-1][map[x][y]];
 }
}

void combat()
{int tx=x,ty=y;x=ox;y=oy;
if(armyloc[tx][ty]>20)
 {
 if(pm==-2)armyloc[tx][ty]=22;
 if(pm==2)armyloc[tx][ty]=21;
 }
}


void gameinputl()
{
 switch(c)
 {
 case 'G':x--;//Directions
 case 'H':y--;break;
 case 'I':y--;x++;break;
 case 'O':x--;
 case 'P':y++;break;
 case 'Q':x++;y++;break;
 case 'K':x--;break;
 case 'M':x++;break;
 case 'v':cout << red[armyloc[x][y]-1].strength << " "
	       << red[armyloc[x][y]-1].movement << "\n"
	       << blue[armyloc[x][y]*-1-1].strength << " "
	       << blue[armyloc[x][y]*-1-1].movement;
	  getch();clrscr();ClearGfx(b);gamedraw();break;
 case ' ':
 case 'L':if(armyloc[x][y]!=0&&armyloc[x][y]<21)
	   {
	   if((armyloc[x][y]<0&&pm==-1)
	    ||(armyloc[x][y]>0&&pm== 1))pm*=2;}break;

 }
if(x>mx-1)x=0;if(x<0)x=mx-1;
if(y>my-1)y=0;if(y<0)y=my-1;
}

void gamedraw()
{
mapdraw();
if(pm==2||pm==-2)
  {p=armyloc[x][y];
  Rectangle(x*10,y*10,x*10+9,y*10+9,14,OPEN);
  if(p<0)
  {
  for(int k=0;k<blue[p*-1-1].strength;k++)
   tile(sword,300,k*10,-1);
  for(;k!=10;k++)blank(300,k*10,b);
  for(k=0;k<blue[p*-1-1].movement;k++)
   tile(boot,310,k*10,-1);
  for(;k!=10;k++)blank(310,k*10,b);
  }
 if(p>0)
  {
  for(int k=0;k<red[p-1].strength;k++)tile(sword,300,k*10,-1);
  for(;k!=10;k++)blank(300,k*10,b);
  for(k=0;k<red[p-1].movement;k++)tile(boot,310,k*10,-1);
  for(;k!=10;k++)blank(310,k*10,b);
  }}
else{if(armyloc[x][y]<0||(armyloc[x][y]>0&&armyloc[x][y]<21))
      {
      if(armyloc[x][y]<0)
       {
       for(int k=0;k<blue[armyloc[x][y]*-1-1].strength;k++)
	tile(sword,300,k*10,-1);
       for(;k!=10;k++)blank(300,k*10,b);
       for(k=0;k<blue[armyloc[x][y]*-1-1].movement;k++)
	tile(boot,310,k*10,-1);
       for(;k!=10;k++)blank(310,k*10,b);
       }
      if(armyloc[x][y]>0)
       {
       for(int k=0;k<red[armyloc[x][y]-1].strength;k++)
	tile(sword,300,k*10,-1);
       for(;k!=10;k++)blank(300,k*10,b);
       for(k=0;k<red[armyloc[x][y]-1].movement;k++)
	tile(boot,310,k*10,-1);
       for(;k!=10;k++)blank(310,k*10,b);
       }
      }
      else{
	  for(k=0;k!=10;k++)blank(300,k*10,b);
	  for(k=0;k!=10;k++)blank(310,k*10,b);
	  }
      Rectangle(x*10,y*10,x*10+9,y*10+9,15,OPEN);
      }
}

void gamesetup()
{c='y';obj=numobj;
redarm=numarm;rednav=numnav;
bluearm=numarm;bluenav=numnav;
StartGfx();ClearGfx(b);
drawsetup();
cout << "Place units. Press 'd' when done.";getch();
clrscr();ClearGfx(b);
while(c!='d'||redarm+bluearm+rednav+bluenav+obj!=0)
 {
 drawsetup();
 c=getch();
 setupinput();
 if(c=='q')break;
 }
}

void setupinput(){
switch(c)
 {
 case 'G':x--;//Directions
 case 'H':y--;break;
 case 'I':y--;x++;break;
 case 'O':x--;
 case 'P':y++;break;
 case 'Q':x++;y++;break;
 case 'K':x--;break;
 case 'M':x++;break;
 case '+':
 case '-':t++;break;
 case 'a':if(map[x][y]!=5&&map[x][y]!=4&&armyloc[x][y]==0)
	   {
	   if(t==0&&redarm!=0){armyloc[x][y]=redarm;redarm--;}
	   if(t==1&&bluearm!=0){armyloc[x][y]=bluearm*-1;bluearm--;}
	   }break;
 case 'n':if((map[x][y]==4||map[x][y]==3)&&armyloc[x][y]==0)
	   {
	   if(t==0&&rednav!=0){armyloc[x][y]=numarm+rednav;rednav--;}
	   if(t==1&&bluenav!=0){armyloc[x][y]=bluenav*-1-numarm;bluenav--;}
	   }break;
 case 'o':if(map[x][y]!=5&&armyloc[x][y]==0&&obj!=0)
	   {armyloc[x][y]=23;obj--;}break;
 case 'v':cout << armyloc[x][y] << " " << map[x][y]
	       << " " << p;getch();
	  clrscr();ClearGfx(b);break;
 case 'p':if(p==-1&&armyloc[x][y]!=0){p*=-1;ox=x;oy=y;}
	  else{if(armyloc[x][y]==0&&map[x][y]!=5){
		if(
		(((armyloc[ox][oy]<0&&armyloc[ox][oy]<numarm*-1)
		||(armyloc[ox][oy]>0&&armyloc[ox][oy]>numarm&&armyloc[ox][oy]<21))
		&&((map[x][y]==4)||(map[x][y]==3)))
		||
		(((armyloc[ox][oy]<0&&armyloc[ox][oy]>=numarm*-1)
		||(armyloc[ox][oy]>0&&armyloc[ox][oy]<=numarm))
		&&map[x][y]!=4)
		||
		(armyloc[ox][oy]>20)
		)
		 {if(p==1)p*=-1;
		 armyloc[x][y]=armyloc[ox][oy];
		 armyloc[ox][oy]=0;}}
	      }
	  break;
 }
if(x>mx-1)x=0;if(y>my-1)y=0;
if(x<0)x=mx-1;if(y<0)y=my-1;
if(t>1)t=0;
}

void drawsetup(){
mapdraw();
for(k=0;k<redarm;k++)tile(redarmy,300,k*10,b);
for(;k!=rednav+redarm;k++)tile(rednavy,300,k*10,b);
for(;k!=20;k++)blank(300,k*10,b);
for(k=0;k<bluearm;k++)tile(bluearmy,310,k*10,b);
for(;k!=bluenav+bluearm;k++)tile(bluenavy,310,k*10,b);
for(;k!=20;k++)blank(310,k*10,b);
Rectangle(x*10,y*10,x*10+9,y*10+9,15,OPEN);
if(t==0)Rectangle(300,0,309,10*(redarm+rednav)-1,4,OPEN);
 else Rectangle(310,0,319,10*(bluearm+bluenav)-1,1,OPEN);
if(p==1)Rectangle(ox*10,oy*10,ox*10+9,oy*10+9,14,OPEN);
}

void editor(){c='y';
startup();
StartGfx();
ClearGfx(b);
while(c!='q')
 {
 editdraw();
 c=getch();
 editinput();
 }
}

void editinput(){int d=0;
switch(c)
 {
 case 'G':x--;//Directions
 case 'H':y--;d=1;break;
 case 'I':y--;x++;d=1;break;
 case 'O':x--;
 case 'P':y++;d=1;break;
 case 'Q':x++;y++;d=1;break;
 case 'K':x--;d=1;break;
 case 'M':x++;d=1;break;
 case '-':t--;d=1;break;//Type selection
 case '+':t++;d=1;break;
 case 'g':t=map[x][y];
 case ' '://Assignment
 case 'L':map[x][y]=t;d=1;break;
 }
 if(d!=1)
  {
  switch(c)
   {
 // Transformation
   case 'r':for(int n=0;n!=mx;n++) map[n][y]=t;break;
   case 'c':for(n=0;n!=my;n++) map[x][n]=t;break;
   case 'p':p*=-1;break;
   case 'b':map[x][y]=t;
	    if(x!=0)map[x-1][y]=t;
	    if(x!=mx-1)map[x+1][y]=t;
	    if(y!=0)map[x][y-1]=t;
	    if(y!=my-1)map[x][y+1]=t;
	    if(x!=0&&y!=0)map[x-1][y-1]=t;
	    if(x!=0&&y!=my-1)map[x-1][y+1]=t;
	    if(x!=mx-1&&y!=0)map[x+1][y-1]=t;
	    if(x!=mx-1&&y!=my-1)map[x+1][y+1]=t;
	    break;
   case 'a':int ot=map[x][y];
	    for(n=0;n!=my;n++)
	     for(int N=0;N!=mx;N++)
	      if(map[N][n]==ot)map[N][n]=-1;
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      if(map[N][n]==t)map[N][n]=ot;
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      if(map[N][n]==-1)map[N][n]=t;
	    break;
   case 'f':for(n=0;n!=my;n++) for(N=0;N!=mx;N++) map[N][n]=t;break;
   case 't':ot=map[x][y];
	    for(n=0;n!=my;n++){
	     for(N=0;N!=mx;N++){
	      if(map[N][n]==ot) map[N][n]=t;}}
	    break;
   case 'v':for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      flipmap[N][n]=map[mx-N%mx-1][n];
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      map[N][n]=flipmap[N][n];break;
   case 'h':for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      flipmap[N][n]=map[mx-N%mx-1][n];
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      map[N][n]=flipmap[N][n];
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      flipmap[mx-N-1][my-n-1]=map[N][n];
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      map[N][n]=flipmap[N][n];break;
   case ',':for(N=0;N!=mx;N++)
	     for(n=0;n!=my;n++)
	      flipmap[N][n]=map[N+1][n];
	    for(n=0;n!=my;n++)
	     flipmap[mx-1][n]=map[0][n];
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      map[N][n]=flipmap[N][n];break;
   case '.':for(N=0;N!=mx;N++)
	     for(n=0;n!=my;n++)
	      flipmap[N][n]=map[N-1][n];
	    for(n=0;n!=my;n++)
	     flipmap[0][n]=map[mx-1][n];
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      map[N][n]=flipmap[N][n];break;
   case ';':for(N=0;N!=mx;N++)
	     for(n=0;n!=my;n++)
	      flipmap[N][n]=map[N][n+1];
	    for(n=0;n!=mx;n++)
	     flipmap[n][my-1]=map[n][0];
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      map[N][n]=flipmap[N][n];break;
   case '/':for(N=0;N!=mx;N++)
	     for(n=0;n!=my;n++)
	      flipmap[N][n]=map[N][n-1];
	    for(n=0;n!=mx;n++)
	     flipmap[n][0]=map[n][my-1];
	    for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      map[N][n]=flipmap[N][n];break;
   case 'V':cout << "Wargame v." << version;//Text stuff
	    getch();clrscr();ClearGfx(b);editdraw();
   case 'n':libfile=1;cout << "Libfile name: ";cin >> filename;
	    clrscr();ClearGfx(b);editdraw();break;
   case 'N':libfile=0;cout << "Libfile unnamed.";getch();clrscr();
	    ClearGfx(b);editdraw();break;
   //File functions.
   case 's':savemap();clrscr();ClearGfx(b);editdraw();break;
   case 'l':loadmap();clrscr();ClearGfx(b);editdraw();break;
   case 'k':killmap();clrscr();ClearGfx(b);editdraw();break;
   case 'T':listmaps();getch();clrscr();
	    ClearGfx(b);editdraw();break;
   case 'R':for(n=0;n!=my;n++)
	     for(N=0;N!=mx;N++)
	      map[N][n]=random(6);break;
   }
  }
if(x>mx-1)x=0;if(y>my-1)y=0;
if(x<0)x=mx-1;if(y<0)y=my-1;
if(t<0)t=5;if(t>5)t=0;
if(p==1)map[x][y]=t;
}

void listmaps()
{char mapname[13],f='a';
if (!libfile)
 {
 cout << "Lib file: ";cin >> filename;
 }
filein.open(filename);
if (!filein.fail())
 {
 filein >> mapname;filein >> mapname;
 cout << mapname << "\n";
 while (!filein.eof())
  {
  filein.get(f);
  if (f==':')
   {
   filein >> mapname; cout << mapname << "\n";
   }
  }
 filein.close();
 }
}

void killmap()
{char f,mapname[13],fmapname[13];int dummy;
if (!libfile)
 {
 cout << "Lib file: ";cin >> filename;
 }
cout << "Map name: ";cin >> mapname;
filein.open(filename);
if (!filein.fail())
 {
 fileout.open("temp.dat");
 filein.get(f);
 while (!filein.eof())
  {
  if (f==':')
   {
   filein >> fmapname;
   if (strcmp(fmapname,mapname)==0)
    {
    for (int n=0;n!=mx*my;n++)
     filein >> dummy;
    } else fileout << ": " << fmapname;
   } else fileout.put(f);
  filein.get(f);
  }
 filein.close();fileout.close();
 filein.open("temp.dat");fileout.open(filename);
 filein.get(f);
 while (!filein.eof())
  {
  fileout.put(f);filein.get(f);
  }
 fileout.close();
 cout << mapname << " deleted.";
 getch();
 }
filein.close();
}

void loadmap()
{char word[13],mapname[13];
if (!libfile)
 {
 cout << "Lib file: ";cin >> filename;
 }
cout << "Map name: ";cin >> mapname;
filein.open(filename);
if (!filein.fail())
 {
 while ((strcmp(word,mapname)!=0) && (!filein.eof())) filein >> word;
 if(!filein.eof()) mapthere=1;
 for(int n=0;n!=my;n++)
  for(int N=0;N!=mx;N++)
   filein >> map[N][n];
 }
filein.close();
clrscr();
}

void savemap()
{char f,mapname[13],fmapname[13];int dummy;
if (!libfile)
 {
 cout << "Lib file: ";cin >> filename;
 }
cout << "Map name: ";cin >> mapname;
filein.open(filename);
if (!filein.fail())
 {
 fileout.open("temp.dat");
 filein.get(f);
 while(!filein.eof())
  {
  if (f==':')
   {
   filein >> fmapname;
   if (strcmp(fmapname,mapname)==0)
    {
    for (int n=0;n!=mx*my;n++)
     filein >> dummy;
    } else fileout << ": " << fmapname;
   } else fileout.put(f);
  filein.get(f);
  }
 filein.close();fileout.close();
 filein.open("temp.dat");
 fileout.open(filename);
 filein.get(f);
 while(!filein.eof())
  {
  fileout.put(f);filein.get(f);
  }
 filein.close();
 } else fileout.open(filename);
fileout << " : " << mapname << "\n";
for(int n=0;n!=my;n++)
 for(int N=0;N!=mx;N++)
  fileout << map[N][n] << " ";
fileout << "\n";
fileout.close();
clrscr();
}

void editdraw(){
mapdraw();
Rectangle(x*10,y*10,x*10+9,y*10+9,15,OPEN);
for(int n=0;n!=6;n++)
 tile(&gr[n][0],305,n*10+5,-1);
Rectangle(305,t*10+5,314,t*10+9+5,15,OPEN);
}

void mapdraw(){
for(int n=0;n!=my;n++)
 for(int N=0;N!=mx;N++)
  {
  if(armyloc[N][n]==0)tile(&gr[map[N][n]][0],N*10,n*10,b);
   else{tile(&gr[map[N][n]][0],N*10,n*10,b);
	if(armyloc[N][n]<0&&armyloc[N][n]>=numarm*-1)
	 tile(bluearmy,N*10,n*10,-1);
	if(armyloc[N][n]>0&&armyloc[N][n]<=numarm)
	 tile(redarmy,N*10,n*10,-1);
	if(armyloc[N][n]<0&&armyloc[N][n]<numarm*-1)
	 tile(bluenavy,N*10,n*10,-1);
	if(armyloc[N][n]>0&&armyloc[N][n]>numarm&&armyloc[N][n]<21)
	 tile(rednavy,N*10,n*10,-1);
	if(armyloc[N][n]==21)
	 tile(redobj,N*10,n*10,-1);
	if(armyloc[N][n]==22)
	 tile(blueobj,N*10,n*10,-1);
	if(armyloc[N][n]==23)
	 tile(whiteobj,N*10,n*10,-1);
	}
  }
}

void startup(){
for(int n=0;n!=my;n++)
 for(int N=0;N!=mx;N++)
  map[N][n]=0;
for(n=0;n!=my;n++)
 for(N=0;N!=mx;N++)
  armyloc[N][n]=0;
}

void loadtiles(){int *gp,n;
gp=loadtile(gf,"ground");
for (n=0;n!=d*d;n++)
 gr[0][n]=*(gp+n);
gp=loadtile(gf,"grass");
for (n=0;n!=d*d;n++)
 gr[1][n]=*(gp+n);
gp=loadtile(gf,"trees");
for (n=0;n!=d*d;n++)
 gr[2][n]=*(gp+n);
gp=loadtile(gf,"swamp");
for (n=0;n!=d*d;n++)
 gr[3][n]=*(gp+n);
gp=loadtile(gf,"water");
for (n=0;n!=d*d;n++)
 gr[4][n]=*(gp+n);
gp=loadtile(gf,"mountain");
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
gp=loadtile(gf,"redarmy");
for (n=0;n!=d*d;n++)
 gr[9][n]=*(gp+n);
gp=loadtile(gf,"bluearmy");
for (n=0;n!=d*d;n++)
 gr[10][n]=*(gp+n);
gp=loadtile(gf,"rednavy");
for (n=0;n!=d*d;n++)
 gr[11][n]=*(gp+n);
gp=loadtile(gf,"bluenavy");
for (n=0;n!=d*d;n++)
 gr[12][n]=*(gp+n);
gp=loadtile(gf,"sword");
for (n=0;n!=d*d;n++)
 gr[13][n]=*(gp+n);
gp=loadtile(gf,"boot");
for (n=0;n!=d*d;n++)
 gr[14][n]=*(gp+n);
}
