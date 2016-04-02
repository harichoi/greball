#include <QApplication>
#include <QTimer>
#include <QTime>
#include <QPaintEvent>
#include <QPainter>
#include <math.h>
#include "playwidget.h"
#define G 800
#define MAXPOWER player[k].maxpower
#define APOWER player[k].apower
#define JUMPPOWER player[k].jumppower
#define ROPEBASE player[k].ropebase
#define ROPEK player[k].ropek
#define ROPELENGTH player[k].ropemlength
#define ROPESPEED player[k].ropespeed
#define ROPERADIUS 5
#define nowx ((QCursor::pos().x())-wx+gx)
#define nowy ((QCursor::pos().y())-wy+gy)
#define BOMBMAX 100
#define GIZOON 0.1
#define absol(a) (((a)>0)?(a):(-(a)))
#define NORMAL 0
#define DIE 1
#define CANBR 2
int ME=0;
int GE;


playwidget::playwidget()
{
int i;
////////////널 세팅////////////
NP=100;
bomb=new BOMB[BOMBMAX];
gx=0;gy=0;
wx=0,wy=0;
////////////타임 세팅/////////////////

timer=new QTimer();
timer->start(10);
time=new QTime();
time->start();
connect(timer,SIGNAL(timeout()),this,SLOT(timefuc()));
resize(800,600);
/////////////wall(맵)///////////////
fileload();
}

