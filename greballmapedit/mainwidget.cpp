#include <QApplication>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "playwidget.h"
#include "mainwidget.h"

mainwidget::mainwidget()
{
play=new playwidget();
QVBoxLayout *lay=new QVBoxLayout();
QVBoxLayout *right=new QVBoxLayout();
QHBoxLayout *ma=new QHBoxLayout();
QHBoxLayout *d1=new QHBoxLayout();
QHBoxLayout *d2=new QHBoxLayout();
QHBoxLayout *u1=new QHBoxLayout();
QHBoxLayout *u2=new QHBoxLayout();
QHBoxLayout *u3=new QHBoxLayout();
QHBoxLayout *u4=new QHBoxLayout();
QHBoxLayout *u5=new QHBoxLayout();
QHBoxLayout *u6=new QHBoxLayout();
QHBoxLayout *u7=new QHBoxLayout();
QHBoxLayout *u8=new QHBoxLayout();
QHBoxLayout *u9=new QHBoxLayout();
QHBoxLayout *u10=new QHBoxLayout();
QHBoxLayout *u11=new QHBoxLayout();
QHBoxLayout *u12=new QHBoxLayout();
QHBoxLayout *w1=new QHBoxLayout();
QHBoxLayout *w2=new QHBoxLayout();
QHBoxLayout *w3=new QHBoxLayout();
QHBoxLayout *w4=new QHBoxLayout();
QHBoxLayout *blank=new QHBoxLayout();
QPushButton *ub1=play->ub1=new QPushButton(trUtf8("이전"));
QPushButton *ub2=play->ub2=new QPushButton(trUtf8("위치랜덤"));
QPushButton *ub3=play->ub3=new QPushButton(trUtf8("다음"));
QPushButton *ub4=play->ub4=new QPushButton(trUtf8("삭제"));
QPushButton *wb1=play->wb1=new QPushButton(trUtf8("이전"));
QPushButton *wb2=play->wb2=new QPushButton(trUtf8("다음"));
QPushButton *wb3=play->wb3=new QPushButton(trUtf8("삭제"));
QPushButton *b1=play->b1=new QPushButton(trUtf8("유닛모드전환"));
QPushButton *b2=play->b2=new QPushButton(trUtf8("유닛생성"));
QPushButton *b3=play->b3=new QPushButton(trUtf8("유닛만불러오기"));
QPushButton *b4=play->b4=new QPushButton(trUtf8("불러오기"));
QPushButton *b5=play->b5=new QPushButton(trUtf8("벽모드로전환"));
QPushButton *b6=play->b6=new QPushButton(trUtf8("벽생성"));
QPushButton *b7=play->b7=new QPushButton(trUtf8("맵만불러오기"));
QPushButton *b8=play->b8=new QPushButton(trUtf8("저장하기"));
//QPushButton *wb3=new QPushButton("다음");

QLabel *ubase,*wbase;
QLabel *ulabel[20], *wlabel[10];
QLineEdit *uline[20], *wline[10];
int i;
for(i=1 ; i<=16 ; i++)
	play->uline[i]=uline[i]=new QLineEdit();
for(i=1 ; i<=5 ; i++)
	play->wline[i]=wline[i]=new QLineEdit();

ubase=play->ubase=new QLabel(trUtf8("<1/1 번째 유닛>"));
wbase=play->wbase=new QLabel(trUtf8("<1/1 번째 벽>"));
ulabel[1]=new QLabel(trUtf8("최대속도")); //maxpower
ulabel[2]=new QLabel(trUtf8("순간가속도")); //apower
ulabel[3]=new QLabel(trUtf8("점프속도")); //jumppower
ulabel[4]=new QLabel(trUtf8("줄 계수")); //ropek
ulabel[5]=new QLabel(trUtf8("줄 길이")); //ropemlength
ulabel[6]=new QLabel(trUtf8("줄 속도")); //ropespeed
ulabel[7]=new QLabel(trUtf8("줄 x지점")); //ropebase
ulabel[8]=new QLabel(trUtf8("반지름")); //radius
ulabel[9]=new QLabel(trUtf8("그림파일")); //filename , isimage
ulabel[10]=new QLabel(trUtf8("에너지")); //energy
ulabel[11]=new QLabel(trUtf8("질량")); //mass
ulabel[12]=new QLabel(trUtf8("명칭")); //name
ulabel[13]=new QLabel(trUtf8("인공지능")); //head
ulabel[14]=new QLabel(trUtf8("")); 
ulabel[15]=new QLabel(trUtf8("")); 
wlabel[1]=new QLabel(trUtf8("벽타입")); //type
wlabel[2]=new QLabel(trUtf8("벽그래픽화"));//일단 패스
wlabel[3]=new QLabel(trUtf8("파일이름"));//일단 패스

connect(b1,SIGNAL(clicked()),play,SLOT(b1click()));
connect(b2,SIGNAL(clicked()),play,SLOT(b2click()));
connect(b3,SIGNAL(clicked()),play,SLOT(b3click()));
connect(b4,SIGNAL(clicked()),play,SLOT(b4click()));
connect(b5,SIGNAL(clicked()),play,SLOT(b5click()));
connect(b6,SIGNAL(clicked()),play,SLOT(b6click()));
connect(b7,SIGNAL(clicked()),play,SLOT(b7click()));
connect(b8,SIGNAL(clicked()),play,SLOT(b8click()));
connect(ub1,SIGNAL(clicked()),play,SLOT(ub1click()));
connect(ub2,SIGNAL(clicked()),play,SLOT(ub2click()));
connect(ub3,SIGNAL(clicked()),play,SLOT(ub3click()));
connect(ub4,SIGNAL(clicked()),play,SLOT(ub4click()));
connect(wb1,SIGNAL(clicked()),play,SLOT(wb1click()));
connect(wb2,SIGNAL(clicked()),play,SLOT(wb2click()));
connect(wb3,SIGNAL(clicked()),play,SLOT(wb3click()));

u1->addWidget(ubase);
u2->addWidget(ulabel[1]);
u2->addWidget(ulabel[2]);
u2->addWidget(ulabel[3]);
u4->addWidget(ulabel[4]);
u4->addWidget(ulabel[5]);
u4->addWidget(ulabel[6]);
u6->addWidget(ulabel[7]);
u6->addWidget(ulabel[8]);
u6->addWidget(ulabel[9]);
u8->addWidget(ulabel[10]);
u8->addWidget(ulabel[11]);
u8->addWidget(ulabel[12]);
u10->addWidget(ulabel[13]);
u10->addWidget(ulabel[14]);
u10->addWidget(ulabel[15]);
u3->addWidget(uline[1]);
u3->addWidget(uline[2]);
u3->addWidget(uline[3]);
u5->addWidget(uline[4]);
u5->addWidget(uline[5]);
u5->addWidget(uline[6]);
u7->addWidget(uline[7]);
u7->addWidget(uline[8]);
u7->addWidget(uline[9]);
u9->addWidget(uline[10]);
u9->addWidget(uline[11]);
u9->addWidget(uline[12]);
u11->addWidget(uline[13]);
u11->addWidget(uline[14]);
u11->addWidget(uline[15]);
u12->addWidget(ub1);
u12->addWidget(ub2);
u12->addWidget(ub3);
u12->addWidget(ub4);

w1->addWidget(wbase);
w2->addWidget(wlabel[1]);
w2->addWidget(wlabel[2]);
w2->addWidget(wlabel[3]);
w3->addWidget(wline[1]);
w3->addWidget(wline[2]);
w3->addWidget(wline[3]);
w4->addWidget(wb1);
w4->addWidget(wb2);
w4->addWidget(wb3);

///////////////////
right->addLayout(u1);
right->addLayout(u2);
right->addLayout(u3);
right->addLayout(u4);
right->addLayout(u5);
right->addLayout(u6);
right->addLayout(u7);
right->addLayout(u8);
right->addLayout(u9);
right->addLayout(u10);
right->addLayout(u11);
right->addLayout(u12);
right->addLayout(blank,1);
right->addLayout(w1);
right->addLayout(w2);
right->addLayout(w3);
right->addLayout(w4);
right->addLayout(blank,1);

d1->addWidget(b1);
d1->addWidget(b2);
d1->addWidget(b3);
d1->addWidget(b4);
d2->addWidget(b5);
d2->addWidget(b6);
d2->addWidget(b7);
d2->addWidget(b8);
//메인부분//
ma->addWidget(play,5);
ma->addLayout(right,0);
///주요소부분///
lay->addLayout(ma);
lay->addLayout(d1);
lay->addLayout(d2);
////////////
setLayout(lay);
resize(800,600);
play->setFocus();
play->showunit();
}
