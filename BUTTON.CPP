typedef void (*ClickPFN)(int);
typedef void (*OverPFN)();
typedef void (*DrawPFN)(int,int,int,int);
//typedef void (*CheckPFN)(int,int,int);

class button{
public: int x1,y1;//Top-left corner (x,y)
	int x2,y2;//Btm-right corner (x,y)
	int h,w;  //Height, width
	ClickPFN click;
	OverPFN over;
	button(int px1,int py1,unsigned ph,unsigned pw,
	       ClickPFN pclick,OverPFN pover);
	button(int px1,int py1,unsigned ph,unsigned pw,
	       ClickPFN pclick,OverPFN pover,DrawPFN pdraw);
		 //Constructors
	void check(int cx,int cy,int cb);
	void draw();
private:DrawPFN draw_button;
};

button::button(int px1,int py1,unsigned ph,unsigned pw,
	       ClickPFN pclick,OverPFN pover){
x1=px1;y1=py1;
x2=x1+pw;y2=y1+ph;
click=pclick;
over=pover;
h=y2-y1;w=x2-x1;
}

button::button(int px1,int py1,unsigned ph,unsigned pw,
	       ClickPFN pclick,OverPFN pover,DrawPFN pdraw){
x1=px1;y1=py1;
x2=x1+pw;y2=y1+ph;
click=pclick;
over=pover;
draw_button=pdraw;
h=y2-y1;w=x2-x1;
}

void button::check(int cx,int cy,int cb){
if(cx>x1&&cx<x2&&cy>y1&&cy<y2)
 {
 if(cb==0)(*over)();
  else(*click)(cb);
 }
}

void button::draw(){(*draw_button)(x1,y1,x2,y2);}