void playwidget::timefuc()
{
/////////////변수 선언//////////////
int i, k;
////////////기준///////////////////
gx+=(player[GE].x-gx-400)*GIZOON;
gy+=(player[GE].y-gy-300)*GIZOON;
////////////타임 셋팅///////////////
double T=time->elapsed()/1000.0;
//T=T/5;
time->start();

player[ME].mousex=nowx;
player[ME].mousey=nowy; 


///////////////컴퓨터//////////////
for(i=0 ; i<NP ; i++)
{
	if(!player[i].ai)
	{
		player[i].ai=new AAI();
		player[i].ai->setting(wall,WALL);
	}
	if(i!=ME && player[i].energy>0)
	{
		AI(i,T);
	}
}
//////////////bomb 상호작용//////////////

for(i=0 ; i<BOMBMAX ; i++)
{
//유저들끼리
	if(bomb[i].flag>0)
	{
		bomb[i].cal(T);
		for(k=0 ; k<NP ; k++)
		{
			if(iscrush(player[k].x,player[k].y,bomb[i].x,bomb[i].y,player[k].radius+bomb[i].radius) &&  bomb[i].player->number!=k)
			{
				player[k].vx+=bomb[i].vx;
				if(player[k].ccd)
				player[k].vy+=bomb[i].vy;
				else
				player[k].vy-=bomb[i].vy;
				if(bomb[i].flag==4)
				{
					player[k].willenergy-=(200+absol(bomb[i].vx)+absol(bomb[i].vy))*0.5;
				}
				else if(bomb[i].flag==1)
				{
					player[k].willenergy-=(150+3*absol(bomb[i].vx)+3*absol(bomb[i].vy))*0.5;
				}
				else if(bomb[i].flag==2)
				{
					player[k].willenergy-=(30)*0.5;
				}
				else if(bomb[i].flag==5)
				{
					player[k].willenergy-=(300)*0.5;
				}
				bomb[i].flag=0;
			}
		}

//벽

		for(k=0 ; k<WALL ; k++)
		{
			if(isin(wall[k],bomb[i].x,bomb[i].y))
			{
				if(wall[k].type==CANBR)
				{
					wall[k].setWidth(0),wall[k].setHeight(0);//wall[k].width()/5*4),wall[k].setHeight(wall[k].height()/5*4);
					wall[k].setX(0);wall[k].setY(0);
				}
				if(bomb[i].flag!=1)
					bomb[i].flag=0;
			}
		}
	}
}
for(k=0 ; k<NP ; k++){
if(player[k].energy>0)
usermove(k,T/3*2);
}


///////////업데이트/////////////////
update();
}
int ee;
void playwidget::paintEvent(QPaintEvent *a)
{
	int i, k;
	QPainter pa(this);
//////////////Bg Print///////////////////////////////
	pa.setBrush(QBrush("#6666ff",Qt::SolidPattern));
	pa.drawRect(0,0,1024,768);
QPixmap pix2("sun.gif");
pa.drawPixmap(-gx/40,-gy/40,pix2);
QPixmap pix3("back.gif");
pa.drawPixmap(-gx/10,-gy/10,pix3);

//QPixmap pix("map1.gif");
//pa.drawPixmap(-gx,-gy,pix);

//////////////////Bomb Draw////////////////////////
for(i=0 ; i<BOMBMAX ; i++)
{

if(bomb[i].flag==2)
{
	pa.setPen(Qt::NoPen);
	pa.setBrush(Qt::green);
	pa.drawEllipse(bomb[i].x-5-gx,bomb[i].y-5-gy,10,10);
}
if(bomb[i].flag==4)
{
	pa.setPen(Qt::NoPen);
	pa.setBrush(Qt::red);
	pa.drawEllipse(bomb[i].x-10-gx,bomb[i].y-10-gy,20,20);
}

if(bomb[i].flag==5)
{
	QPen a;
	a.setWidth(7);
	a.setColor("#0000ff");
	pa.setPen(a);
	pa.drawLine(bomb[i].player->x-gx,bomb[i].player->y-gy,bomb[i].x-10-gx,bomb[i].y-10-gy);
	a.setWidth(1);
	pa.setPen(a);
}
if(bomb[i].flag==1)
{
	double X,Y, R;
	X=bomb[i].player->x-gx;
	Y=bomb[i].player->y-gy;
	R=bomb[i].player->radius;
pa.translate(X,Y);
		pa.setPen(Qt::black);
		pa.setBrush(Qt::blue);
		double ag=-bomb[i].angle;

		if(bomb[i].right){
			pa.rotate(ag/3.141592*180);
			pa.drawRect(QRect(-R,-R/4-R/7,R,R/2));
			pa.drawRect(QRect(R,-R+R/7,R*6/4,R*2.5));
			pa.rotate(-ag/3.141592*180);
		}
		if(!bomb[i].right){
ag=3.141592-ag;
			pa.rotate(ag/3.141592*180);
			pa.drawRect(QRect(-R, -( -R/4-R/7 ),R,-(R/2)));
			pa.drawRect(QRect(R,-(-R+R/7),R*6/4,-(R*2.5)));
			pa.rotate(-ag/3.141592*180);
		}
pa.translate(-X,-Y);
}
}
////////////////////////////////////////////////////

/////////////////////WALL Draw//////////////////

      //  pa.setBrush(gradient1);
	for(i=0 ; i<WALL ; i++)
	{
		if(wall[i].x()-wall[i].width()/2-gx>1024)
			continue;
		if(wall[i].x()+wall[i].width()/2-gx<0)
			continue;
		if(wall[i].y()-wall[i].height()/2-gy>768)
			continue;
		if(wall[i].y()+wall[i].height()/2-gy<0)
			continue;
	pa.setPen(Qt::NoPen);
	if(wall[i].type==NORMAL)
	pa.setBrush(Qt::green);
//	else if(wall[i].type==DIE)
//	pa.setBrush(QBrush("#ff7777",Qt::SolidPattern));
//	else if(wall[i].type==CANBR)
//	pa.setBrush(Qt::yellow);
//QLinearGradient gradient1(0,0,1000,1000);
    //    gradient1.setColorAt(0.0, Qt::blue);
//	gradient1.setColorAt(0.5, Qt::red);
//        gradient1.setColorAt(1.0, Qt::yellow);
	pa.drawRect(QRect(wall[i].x()-wall[i].width()/2-gx,wall[i].y()-wall[i].height()/2-gy,wall[i].width(),wall[i].height()));
	}
////////////////여기까지/////////////////////
	pa.setPen(Qt::black);
	pa.setBrush(QBrush("#6666ff",Qt::SolidPattern));
	pa.drawRect(0,0,100,100);
	gx-=45*50;
	gy-=45*50;
	for(i=0 ; i<WALL ; i++)
	{
	if(wall[i].type==NORMAL)
	pa.setBrush(Qt::black);
	else if(wall[i].type==DIE)
	pa.setBrush(Qt::red);
	else if(wall[i].type==CANBR)
	pa.setBrush(Qt::yellow);
	int ppx,ppy;
	ppx=(wall[i].x()-gx)/50;
	ppy=(wall[i].y()-gy)/50;
	if(ppx<100 && ppy<100 && ppx>0 && ppy>0)
	{
	pa.drawRect(QRect((wall[i].x()-wall[i].width()/2-gx)/50,(wall[i].y()-wall[i].height()/2-gy)/50,(wall[i].width())/50,(wall[i].height())/50));
	}
	}
	pa.setPen(Qt::white);
	pa.drawPoint((player[ME].x-gx)/50,(player[ME].y-gy)/50);
	pa.drawPoint((player[ME].x-gx)/50,(player[ME].y-gy)/50+1);
	pa.drawPoint((player[ME].x-gx)/50+1,(player[ME].y-gy)/50);
	pa.drawPoint((player[ME].x-gx)/50+1,(player[ME].y-gy)/50+1);
	for(i=0 ; i<NP ; i++){
		if(i==ME)continue;
	if(player[i].energy>0){
	pa.setPen(Qt::green);
	pa.drawPoint((player[i].x-gx)/50,(player[i].y-gy)/50);
	pa.drawPoint((player[i].x-gx)/50,(player[i].y-gy)/50+1);
	pa.drawPoint((player[i].x-gx)/50+1,(player[i].y-gy)/50);
	pa.drawPoint((player[i].x-gx)/50+1,(player[i].y-gy)/50+1);
	}
	}
	gx+=45*50;
	gy+=45*50;

/////////////////////////////////////////////////////
////////////// BombWait Draw///////////////////////////////
player[ME].mousex=nowx;
player[ME].mousey=nowy;
for(k=0 ; k<NP ; k++){
	if(player[k].energy>0){
//로프발사부분
	if(player[k].openmouse){
			pa.setPen(Qt::NoPen);
			for(i=1 ; i<=20 ; i++)
			{
				if(i%2==0)
					pa.setBrush(Qt::black);
				else 
					pa.setBrush(Qt::gray);
				int ppx,ppy;
				ppx=(player[k].ropex-player[k].x)/20*i+player[k].x-gx;
				ppy=(player[k].ropey-player[k].y)/20*i+player[k].y-gy;
				pa.drawEllipse(ppx-5,ppy-5,10,10);
			}
		}
///////////////
	double CR,SR,X,Y, R, ag;
	X=player[k].x-gx;
	Y=player[k].y-gy;

	ag=atan((player[k].mousey-player[k].y)/(player[k].mousex-player[k].x));
if(player[k].mousex-player[k].x<0)
			ag+=3.141592;
	CR=player[k].radius*cos(ag);
	SR=player[k].radius*sin(ag);
	if(player[k].bombtype==1 && player[k].bombdelay<=0)
	{
		pa.translate(X,Y);
		pa.setPen(Qt::black);
		pa.setBrush(Qt::blue);
		double ag=-3.141592/3;

		R=player[k].radius;
		if(player[k].mousex-player[k].x<0){
			pa.rotate(ag/3.141592*180);
			pa.drawRect(QRect(-R,-R/4-R/7,R,R/2));
			pa.drawRect(QRect(R,-R+R/7,R*6/4,R*2.5));
			pa.rotate(-ag/3.141592*180);
		}
		if(player[k].mousex-player[k].x>0){
			pa.rotate(-ag/3.141592*180);
			pa.drawRect(QRect(R,-R/4-R/7,-R,R/2));
			pa.drawRect(QRect(-R,-R+R/7,-R*6/4,R*2.5));
			pa.rotate(ag/3.141592*180);
		}
pa.translate(-X,-Y);
	}
	if(player[k].bombtype==4)
	{
		pa.setPen(Qt::black);
		pa.setBrush(Qt::blue);
		QPolygon poly;

		if(player[k].mousex-player[k].x<0)
			ag+=3.141592;
		poly<<QPoint(X+SR/3,Y-CR/3)<<QPoint(X-SR/3,Y+CR/3)<<QPoint(X+2*CR-SR/3,Y+2*SR+CR/3)<<QPoint(X+2*CR+SR/3,Y+2*SR-CR/3);
		pa.drawPolygon(poly);
	}
////////////////////////////////////////////////////

////////////////User Draw/////////////////////////
	

	pa.setPen(Qt::white);
	pa.setBrush(Qt::blue);
	pa.drawRect(player[k].x-player[k].energy/40-gx,player[k].y+player[k].radius-gy,player[k].energy/20,5);




	pa.setPen(Qt::black);
	pa.setBrush(Qt::yellow);
	pa.drawEllipse(player[k].footx[0]-player[k].radius/2-gx, player[k].footy[0]-player[k].radius/2-gy,player[k].radius,player[k].radius);
	if(player[k].isimage==0){

QLinearGradient gradient(player[k].x-player[k].radius-gx,player[k].y-player[k].radius-gy,player[k].x+player[k].radius-gx,player[k].y+player[k].radius-gy);
        gradient.setColorAt(0.0, "#ffff00");
        gradient.setColorAt(1.0, "#aaaaaa");
        pa.setBrush(gradient);
		pa.setPen(Qt::black);
		pa.setBrush(Qt::yellow);
		pa.drawEllipse(player[k].x-player[k].radius-gx,player[k].y-player[k].radius-gy,player[k].radius*2,player[k].radius*2);
	}
	else	{
		QPixmap us(player[k].filename);
		pa.drawPixmap(player[k].x-player[k].radius-gx,player[k].y-player[k].radius-gy,us);
	}

	pa.setPen(Qt::black);
	pa.setBrush(Qt::yellow);
	pa.drawEllipse(player[k].footx[1]-player[k].radius/2-gx, player[k].footy[1]-player[k].radius/2-gy,player[k].radius,player[k].radius);

	ag=atan((player[k].mousey-player[k].y)/(player[k].mousex-player[k].x));
		if(player[k].mousex-player[k].x<0)
			ag+=3.141592;


	CR=player[k].radius*cos(ag);
	SR=player[k].radius*sin(ag);
	pa.setBrush(Qt::black);
	pa.drawEllipse(player[k].x+CR/5*4-player[k].radius/3.75-gx,player[k].y-player[k].radius/2+SR/5-gy,player[k].radius/7.5,player[k].radius/5*3);
	pa.drawEllipse(player[k].x+CR/5*4+player[k].radius/3.75-gx,player[k].y-player[k].radius/2+SR/5-gy,player[k].radius/7.5,player[k].radius/5*3);
	}
}

}
void playwidget::keyPressEvent(QKeyEvent *a)
{
	if(a->key()>255 || a->key()<0)
		return;
	player[ME].keyboard[a->key()]=1;
}

