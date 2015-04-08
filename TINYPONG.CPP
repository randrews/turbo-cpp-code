#include <conio.h>
#include <stdlib.h>
#include "tmouse.cpp"
#include "tgraph.cpp"

class paddle{
public:
paddle(); // Constructor. Since we've only got
	  // one instance I'll use this to init
	  // variables in.
void update(); // Update status of the game.
private:  // Stuff that paddle::update() needs
	  // but nothing else does.
void chkball(); // Did the ball drop or bounce?
void fall();    // Oopsie, it fell.
int bx,by, // Ball coords
    dx,dy, // Delta-x, delta-y. Ball speed and dir.
    px,py, // Paddle position. py is constant, of course.
    ox,oy, // Old ball position. From the last round.
    omx,   // Old mouse position, used to see if the
	   // paddle needs to be redrawn.
    ballsleft, // Number of balls left until the game ends.
    clr,lngth; // Color and length of paddle.
cursor mouse;
};

paddle::paddle(){
mouse=cursor(); // Call cursor's constructor
ballsleft=3;clr=15;lngth=30; // Setting up variables
py=195;
bx=random(320); // Ball starts in a random spot.
by=random(100);
ox=bx,oy=by;    // Old position of ball is also new
		// pos, because it's 1st cycle....
dx=(random(2)==0?-1:1); // Ball goes in a random dir
dy=(random(2)==0?-1:1);
px=160-lngth/2; // x coord of paddle is in middle.
}

void paddle::update(){
mouse.update(); // Update mouse status
chkball(); // Did the ball hit the ground?
bx+=dx;by+=dy; // I guess it didn't, move it....
pixel(ox,oy,0); // Zorch the old ball image
pixel(bx,by,clr); // Draw a new one
ox=bx,oy=by; // Update the old-ball-position

if(mouse.x+lngth>319)mouse.x=319-lngth; // Make sure
					//the paddle stays onscreen
if(omx!=mouse.x) // If the paddle moved....
 {
 px=mouse.x; // Move the paddle
 omx=px;     // Old mouse pos...
 hline(0,319,py,0); // Zorch old paddle image
 hline(px,px+lngth,py,clr); // Draw new paddle image
 }
}

void paddle::chkball(){
if(bx==1||bx==318)dx*=-1; // Bounce off the sides of neccessary
if(by==1)dy*=-1;          // Bounce off the top....
if(by==py-1&&(bx>=px&&bx<=px+lngth))dy*=-1; // Bounce off the paddle....
if(by==199)fall(); // Uh-oh, I dropped it....
} // Since the delta-x and delta-y are added to the ball-x and ball-y
  // each round, by making dx or dy negative or positive, we can change
  // the direction the ball is traveling.

void paddle::fall(){
ballsleft--; // You break, you buy!
if(ballsleft==0) // You are out of balls. Insert more coins!
 {
 mouse.getclick(); // Wait for a click.
 endgraph(); // Go back to text mode.
 exit(0); // Make the program die now.
 }
bx=random(320); // Make a new ball, random pos and dir.
by=random(100);
dx=(random(2)==0?-1:1);
dy=(random(2)==0?-1:1);
mouse.getclick(); // Wait for Mr. User to click before we drop him
}		  // back in the game.

void main(){
randomize(); // Make all the numbers random.
startgraph(); // Start graphics mode.
paddle p=paddle(); // Make a paddle and a ball for us.
while(!kbhit()) // While I don't touch the keyboard....
 {
 p.update(); // Update the game.
 delay(10);  // Wait a bit so it doesn't run too fast.
 }
endgraph();  // Go back to text mode, game is over.
}