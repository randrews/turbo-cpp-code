#include <conio.h>

enum bool {false,true}; //false=0 true=1
bool board[79][24];

void refresh();
void main()
{ for (int x=0;x<80;x++)
  { for (int y=0;y<25;y++)
    { board[x][y]=false;
    }
  }
  _setcursortype(_NOCURSOR);
  clrscr();

  int coordx=1,coordy=1;
  char input;

  gotoxy(9,4); putch(201);
  gotoxy(71,4); putch(187);
  for (x=10;x<=70;x++) { gotoxy(x,4); putch(205); }
  gotoxy(9,21); putch(200);
  gotoxy(71,21); putch(188);
  for (x=10;x<=70;x++) { gotoxy(x,21); putch(205); }
  for (int y=5;y<=20;y++)
  { gotoxy(9,y); putch(186);
    gotoxy(71,y); putch(186);
  }

  input=getch();
  while (input!='q')
  { window(10,5,70,20);

    switch (input)
    { case 'H': coordy--; refresh(); break;
      case 'P': coordy++; refresh(); break;
      case 'K': coordx--; refresh(); break;
      case 'M': coordx++; refresh(); break;
    }

    if (coordx<2) coordx=2;
    if (coordx>60) coordx=60;
    if (coordy<2) coordy=2;
    if (coordy>15) coordy=15;

    if (input=='`')
    { 	if (board[coordx-2][coordy-1]==false) board[coordx-2][coordy-1]=true;
	else if (board[coordx-2][coordy-1]==true) board[coordx-2][coordy-1]=false;

	if (board[coordx][coordy-1]==false) board[coordx][coordy-1]=true;
	else if (board[coordx][coordy-1]==true) board[coordx][coordy-1]=false;

	if (board[coordx-1][coordy-2]==false) board[coordx-1][coordy-2]=true;
	else if (board[coordx-1][coordy-2]==true) board[coordx-1][coordy-2]=false;

	if (board[coordx-1][coordy]==false) board[coordx-1][coordy]=true;
	else if (board[coordx-1][coordy]==true) board[coordx-1][coordy]=false;
    }
    gotoxy(coordx,coordy); putch(219);
    input=getch();
  }
  clrscr();
}

void refresh()
{ clrscr();
  for (int x=1;x<60;x++)
  { for (int y=1;y<15;y++)
    {
      if (board[x][y]==true) { gotoxy(x+1,y+1); putch(176); }
      //if (board[x][y]==false) { gotoxy(x+1,y+1); cprintf(" "); }
    }
  }
}

