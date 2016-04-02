#include <math.h>
#include <stdio.h>
#include "wall.h"
#include "compoint.h"
#include "player.h"
#include "bomb.h"

#define absol(a) (((a)>0)?(a):(-(a)))


void AINEED::set(int __x,int __y, int _x,int _y,int _beflag,int _fright, int _fflag)
{
//num=absol(_x-__x)+absol(_y-__y);
num=0;/*
if(_fflag==2)
	num=200000;
if(_fflag==4)
	num=100000;*/
//x=(_x+__x)/2;
//y=(_y+__y)/2;
x=_x;
y=_y;
beflag=_beflag;
fright=_fright;
fflag=_fflag;
}
void AINEED::halfset(int __x,int __y, int _x,int _y,int _beflag,int _fright, int _fflag)
{
//num=absol(_x-__x)+absol(_y-__y);
num=0;/*
if(_fflag==2)
	num=200000;
if(_fflag==4)
	num=100000;*/
x=(_x+__x)/2;
y=(_y+__y)/2;
//x=_x;
//y=_y;
beflag=_beflag;
fright=_fright;
fflag=_fflag;
}


void AINEED::nextset(int _x,int _y)
{
//num+=absol(_x-befx)+absol(_y-befy);
befx=x;
befy=y;
x=_x;
y=_y;
beflag=1-beflag;
num+=100;
}

AAI::AAI()
{
si=0;
fi=0;
target=-1;
}
void AAI::setting(CWALL *wall,int WALL)
{

int i, j, k;
int top[100],le[100],ri[100],bot[100], temp;

for(k=0 ; k<WALL ; k++)
{
	lwall[k]=rwall[k]=twall[k]=bwall[k]=k;
	top[k]=wall[k].y()-wall[k].height()/2;
	le[k]=wall[k].x()-wall[k].width()/2;
	ri[k]=wall[k].x()+wall[k].width()/2;
	bot[k]=wall[k].y()+wall[k].height()/2;
}
for(i=0 ; i<WALL ; i++)
{
	for(j=i+1 ; j<WALL ; j++)
	{
		if(top[i]>top[j])
		{
			temp=top[i];
			top[i]=top[j];
			top[j]=temp;
			
			temp=twall[i];
			twall[i]=twall[j];
			twall[j]=temp;
		}
		if(bot[i]>bot[j])
		{
			temp=bot[i];
			bot[i]=bot[j];
			bot[j]=temp;
			
			temp=bwall[i];
			bwall[i]=bwall[j];
			bwall[j]=temp;
		}
		if(le[i]>le[j])
		{
			temp=le[i];
			le[i]=le[j];
			le[j]=temp;
			
			temp=lwall[i];
			lwall[i]=lwall[j];
			lwall[j]=temp;
		}
		if(ri[i]>ri[j])
		{
			temp=ri[i];
			ri[i]=ri[j];
			ri[j]=temp;
			
			temp=rwall[i];
			rwall[i]=rwall[j];
			rwall[j]=temp;
		}
	}
}
/*
for(k=0 ; k<WALL ; k++)
{
	for(i=wall[k].y()-wall[k].height()/2 ; i<=wall[k].y()+wall[k].height()/2 ; i+=15)
	{
		for(j=wall[k].y()-wall[k].height()/2 ; j<=wall[k].y()+wall[k].height()/2 ; j+=15)
		{
			if(i>0 && j>0)
			{
				basemap[i/15][j/15]=1;
			}
		}
	}
}*/
}

PLAYER::PLAYER()
{ 
ai=0;
head=300;
ccl=ccr=ccd=ccu=1;
bombtype=1;
bombdelay=0;
ropemlength=230;
ropespeed=1500;
maxpower=550;
apower=3000;
jumppower=450;
ropebase=15;
ropek=30;
openmouse=openrope=0;
radius=15;
energy=1000;
willenergy=1000;
mousex=mousey=0;
int i;
x=0;
y=0;
footx[0]=footy[0]=footx[1]=footy[1]=0;
vx=0;
vy=0;

for(i=0 ; i<255 ; i++)
keyboard[i]=0;
}

