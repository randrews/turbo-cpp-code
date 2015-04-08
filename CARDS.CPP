#ifndef CARDS_CPP
#define CARDS_CPP
//#define TESTING
#include <iostream.h>
#include <stdlib.h>
typedef struct{int suit;
	       int value;} card;

card *deck;

void initdeck(){card c;

if(!(deck=new card[52]))
 {cout << "ERROR: This program is unable to "
	<< "allocate memory for the deck of cards.\n"
	<< "It will now die painfully.";
   exit(1);
 }
else
 {
 for(int n=0;n!=4;n++)
  {
  for(int N=0;N!=13;N++)
   {
   c.suit=n;c.value=N;
   *(deck+N+13*n)=c;
   //*(deck+N+13*n)=N;
   }
  }
 }
}

#ifdef TESTING

#include <conio.h>

void main(){
clrscr();
cout << *deck.suit;
getch();
}

#endif


#endif