#include <QWidget>
#include "compoint.h"
#include "wall.h"
#include "player.h"
#include "bomb.h"

class playwidget : public QWidget
{
Q_OBJECT

public:
int NP;
PLAYER *player;
BOMB *bomb;
int WALL;
double gx, gy;
int wx, wy;
double tt;
double having;
char mapfile[256];
QTimer *timer;
QTime *time;
CWALL *wall;
COMPOINT cpoint;
bool placerandom;
playwidget();

void filesave();
void fileload();
void usermove(int k,double T);
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

public slots:
void timefuc();
};