void PLAYER::ropesetup(double _mousex,double _mousey)
{
	ropex=x;
	ropey=y;
	ropelength=0;
	openmouse=1;
	openrope=0;
	mousex=_mousex;
	mousey=_mousey;
}

bool PLAYER::isropeing()
{
if(openmouse)
return 1;
return 0;
}


void PLAYER::mouse(double _mousex,double _mousey)
{
mousex=_mousex;
mousey=_mousey;
}


void PLAYER::com(int orr,double orrtime,double t1,double t2)
{
	ai->temp3[ai->fi]=0;
	ai->order[ai->fi]=orr;
	ai->ordertime[ai->fi]=orrtime;
	ai->temp1[ai->fi]=t1;
	ai->temp2[ai->fi]=t2;
	ai->fi++;
	ai->fi=ai->fi%100;
}

void PLAYER::comorder(double T)
{
	if(ai->si!=ai->fi)
	{
		if(ai->order[ai->si]=='A')
		{
			keyboard['A']=1;
		}
		if(ai->order[ai->si]=='D')
		{
			keyboard['D']=1;
		}
		if(ai->order[ai->si]>='1' && ai->order[ai->si]<='5' )
		{
			keyboard[ai->order[ai->si]]=1;
			ai->si++;
			ai->si=ai->si%100;
			return;
		}
		
		if(ai->order[ai->si]=='W')
		{
			if(ai->temp1[ai->si]==0)
				keyboard['W']=1;
			ai->temp1[ai->si]=1;
			ai->si++;
			ai->si=ai->si%100;
			return;
		}
		if(ai->order[ai->si]=='S')
		{
			keyboard['S']=1;
			mousex=ai->temp1[ai->si];
			mousey=ai->temp2[ai->si];
			ai->si++;
			ai->si=ai->si%100;
			return;
		}
		if(ai->order[ai->si]=='R')
		{	
			if(ai->temp3[ai->si]==0)
			{
				mousex=ai->temp1[ai->si];
				mousey=ai->temp2[ai->si];
				ropesetup(mousex,mousey);
				ai->temp3[ai->si]=1;
			}
			if(mousey>y)
				ai->ordertime[ai->si]=-1;
		}
		ai->ordertime[ai->si]-=T;
		if(ai->ordertime[ai->si]<0)
		{
			if(ai->order[ai->si]=='A')
				keyboard['A']=0;
			if(ai->order[ai->si]=='D')
				keyboard['D']=0;
			if(ai->order[ai->si]=='R')
				openmouse=0;
			ai->si++;
			ai->si=ai->si%100;
		}
	}
}

bool PLAYER::AIUPWALL(CWALL wall,bool right)
{
bool yes;
	int top, le, ri,bot;
double dx, dy;
	top=wall.y()-wall.height()/2;
	le=wall.x()-wall.width()/2;
	ri=wall.x()+wall.width()/2;
	bot=wall.y()+wall.height()/2;

yes=0;


	if(top>y+radius)
		return 0;
	if(!right && x+radius<ri)
		return 0;
	if(right && x-radius>le)
		return 0;
//////////////완전한 체킹//////////////
	double h;
dy=-1;
	if(right)
		dx=le-x;
	else if(!right)
		dx=ri-x;

	if(absol(dx*1.1)<radius)
		dx*=1.2;
	h=ropemlength*ropemlength-dx*dx;
	if(h<0)
		return 0;
	
	dy=sqrt(h);
	if(y-dy>bot)
		return 0;

	if(y-dy<top)
		dy=(y-top)*0.9;
		
	com('R',0.6,dx+x,y-dy);

//////////////////////////////////////

	double xxx=0;

	if(right)	xxx+=0.1;
	if(!right)	xxx-=0.1;
	else if(top>y-ropemlength/2)
		com('W',0.2,0,0);	
	if(xxx>0)
		com('D',xxx,0,0);
	else if(xxx<0)
		com('A',-xxx,0,0);
	return 1;
}