void playwidget::keyReleaseEvent(QKeyEvent *a)
{
	if(a->key()>255 || a->key()<0)
		return;
player[ME].keyboard[a->key()]=0;
}

bool playwidget::canright(QRect rect,double xx, double yy,double xxx, double yyy, double rad)
{
rad*=1.414/2;
if(absol(rect.y()-yy)<rect.height()/2+rad)
{
if(xx+rad<rect.x()-rect.width()/2 && xxx+rad>rect.x()-rect.width()/2)
{
return 0;
}
}
return 1;
}

bool playwidget::canup(QRect rect,double xx, double yy,double xxx, double yyy, double rad)
{
rad*=1.414/2;
if(absol(rect.x()-xx)<rect.width()/2+rad)
{
if(yy-rad>rect.y()+rect.height()/2 && yyy-rad<rect.y()+rect.height()/2)
{
return 0;
}
}
return 1;
}
bool playwidget::candown(QRect rect,double xx, double yy,double xxx, double yyy, double rad)
{
rad*=1.414/2;
if(absol(rect.x()-xx)<rect.width()/2+rad)
{
if(yy+rad<rect.y()-rect.height()/2 && yyy+rad>rect.y()-rect.height()/2)
{
return 0;
}
}
return 1;
}
bool playwidget::canleft(QRect rect,double xx, double yy,double xxx, double yyy, double rad)
{
rad*=1.414/2;
if(absol(rect.y()-yy)<rect.height()/2+rad)
{
if(xx-rad>rect.x()+rect.width()/2 && xxx-rad<rect.x()+rect.width()/2)
{
return 0;
}
}
return 1;
}

