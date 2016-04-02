#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "compoint.h"
#include "wall.h"
#include "player.h"
#include "bomb.h"

class playwidget : public QWidget
{
Q_OBJECT

public:
QLabel *ubase,*wbase;
QLineEdit *uline[20];
QLineEdit *wline[10];
QPushButton *ub1;
QPushButton *ub2;
QPushButton *ub3;
QPushButton *ub4;
QPushButton *wb1;
QPushButton *wb2;
QPushButton *wb3;
QPushButton *b1;
QPushButton *b2;
QPushButton *b3;
QPushButton *b4;//=new QPushButton(trUtf8("불러오기"));
QPushButton *b5;//=new QPushButton(trUtf8("벽모드로전환"));
QPushButton *b6;//=new QPushButton(trUtf8("벽생성"));
QPushButton *b7;//=new QPushButton(trUtf8("맵만불러오기"));
QPushButton *b8;//=new QPushButton(trUtf8("저장하기"));

int fflag;

//////
PLAYER *player;
BOMB *bomb;
int WALL;
double gx, gy;
int wx, wy;
double tt;
double having;
bool placerandom;
bool keyboard[256];
char mapfile[256];
QTimer *timer;
QTime *time;
CWALL *wall;
COMPOINT cpoint;
playwidget();
void paintEvent(QPaintEvent *a);
void keyPressEvent(QKeyEvent *a);
void keyReleaseEvent(QKeyEvent *a);
void mousePressEvent(QMouseEvent *a);
void mouseReleaseEvent(QMouseEvent *a);
void mouseMoveEvent(QMouseEvent *a);
bool canright(QRect rect,double xx, double yy,double xxx, double yyy,double rad);
bool canup(QRect rect,double xx, double yy,double xxx, double yyy,double rad);
bool candown(QRect rect,double xx, double yy,double xxx, double yyy,double rad);
bool canleft(QRect rect,double xx, double yy,double xxx, double yyy,double rad);
bool isin(QRect rect,double xx,double yy);
bool iscrush(double xx,double yy, double xxx, double yyy, double rad);
void AI(int num,double T);

void showunit();
void saveunit();
void showwall();
void savewall();

void filesave();
void fileload();
public slots:
void timefuc();
void b1click();
void b2click();
void b3click();
void b4click();
void b5click();
void b6click();
void b7click();
void b8click();
void ub1click();
void ub2click();
void ub3click();
void ub4click();
void wb1click();
void wb2click();
void wb3click();
};