bool PLAYER::AITOP(CWALL wall,bool right)
{

	int top, le, ri,bot;
double dx, dy;
	top=wall.y()-wall.height()/2;
	le=wall.x()-wall.width()/2;
	ri=wall.x()+wall.width()/2;
	bot=wall.y()+wall.height()/2;

//////////////완전한 체킹//////////////
	double h;
dy=-1;
	if(x+radius<le)
		return 0;
	if(x-radius>ri)
		return 0;

	dy=y-bot;
	h=ropemlength*ropemlength-dy*dy;
	if(h<0)
		return 0;
	if(y+radius<bot)
		return 0;
	dx=sqrt(h);
	if(right && x+dx>ri)
	{
		dx=absol((ri-x)*0.9);
	}
	if(!right && x-dx<le)
	{
		dx=absol((x-le)*0.9);
	}

	dy*=1.2;
	if(right)	
		com('R',0.5,x+dx,y-dy);
	else
		com('R',0.5,x-dx,y-dy);

//////////////////////////////////////

	double xxx=0;
	if(right)	xxx+=0.1;
	if(!right)	xxx-=0.1;

	if(xxx>0)
		com('D',xxx,0,0);
	else if(xxx<0)
		com('A',-xxx,0,0);
	return 1;
}

bool PLAYER::AIBOT(CWALL wall,bool right)
{
	int top, le, ri,bot;
	top=wall.y()-wall.height()/2;
	le=wall.x()-wall.width()/2;
	ri=wall.x()+wall.width()/2;
	bot=wall.y()+wall.height()/2;

	if(y+radius<top)
		return 0;
	if(y-radius>bot)
		return 0;
	if(right && le<x+radius)
		return 0;
	if(!right && x-radius<ri)
		return 0;
	if(right)
		com('D',0.2,0,0);
	else
		com('A',0.2,0,0);
	return 1;
}
////////////////////can//////////////////////////

bool PLAYER::canwallup(CWALL wall,bool right, int x, int y)
{
	int top, le, ri,bot;
double dx, dy;
	top=wall.y()-wall.height()/2;
	le=wall.x()-wall.width()/2;
	ri=wall.x()+wall.width()/2;
	bot=wall.y()+wall.height()/2;
	if(top>y+radius)
		return 0;
	if(!right && x+radius<ri)
		return 0;
	if(right && x-radius>le)
		return 0;
	double h;
dy=-1;
	if(right)
		dx=le-x;
	else if(!right)
		dx=ri-x;

	if(absol(dx*1.1)<radius)
		dx*=1.2;
	h=ropemlength*ropemlength-dx*dx;
	if(h<0)
		return 0;
	
	dy=sqrt(h);
	if(y-dy>bot)
		return 0;

	return 1;
}

bool PLAYER::canwalltop(CWALL wall,bool right, int x, int y)
{

	int top, le, ri,bot;
double dx, dy;
	top=wall.y()-wall.height()/2;
	le=wall.x()-wall.width()/2;
	ri=wall.x()+wall.width()/2;
	bot=wall.y()+wall.height()/2;

//////////////완전한 체킹//////////////
	double h;
dy=-1;
	if(x+radius<le)
		return 0;
	if(x-radius>ri)
		return 0;

	dy=y-bot;
	h=ropemlength*ropemlength-dy*dy;
	if(h<0)
		return 0;
	if(y+radius<bot)
		return 0;
	return 1;
}