void playwidget::mousePressEvent(QMouseEvent *a)
{
wx=QCursor::pos().x()-a->x();
wy=QCursor::pos().y()-a->y();
if(a->buttons()==Qt::RightButton)
{
player[ME].ropesetup(gx+a->x(),gy+a->y());
}
}


void playwidget::mouseReleaseEvent(QMouseEvent *a)
{
if(a->buttons()!=Qt::LeftButton){
player[ME].openmouse=0;
}
}


void playwidget::mouseMoveEvent(QMouseEvent *a)
{
if(a->buttons()==Qt::RightButton)
{
player[ME].mouse(gx+a->x(),gy+a->y());
}
}

bool playwidget::isin(QRect rect,double xx,double yy)
{
if(absol(rect.y()-yy)<rect.height()/2)
{
if(absol(rect.x()-xx)<rect.width()/2)
{
return 1;
}
}
return 0;

}



bool playwidget::iscrush(double xx,double yy, double xxx, double yyy, double rad)
{
	if(hypot(xxx-xx,yyy-yy)<=rad)
		return 1;
	return 0;
}
void playwidget::AI(int num,double T)
{
int i;
	if(!player[num].ai->tar){
		for(i=1 ; i<=NP ; i++){
			int dd=rand()%NP;
			if(player[dd].energy>0)
			{
				player[num].ai->tar=&player[dd];
				break;
			}
		}
	}
	if(!player[num].ai->tar)
		return;
	if(((PLAYER *)player[num].ai->tar)->energy<=0)
	{
		player[num].ai->tar=0;
		return;
	}
	
	if(rand()%100==0)
		player[num].com(rand()%5+'1',0.1,0,0);

	PLAYER *tar=(PLAYER *)player[num].ai->tar;
	if(absol(player[num].x-tar->x)<=400 && absol(player[num].y-tar->y)<=300)
		player[num].com('S',0.1,tar->x,tar->y);

	if(absol(player[num].ai->si-player[num].ai->fi)<=0)
	{
		AINEED rcv=player[num].whatiwant(wall,WALL);
		if(rcv.fflag==1) player[num].wantup(wall,WALL,rcv.fright);
		//if(rcv.fflag==3) 
		if(rcv.fflag==4) if(!player[num].wanttop(wall,WALL,rcv.fright)) player[num].wantmove(wall,WALL,rcv.fright);
	}
	player[num].comorder(T);
}


