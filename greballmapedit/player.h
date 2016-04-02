class AINEED
{
public:
int x, y; //현재 위치
int befx, befy;
int beflag; //아까 세로로 꺽었냐 가로로 꺽었냐
int num;//몇번 꺽었냐
int fright; int fflag; //처음에 어째 시작했냐
void set(int __x,int __y, int _x,int _y,int _beflag,int _fright, int _fflag);
void halfset(int __x,int __y, int _x,int _y,int _beflag,int _fright, int _fflag);
void nextset(int _x,int _y);
};

class AAI
{
public : 
AAI();
void setting(CWALL *wall,int WALL);
int target;
void *tar;
int si;
int fi;
int lwall[100];
int rwall[100];
int twall[100];
int bwall[100];
int order[100];
double ordertime[100];
double temp1[100];
double temp2[100];
int temp3[100];
double lasdis;
double compoint;
COMPOINT cpoint;
};

class PLAYER
{
public:
PLAYER();
void userbasicsetting(double _energy,double _mass,double _force, char *_name);
void usermovesetting(double _maxpower, double _apower, double _jumppower); 
void userropesetting(double _ropek, double _ropemlength, double _ropespeed);
void ropesetup(double _mousex,double _mousey);
void mouse(double _mousex,double _mousey);
bool isropeing();
int number;
int head;
double maxpower,apower,jumppower;
double ropebase, ropek, ropemlength, ropespeed;
double x;
double y;
double mass;
double energy;
double willenergy;
double vx;
double vy;
double footx[2];
double footy[2];
double footvx[2];
double footvy[2];
int bombtype;
bool isimage;
char filename[256];
double bombdelay;
bool ccl,ccr,ccu,ccd;
char name[256];
int width, height;
double radius;
double mousex,mousey;
double ropex,ropey;
double ropelength;
int ropeflag;
bool keyboard[256];
int having;
bool openmouse, openrope;
/////////computer/////////////
AAI *ai;
AINEED whatiwant(CWALL *wall,int WALL);
bool wantup(CWALL *wall, int WALL, bool right);
bool wanttop(CWALL *wall, int WALL, bool right);
bool wantmove(CWALL *wall,int WALL, bool right);
int canup(CWALL *wall, int WALL, bool right, int x, int y);
int cantop(CWALL *wall, int WALL, bool right, int x, int y);
int canmove(CWALL *wall,int WALL, bool right, int x, int y);
int candown(CWALL *wall,int WALL, int x, int y);
int potdistance(CWALL *wall,int WALL, int x1,int y1,int x2,int y2,int x, int y);
bool canwallup(CWALL wall, bool right, int x, int y);
bool canwalltop(CWALL wall, bool right, int x, int y);
bool canwallmove(CWALL wall, bool right, int x, int y);
bool canwalldown(CWALL wall, int x, int y);
bool AIUPWALL(CWALL wall,bool right);
bool AIBOT(CWALL wall,bool right);
bool AITOP(CWALL wall,bool right);
void com(int orr,double orrtime,double t1,double t2);
void comorder(double T);

//임시함수//////
bool jump;
};