bool PLAYER::canwallmove(CWALL wall,bool right, int x, int y)
{
	int top, le, ri,bot;
	top=wall.y()-wall.height()/2;
	le=wall.x()-wall.width()/2;
	ri=wall.x()+wall.width()/2;
	bot=wall.y()+wall.height()/2;
	if(y<top)
		return 0;
	if(y>bot)
		return 0;
	if(right && le<x)
		return 0;
	if(!right && x<ri)
		return 0;
	return 1;
}
/////////////////////////
bool PLAYER::wantup(CWALL *wall, int WALL, bool right)
{
	int i;
	
	if(right){
		for(i=0 ; i<WALL ; i++)
			if(AIUPWALL(wall[ai->lwall[i]],right))
				return 1;
	}
	else if(!right)	{
		for(i=WALL-1 ; i>=0 ; i--)
			if(AIUPWALL(wall[ai->rwall[i]],right))
				return 1;
	}
	return 0;
}


bool PLAYER::wanttop(CWALL *wall, int WALL, bool right)
{
	int i;
	
	if(right){
		for(i=0 ; i<WALL ; i++)
			if(AITOP(wall[ai->lwall[i]],right))
				return 1;
	}
	else if(!right)	{
		for(i=WALL-1 ; i>=0 ; i--)
			if(AITOP(wall[ai->rwall[i]],right))
				return 1;
	}
	return 0;
}
bool PLAYER::wantmove(CWALL *wall, int WALL, bool right)
{
	int i;
	
	if(right){
		for(i=0 ; i<WALL ; i++)
			if(AIBOT(wall[ai->lwall[i]],right))
				return 1;
	}
	else if(!right)	{
		for(i=WALL-1 ; i>=0 ; i--)
			if(AIBOT(wall[ai->rwall[i]],right))
				return 1;
	}
	return 0;
}
/////////////////can/////////////////////////

int PLAYER::canup(CWALL *wall, int WALL, bool right, int x, int y)
{
	int i;
	
	if(right){
		for(i=0 ; i<WALL ; i++)
			if(canwallup(wall[ai->lwall[i]],right,x,y))
				return ai->lwall[i];
	}
	else if(!right)	{
		for(i=WALL-1 ; i>=0 ; i--)
			if(canwallup(wall[ai->rwall[i]],right,x,y))
				return ai->rwall[i];
	}
	return -1;
}


int PLAYER::cantop(CWALL *wall, int WALL, bool right,int x,int y)
{
	int i;
	
	if(right){
		for(i=0 ; i<WALL ; i++)
			if(canwalltop(wall[ai->lwall[i]],right,x,y))
				return ai->lwall[i];//canmove(wall,WALL,right,x,y);
	}
	else if(!right)	{
		for(i=WALL-1 ; i>=0 ; i--)
			if(canwalltop(wall[ai->rwall[i]],right,x,y))
				return ai->rwall[i];//canmove(wall,WALL,right,x,y);
	}
	return -1;
}
int PLAYER::canmove(CWALL *wall, int WALL, bool right,int x,int y)
{
	int i;
	
	if(right){
		for(i=0 ; i<WALL ; i++)
			if(canwallmove(wall[ai->lwall[i]],right,x,y))
				return ai->lwall[i];
	}
	else if(!right){
		for(i=WALL-1 ; i>=0 ; i--)
			if(canwallmove(wall[ai->rwall[i]],right,x,y))
				return ai->rwall[i];
	}
	return -1;
}

int PLAYER::candown(CWALL *wall, int WALL,int x, int y)
{
	int i;
	
	for(i=0 ; i<WALL ; i++)
		if(canwalldown(wall[ai->twall[i]],x,y))
			return ai->twall[i];
	return -1;
}

bool PLAYER::canwalldown(CWALL wall, int x, int y)
{
	int top, le, ri,bot;
	top=wall.y()-wall.height()/2;
	le=wall.x()-wall.width()/2;
	ri=wall.x()+wall.width()/2;
	bot=wall.y()+wall.height()/2;

	if(y>top)
		return 0;
	if(ri<x-radius)
		return 0;
	if(x+radius<le)
		return 0;
	return 1;
}

