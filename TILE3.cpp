#ifndef tile_lib
#define tile_lib 1
#include "graph.inc"
#include <fstream.h>
#include <conio.h>
#include <iostream.h>
#include <string.h>

const int d=10;
int s[d*d],z[d*d],z2[d*d];
ifstream filein;

//void tile(int x,int y,int t);
void tile(int *a,int x, int y, int t);
void directtile(int *a,int x,int y,int t);
void blank(int x,int y,int c);
void backgrnd(int *a,int t);
void layer(int *btm, int *top,int x,int y,int t);
int * loadtile(char filename[12],char tile[12]);

int * transform(int s[d*d],int a,int b);
int * vertical(int s[d*d]);
int * invert(int s[d*d]);
int * horizontal(int s[d*d]);
int * cwrotate(int s[d*d]);
int * ccwrotate(int s[d*d]);
int * yxinvert(int s[d*d]);

//
//Example of loadtile usage:
/* int *gp=loadtile(gf,"player");
   for (int n=0;n!=d*d;n++)
    graphics[0][n]=*(gp+n);*/
//

/*void tile(int s[d*d],int x,int y,int t)
{
for (int n=0;n!=d*d;n++)
 {
 Pixel(x+n%d,y+n/d,s[n]);
 if (s[n]==13) Pixel(x+n%d,y+n/d,t);
 }
} */
void tile(int *a,int x,int y,int t)
{
for(int n=0;n!=d*d;n++)
 {
 if(*(a+n)==13 && t!=-1) pixel(x+n%d,y+n/d,t);
 if(*(a+n)!=13) pixel(x+n%d,y+n/d,*(a+n));
 }
}

void directtile(int *a,int x,int y,int t)
{
for(int n=0;n!=d*d;n++)
 {
 if(*(a+n)==13 && t!=-1) directpixel(x+n%d,y+n/d,t);
 if(*(a+n)!=13) directpixel(x+n%d,y+n/d,*(a+n));
 }
}

void directblank(int x,int y,int c)
{
for(int n=0;n!=d*d;n++)
 directpixel(x+n%d,y+n/d,c);
}

void blank(int x,int y,int c)
{
for(int n=0;n!=d*d;n++)
 pixel(x+n%d,y+n/d,c);
}

void backgrnd(int *a,int t)
{
for(int n=0;n!=20;n++)
 {
 for(int N=0;N!=32;N++)
  tile(a,N*10,n*10,t);
 }
}

void layer(int *btm, int *top,int x,int y, int t)
{
for(int n=0;n!=d*d;n++)
 {
 if(*(top+n)!=13){pixel(x+n%d,y+n/d,*(top+n));}
 else if(*(btm+n)==13 && t!=-1){pixel(x+n%d,y+n/d,t);}
 else pixel(x+n%d,y+n/d,*(btm+n));
 }
}

int * loadtile(char filename[12],char tile[12])
{char word[12];
filein.open(filename);
if (!filein.fail())
 {
 while ((strcmp(word,tile)!=0) && (!filein.eof())) filein >> word;
 for (int n=0;n!=d*d;n++) filein >> s[n];
 }
filein.close();
return s;
}

int * transform(int s[d*d],int a,int b)
{
for (int n=0;n!=d*d;n++)
 {
 if (s[n]==a) z[n]=b;
 else z[n]=s[n];
 }
return z;
}

int * vertical(int s[d*d])
{
for(int n=0;n!=d*d;n++)
 z[n]=s[d*(n/d)+(d-n%d-1)];
for(n=0;n!=d*d;n++)
 z2[n]=*(z+n);
return z2;
}

int * invert(int s[d*d])
{
for (int n=d*d;n!=0;n--)
 z[d*d-n]=s[n-1];
return z;
}

int * horizontal(int s[d*d])
{
return invert(vertical(s));
}

int * cwrotate(int s[d*d])
{
for (int n=0;n!=d*d;n++)
 z[n]=s[d*(d-n%d-1)+(n/d)];
return z;
}

int * ccwrotate(int s[d*d])
{
for (int n=0;n!=d*d;n++)
 z[n]=s[d*(n%d)+(d-n/d-1)];
return z;
}

int * yxinvert(int s[d*d])
{
for (int n=0;n!=d*d;n++)
 z[n]=s[d*(d-n%d-1)+(d-n/d-1)];
return z;
}
#endif