void playwidget::filesave()
{
FILE *file=fopen("greball.txt","wb");
int sztu,sztw;
sztu=sizeof(PLAYER);
sztw=sizeof(CWALL);
fwrite(&NP,sizeof(int),1,file);
fwrite(&WALL,sizeof(int),1,file);
fwrite(&placerandom,sizeof(bool),1,file);
fwrite(&sztu,sizeof(int),1,file);
fwrite(&sztw,sizeof(int),1,file);
fwrite(mapfile,sizeof(char),256,file);
fwrite(player,sztu,NP,file);
fwrite(wall,sztw,WALL,file);
fclose(file);
}

void playwidget::fileload()
{
FILE *file=fopen("greball.txt","rb");
int sztu,sztw;
fread(&NP,sizeof(int),1,file);
fread(&WALL,sizeof(int),1,file);
fread(&placerandom,sizeof(bool),1,file);
player=new PLAYER[NP+1];
wall=new CWALL[WALL+1];
fread(&sztu,sizeof(int),1,file);
fread(&sztw,sizeof(int),1,file);
fread(mapfile,sizeof(char),256,file);
fread(player,sztu,NP,file);
fread(wall,sztw,WALL,file);
fclose(file);
int i;
for(i=0 ; i<NP ; i++)
{
	player[i].number=i;
}
}

