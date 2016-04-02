#include <QRect>

class CWALL : public QRect
{
public:
CWALL();
CWALL(int x1,int y1,int width1,int height1,int type1);
int bot();
int ri();
int le();
int top();
int type;
};
