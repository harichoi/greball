

struct BOMB
{
public:
int flag;//1 도끼: 2: 따발총 3: 퍼짐형 4: 수류탄 5: 레이저총  0:없음
bool right;
double x;
double y;
double vx;
double vy;
double angle;
double radius;
double flowtime;
PLAYER *player;
BOMB();
bool setting(PLAYER *who);
void cal(double T);
};
