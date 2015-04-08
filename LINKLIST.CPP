class node{
public: int x;
	friend void linkto(node x);
	node operator =(int v){x=v;return *this;}
	node operator ++(){return *fwd;}
	friend node operator +=(node i,int n);
private: node *fwd,*back;

};

node operator +=(node i,int n){node w;
for(;n!=0;n++)
 {
 w.fwd=i.fwd;
 }
return i;}