AINEED PLAYER::whatiwant(CWALL *wall,int WALL)
{
AINEED *que=new AINEED[head+50];
int rear,front, rr, i;
int min;
AINEED mini;
mini.fflag=0;
rear=0;
front=0;
min=999999;


//void AINEED::set(int _x,int _y,int _beflag,int _num,int _fright, int _fflag)
rr=canup(wall,WALL,1,x,y);
if(rr != -1)
{
front++;
que[front].set(x,y,x,wall[rr].top()-radius,0,1,1);
front++;
que[front].halfset(x,y,x,wall[rr].top()-radius,0,1,1);
}
rr=canup(wall,WALL,0,x,y);
if(rr != -1)
{
front++;
que[front].set(x,y,x,wall[rr].top()-radius,0,0,1);
front++;
que[front].halfset(x,y,x,wall[rr].top()-radius,0,0,1);
}

//void AINEED::set(int _x,int _y,int _beflag,int _num,int _fright, int _fflag)
rr=cantop(wall,WALL,1,x,y);
if(rr != -1)
{
front++;
que[front].set(x,y,wall[rr].ri()+radius,wall[rr].bot()+radius,1,1,3);
front++;
que[front].halfset(x,y,wall[rr].ri()+radius,wall[rr].bot()+radius,1,1,3);
}
rr=cantop(wall,WALL,0,x,y);
if(rr != -1)
{
front++;
que[front].set(x,y,wall[rr].le()-radius  ,wall[rr].bot()+radius,1,0,3);
front++;
que[front].halfset(x,y,wall[rr].le()-radius  ,wall[rr].bot()+radius,1,0,3);
}
//void AINEED::set(int _x,int _y,int _beflag,int _num,int _fright, int _fflag)
rr=canmove(wall,WALL,1,x,y);
if(rr != -1)
{
front++;
que[front].set(x,y,wall[rr].le()-radius ,y,1,1,4);
front++;
que[front].halfset(x,y,wall[rr].le()-radius ,y,1,1,4);
}
rr=canmove(wall,WALL,0,x,y);
if(rr != -1)
{
front++;
que[front].set(x,y,wall[rr].ri()+radius ,y,1,0,4);
front++;
que[front].halfset(x,y,wall[rr].ri()+radius ,y,1,0,4);
}
//void AINEED::set(int _x,int _y,int _beflag,int _num,int _fright, int _fflag)
rr=candown(wall,WALL,x,y);
if(rr != -1)
{
front++;
que[front].set(x,y,x,wall[rr].top()-radius,0,1,2);
front++;
que[front].halfset(x,y,x,wall[rr].top()-radius,0,1,2);
}
for(i=1 ; i<=front ; i++)
{
	que[i].befx=x;
	que[i].befy=y;
}
int ff=front;
	do{
		rear++;
		if(front>head)
			break;
		rr=potdistance(wall,WALL,que[rear].befx,que[rear].befy,que[rear].x,que[rear].y, ((PLAYER *)ai->tar)->x,((PLAYER *)ai->tar)->y);
		if(rr+que[rear].num<min)
		{
			mini=que[rear];
			min=rr+que[rear].num;
		}
			rr=canup(wall,WALL,1,que[rear].x,que[rear].y);
			if(rr != -1)
			{
			front++;
			que[front]=que[rear];
			que[front].nextset(que[rear].x,wall[rr].top()-radius);
			front++;
			que[front]=que[rear];
			que[front].nextset((que[rear].x+que[rear].x)/2,(wall[rr].top()-radius+que[rear].y)/2);
			}
			rr=canup(wall,WALL,0,que[rear].x,que[rear].y);
			if(rr != -1)
			{
			front++;
			que[front]=que[rear];
			que[front].nextset(que[rear].x,wall[rr].top()-radius);
			front++;
			que[front]=que[rear];
			que[front].nextset((que[rear].x+que[rear].x)/2,(wall[rr].top()-radius+que[rear].y)/2);
			}
			rr=candown(wall,WALL,que[rear].x,que[rear].y);
			if(rr != -1)
			{
			front++;
			que[front]=que[rear];
			que[front].nextset(que[rear].x,wall[rr].top()-radius);
			front++;
			que[front]=que[rear];
			que[front].nextset((que[rear].x+que[rear].x)/2,(wall[rr].top()-radius+que[rear].y)/2);
			}
			rr=cantop(wall,WALL,1,que[rear].x,que[rear].y);
			if(rr != -1)
			{
			front++;
			que[front]=que[rear];
			que[front].nextset(wall[rr].ri()+radius,wall[rr].bot()+radius);
			front++;
			que[front]=que[rear];
			que[front].nextset((wall[rr].ri()+radius+que[rear].x)/2 ,(wall[rr].bot()+radius+que[rear].y)/2);
			}

			rr=cantop(wall,WALL,0,que[rear].x,que[rear].y);
			if(rr != -1)
			{
			front++;
			que[front]=que[rear];
			que[front].nextset(wall[rr].le()-radius ,wall[rr].bot()+radius);
			front++;
			que[front]=que[rear];
			que[front].nextset((wall[rr].le()-radius +que[rear].x)/2,(wall[rr].bot()+radius+que[rear].y)/2);
			}
			rr=canmove(wall,WALL,1,que[rear].x,que[rear].y);
			if(rr != -1)
			{
			front++;
			que[front]=que[rear];
			que[front].nextset(wall[rr].le()-radius ,que[rear].y);
			front++;
			que[front]=que[rear];
			que[front].nextset((wall[rr].le()-radius+que[rear].x)/2,que[rear].y);
			}
			rr=canmove(wall,WALL,0,que[rear].x,que[rear].y);
			if(rr != -1)
			{
			front++;
			que[front]=que[rear];
			que[front].nextset(wall[rr].ri()+radius ,que[rear].y);
			front++;
			que[front]=que[rear];
			que[front].nextset((wall[rr].ri()+radius+que[rear].x)/2,que[rear].y);
			}
	}while(rear!=front);
return mini;
}