void playwidget::usermove(int k,double T)
{
	int i;
	//로프발사
	player[k].footvx[0]+=(player[k].x-player[k].radius*0.6-player[k].footx[0])*30*T;
	player[k].footvy[0]+=(player[k].y+player[k].radius*0.6-player[k].footy[0])*30*T;
	player[k].footvx[1]+=(player[k].x+player[k].radius*0.6-player[k].footx[1])*30*T;
	player[k].footvy[1]+=(player[k].y+player[k].radius*0.6-player[k].footy[1])*30*T;
	player[k].footvx[0]*=0.7;
	player[k].footvy[0]*=0.7;
	player[k].footvx[1]*=0.7;
	player[k].footvy[1]*=0.7;
	player[k].footx[0]+=player[k].footvx[0];
	player[k].footy[0]+=player[k].footvy[0];
	player[k].footx[1]+=player[k].footvx[1];
	player[k].footy[1]+=player[k].footvy[1];


	player[k].energy+=(player[k].willenergy-player[k].energy)*0.1*T;
	if(player[k].keyboard['1'])
	{
		player[k].bombtype=1;
		player[k].keyboard['1']=0;
	}
	if(player[k].keyboard['2'])
	{
		player[k].bombtype=2;
		player[k].keyboard['2']=0;
	}
	if(player[k].keyboard['3'])
	{
		player[k].bombtype=3;
		player[k].keyboard['3']=0;
	}
	if(player[k].keyboard['4'])
	{
		player[k].bombtype=4;
		player[k].keyboard['4']=0;
	}
	if(player[k].keyboard['5'])
	{
		player[k].bombtype=5;
		player[k].keyboard['5']=0;
	}
	if(player[k].keyboard['A'])
	{
		if(player[k].vx>-MAXPOWER)
			player[k].vx-=APOWER*T;
	}
	if(player[k].keyboard['D'])
	{
		if(player[k].vx<MAXPOWER)
			player[k].vx+=APOWER*T;
	}
	if(player[k].keyboard['G'])
	{
		GE++;
		GE%=NP;
		player[k].keyboard['G']=0;
	}
	player[k].jump=0;
	if(player[k].keyboard['W']){
		player[k].jump=1;
		player[k].keyboard['W']=0;
	}
	if(player[k].keyboard['S'])
	{
		////미사일발사////
		player[k].keyboard['S']=0;
		for(i=0 ; i<BOMBMAX ; i++)
			if(bomb[i].setting(&player[k]))
				break;
	}
	player[k].bombdelay-=T;//봄브딜레이
///////////로프발사
	if(player[k].openmouse && !player[k].openrope)
	{
		player[k].ropelength+=ROPESPEED*T;
		if(player[k].ropelength>ROPELENGTH)
		{
			player[k].openmouse=0;
		}
		double mmx,mmy;
		mmx=player[k].mousex;
		mmy=player[k].mousey;
		double angle, xsi, ysi;
		angle=atan((mmy-player[k].y)/(mmx-player[k].x));
		if(mmx-player[k].x<0)
			angle+=3.141592;
		xsi=player[k].ropelength*cos(angle);
		ysi=player[k].ropelength*sin(angle);
		player[k].ropex=player[k].x+xsi;
		player[k].ropey=player[k].y+ysi;
	}
	///로프열기
	for(i=0 ; i<WALL ; i++){
		if(isin(wall[i],player[k].ropex,player[k].ropey) && player[k].openmouse)
		{
			player[k].openrope=1;
			player[k].ropeflag=-1;
		}
	}
	for(i=0 ; i<NP ; i++){
		if(i==k || player[i].energy>0) continue;//오기
		if(iscrush(player[i].x,player[i].y,player[k].ropex,player[k].ropey,player[i].radius+ROPERADIUS) && player[k].openmouse)
		{
			player[k].openrope=1;
			player[k].ropeflag=i;
		}
	}
	
/////////////////로프당김/////////////////
	if(player[k].openrope && player[k].openmouse)
	{
		if(player[k].ropex-player[k].x>0)
			player[k].vx+=(player[k].ropex-player[k].x-ROPEBASE)*T*ROPEK;
		if(player[k].ropey-player[k].y>0)
			player[k].vy+=(player[k].ropey-player[k].y-ROPEBASE)*T*ROPEK;
		if(player[k].ropex-player[k].x<0)
			player[k].vx+=(player[k].ropex-player[k].x+ROPEBASE)*T*ROPEK;
		if(player[k].ropey-player[k].y<0)
			player[k].vy+=(player[k].ropey-player[k].y+ROPEBASE)*T*ROPEK;
		if(player[k].ropeflag>=0)
		{
			if(player[k].x-player[player[k].ropeflag].x>0)
				player[player[k].ropeflag].vx+=(player[k].x-player[player[k].ropeflag].x-ROPEBASE)*T*ROPEK;
			if(player[k].y-player[player[k].ropeflag].y>0)
				player[player[k].ropeflag].vy+=(player[k].y-player[player[k].ropeflag].y-ROPEBASE)*T*ROPEK;
			if(player[k].x-player[player[k].ropeflag].x<0)
				player[player[k].ropeflag].vx+=(player[k].x-player[player[k].ropeflag].x+ROPEBASE)*T*ROPEK;
			if(player[k].y-player[player[k].ropeflag].y<0)
				player[player[k].ropeflag].vy+=(player[k].y-player[player[k].ropeflag].y+ROPEBASE)*T*ROPEK;
			player[k].ropex=player[player[k].ropeflag].x;
			player[k].ropey=player[player[k].ropeflag].y;
		}
	}
/////////////유저간 충돌//////////////
	for(i=0 ; i<NP ; i++)
	{
		if(k==i || player[i].energy>0)
			continue;
		if(iscrush(player[k].x,player[k].y,player[i].x,player[i].y,player[i].radius+player[k].radius))
		{
			double rrr, ee;
			rrr=(player[i].y-player[k].y)/(player[i].x-player[k].x);//hypot(player[i].x-player[k].x,player[i].y-player[k].y);
			ee=player[i].radius+player[k].radius;
			player[k].vx-=((player[i].x-player[k].x)/ee)*10000*T;//10000/(player[i].x-player[k].x)*T;
			player[k].vy-=((player[i].y-player[k].y)/ee)*10000*T;//10000/(player[i].y-player[k].y)*T;
		}
	}
	///////////////갈 수 있는지 체크//////////////////

	player[k].ccr=player[k].ccl=player[k].ccu=player[k].ccd=1;
	for(i=0 ; i<WALL ; i++)
	{
		player[k].ccd*=candown(wall[i],player[k].x,player[k].y,player[k].x,player[k].y+(player[k].vy)*T+0.5*G*T*T,player[k].radius);
		player[k].ccu*=canup(wall[i],player[k].x,player[k].y,player[k].x,player[k].y+(player[k].vy)*T+0.5*G*T*T,player[k].radius);
		player[k].ccl*=canleft(wall[i],player[k].x,player[k].y,player[k].x+player[k].vx*T,player[k].y,player[k].radius);
		player[k].ccr*=canright(wall[i],player[k].x,player[k].y,player[k].x+player[k].vx*T,player[k].y,player[k].radius);

		if(isin(wall[i],player[k].ropex,player[k].ropey) && player[k].openmouse)
			player[k].openrope=1;
		if(wall[i].type==DIE)
		{
			if(isin(wall[i],player[k].x+17,player[k].y+17) || isin(wall[i],player[k].x-17,player[k].y-17) || isin(wall[i],player[k].x-17,player[k].y+17) || isin(wall[i],player[k].x+17,player[k].y-17))
			{//죽음처리해야함
			}
		}
	}
	////////////////체크한 값을 토대로 가게함////////////
if(player[k].vx<0 && player[k].ccl)
		player[k].x+=player[k].vx*T;
	else if(player[k].vx>0 && player[k].ccr)
		player[k].x+=player[k].vx*T;
	else
		player[k].vx=0;
	if(!player[k].ccd)
	{
		if(player[k].vy>0)
			player[k].vy=0;
		player[k].having=0;
		if(player[k].jump)
			player[k].vy=-JUMPPOWER;
		player[k].jump=0;
	}
	//두번점프
	if(player[k].jump && player[k].having==0)
	{
		player[k].having=1;
		player[k].vy=-JUMPPOWER;
	}
	if(!player[k].ccu) player[k].vy=0;

	if(player[k].ccd){
		player[k].y+=(player[k].vy)*T+0.5*G*T*T;
		player[k].vy+=G*T;
	}
}
