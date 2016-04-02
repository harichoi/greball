#include <math.h>
#include <stdio.h>
#include "wall.h"
#include "compoint.h"
#include "player.h"
#include "bomb.h"
#define G 800

BOMB::BOMB()
{
flag=0;
}

bool BOMB::setting(PLAYER *who)
{
	if(flag>0 || who->bombdelay>0)
		return 0;

	double mmx,mmy;
	mmx=who->mousex;
	mmy=who->mousey;
	double angle, xsi, ysi, tx, ty;
	angle=atan((mmy-who->y)/(mmx-who->x));
	if(mmx-who->x<0)
		angle+=3.141592;
	player=who;
	x=player->x;
	y=player->y;
	flag=who->bombtype;
	if(flag==4)
	{
		xsi=450*cos(angle);
		ysi=450*sin(angle);
	}
	else if(flag==2)
	{
		xsi=1300*cos(angle);
		ysi=1300*sin(angle);
	}
	else if(flag==5)
	{
		xsi=2500*cos(angle);
		ysi=2500*sin(angle);
	}
	vx=player->vx+xsi;
	vy=player->vy+ysi;

	if(cos(angle)>0) right=1; else right=0;
	
	if(flag==1)
		who->bombdelay=3.141592/20;
	if(flag==2)
		who->bombdelay=0.15;
	if(flag==3)
		who->bombdelay=1;
	if(flag==4)
		who->bombdelay=1;
	if(flag==5)
		who->bombdelay=1;
	radius=15;
flowtime=0;
	return 1;
}
void BOMB::cal(double T)
{
flowtime+=T;
	if(flag==1){
angle=3.141592/3*2-flowtime*12;
		if(right)
			x=player->x+2*player->radius*cos(3.141592/3*2-flowtime*12);
		else
			x=player->x-2*player->radius*cos(3.141592/3*2-flowtime*12);
		y=player->y-2*player->radius*sin(3.141592/3*2-flowtime*12);
		if(flowtime>3.141592/18)
		{
			flag=0;
		}
	}
	if(flag==2){
		x+=vx*T;
		y+=(vy)*T+0.5*G*T*T;
		vy+=G*T;
		if(flowtime>2.5)
		{
			flag=0;
		}
	}
	if(flag==4){
		x+=vx*T;
		y+=(vy)*T+0.5*G*T*T;
		vy+=G*T;
		if(flowtime>2.5)
		{
			flag=0;
		}
	}
	
	if(flag==5){
		x+=vx*T;
		y+=(vy)*T;
		if(flowtime>0.5)
		{
			flag=0;
		}
	}
}