int PLAYER::potdistance(CWALL *wall,int WALL,int x1,int y1,int x2,int y2,int x, int y)
{
	int temp, i;
	int top, le, ri,bot;
	if(absol(x1-x2)<absol(y1-y2))
		x1=x2=(x1+x2)/2;
	else y1=y2=(y1+y2)/2;
	if(y2<y1)
	{
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if(x2<x1)
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}
	if(y1==y2 && x1-radius<x && x<x2+radius)
	{
		//y, y1 까지 막혀진거 체크
		if(y>y1) //y가 더 아래쪽에 있다면
		{
			temp=y1;
			y1=y;
			y=temp;
		}
		for(i=0 ; i<WALL ; i++)
		{	
			if(wall[i].y()>y && wall[i].y() <y1)
			{
				le=wall[i].x()-wall[i].width()/2;
				ri=wall[i].x()+wall[i].width()/2;
				if(le<x && ri>x)
					return 999999;
			}
		}
		return absol(y-y1);
	}
	if(x1==x2 && y1-radius<y && y<y2+radius)
	{

		//x, x1 까지 막혀진거 체크
		if(x>x1) //x가 더 아래쪽에 있다면
		{
			temp=x1;
			x1=x;
			x=temp;
		}
		for(i=0 ; i<WALL ; i++)
		{	
			if(wall[i].x()>x && wall[i].x() <x1)
			{
				top=wall[i].y()-wall[i].height()/2;
				bot=wall[i].y()+wall[i].height()/2;
				if(top<y && bot>y)
					return 999999;
			}
		}
		return absol(x-x1);
	}
	return 999999;
}
