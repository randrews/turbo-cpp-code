#ifndef tile_lib
#define tile_lib 1
#include "graph.inc"
#include <fstream.h>
#include <conio.h>
#include <iostream.h>
#include <string.h>
#define maxtext 53
const int d=10;
//const int d=5;
int s[d*d],z[d*d],z2[d*d];
int *alphabet[maxtext];
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

void directsafetile(int *a,int x,int y,int t)
{
for(int n=0;n!=d*d;n++)
 {
 if(*(a+n)==13 && t!=-1
    && (x+n%d<=319) && (y+n/d<=199))
    directpixel(x+n%d,y+n/d,t);
 if(*(a+n)!=13&& (x+n%d<=319) && (y+n/d<=199))
    directpixel(x+n%d,y+n/d,*(a+n));
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
{char word[12];ifstream filein;
filein.open(filename);
if (!filein.fail())
 {
 while ((strcmp(word,tile)!=0) && (!filein.eof())) filein >> word;
 for (int n=0;n!=d*d;n++) filein >> s[n];
 }
filein.close();
return s;
}

int* newload(char filename[12],char tile[12])
{int *tmp=new int[d*d];
char word[12];ifstream filein;
filein.open(filename);
if (!filein.fail())
 {
 while ((strcmp(word,tile)!=0) && (!filein.eof())) filein >> word;
 for (int n=0;n!=d*d;n++) filein >> *(tmp+n);
 }
filein.close();
//if(tmp)return 0;else return 1;
return tmp;
}

int* newload5(char filename[12],char tile[12])
{int *tmp=new int[5];
char word[12];ifstream filein;
filein.open(filename);
if (!filein.fail())
 {
 while ((strcmp(word,tile)!=0) && (!filein.eof())) filein >> word;
 for (int n=0;n!=5;n++) filein >> *(tmp+n);
 }
filein.close();
//if(tmp)return 0;else return 1;
return tmp;
}

int* textload(char filename[12],char letter[1])
{int *ga=newload5(filename,letter);
int r,n,t,*rp=new int[5],*ans=new int[25],*lp=new int[5],
	  *zns=new int[25];
for(n=0;n!=5;n++)
 {
 for(int j=0;j!=5;j++)
  {
  *(zns+j+n*5)=*(ga+n)%2;
  *(ga+n)/=2;
  }
 }
for(n=0;n!=25;n++)
 *(ans+5*(n/5)+(5-n%5-1))=*(zns+n);
return ans;
}

void fontload(){
char *ltrs[]={"a","b","c","d","e",
	      "f","g","h","i","j",
	      "k","l","m","n","o",
	      "p","q","r","s","t",
	      "u","v","w","x","y",
	      "z",
	      "n1","n2",
	      "n3","n4",
	      "n5","n6",
	      "n7","n8",
	      "n9","Zero",".","space",
	      "comma","exclam","colon",
	      "question","open","close",
	      "minus","plus","times",
	      "slash","bslash","equal",
	      "exponent","bar","underscore"};
for(int n=0;n!=maxtext;n++)
 {
 *(alphabet+n)=textload("font.bit",*(ltrs+n));
 }
}

void charout(int ltr,int x,int y,int fg,int bg)
{int *letter=alphabet[ltr];
/*if(ltr>='a'&&ltr<='z')letter=alphabet[(int)(ltr-'a')];
if(ltr=='.')letter=alphabet[36];
if(ltr==' ')letter=alphabet[37];
if(ltr>='1'&&ltr<='9')letter=alphabet[(int)(ltr-'1'+26)];
if(ltr=='0')letter=alphabet[35];*/
for(int n=0;n!=5;n++)
 {
 for(int r=0;r!=5;r++)
  {
  if(*(letter+r+n*5)==0)pixel(x+r,y+n,bg);
  else pixel(x+r,y+n,fg);
  }
 }
}

void directcharout(int ltr,int x,int y,int fg,int bg)
{int *letter=alphabet[ltr];
/*if(ltr>='a'&&ltr<='z')letter=alphabet[(int)(ltr-'a')];
if(ltr=='.')letter=alphabet[36];
if(ltr==' ')letter=alphabet[37];
if(ltr>='1'&&ltr<='9')letter=alphabet[(int)(ltr-'1'+26)];
if(ltr=='0')letter=alphabet[35];*/
for(int n=0;n!=5;n++)
 {
 for(int r=0;r!=5;r++)
  {
  if(*(letter+r+n*5)==0)directpixel(x+r,y+n,bg);
  else directpixel(x+r,y+n,fg);
  }
 }
}

int whatchar(char c){int i=-1;
if(c>='a'&&c<='z')
 i=(int)(c-'a');
if(c>='A'&&c<='Z')
 i=(int)(c-'A');
if(c>='1'&&c<='9')
 i=(int)(c-'1'+26);
if(i==-1)
 {
 switch(c)
  {
  case ' ':i=37;break;
  case '.':i=36;break;
  case '0':i=35;break;
  case ',':i=38;break;
  case '!':i=39;break;
  case ':':i=40;break;
  case '?':i=41;break;
  case '(':i=42;break;
  case ')':i=43;break;
  case '-':i=44;break;
  case '+':i=45;break;
  case '*':i=46;break;
  case '/':i=47;break;
  case '\\':i=48;break;
  case '=':i=49;break;
  case '^':i=50;break;
  case '|':i=51;break;
  case '_':i=52;break;
  default :i=37;break;
  }
 }
return i;
}

void strout(char *str,int x,int y,int fg,int bg)
{int n=0,i,s_x=x;char c;
while(*(str+n)!='\0')
 {
 //c=*(str+n);
 if(*(str+n)=='\n'){y+=5;x=s_x;}
 else {i=whatchar(*(str+n));
 //if((c>='a'&&c<='z')||(c>='1'&&c<='9')||c=='.'||c=='0'||c==' ')
  charout(i,x,y,fg,bg);
 x+=5;}
 n++;
 }
}

void directstrout(char *str,int x,int y,int fg,int bg)
{int n=0,i;char c;
while(*(str+n)!='\0')
 {
 //c=*(str+n);
 i=whatchar(*(str+n));
 //if((c>='a'&&c<='z')||(c>='1'&&c<='9')||c=='.'||c=='0'||c==' ')
  directcharout(i,x,y,fg,bg);
 x+=5;
 n++;
 }
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