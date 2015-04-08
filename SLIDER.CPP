typedef void (*SliderDrawPFN)(int,int,int,int,int,int,char);
//void drw(int x1,int y1,int len,int wid,int step,int pos,char h_or_v)

class slider{
public: void check(int mx,int my,int mb);
	void draw(){(*draw_slider)(x1,y1,len,wid,step,pos,h_or_v);};
	int pos;
	//
	slider(int px1,int py1,int plen,int pwid,
	       int pstep,int ppos,char phorv,SliderDrawPFN pd);
private: void handle(int mx,int my,int mb);
	 int x1,y1,len,wid,step;
	 char h_or_v;
	 SliderDrawPFN draw_slider;
};

slider::slider(int px1,int py1,int plen,int pwid,
	       int pstep,int ppos,char phorv,SliderDrawPFN pd){
x1=px1,y1=py1;
len=plen,wid=pwid;
if(pstep>=1)step=pstep;
 else step=1;
if(ppos>=0&&ppos<len)pos=ppos;
 else pos=0;
h_or_v=phorv;
draw_slider=pd;
}

void slider::check(int mx,int my,int mb){
if(mb!=0)
 if(mx>=x1&&my>=y1)
  switch(h_or_v)
   {
   case 'h':if(mx<x1+len&&my<y1+wid)
	     {
	     handle(mx,my,mb);
	     }
	    break;
   case 'v':if(mx<x1+wid&&my<y1+len)
	     {
	     handle(mx,my,mb);
	     }
	    break;
   }
}

void slider::handle(int mx,int my,int mb){
mb;
switch(h_or_v)
 {
 case 'h':pos=(mx-x1)*step;
	  break;
 case 'v':pos=(my-y1)*step;
	  break;
 }
draw();
}