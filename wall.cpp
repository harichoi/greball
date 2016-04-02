#include <QRect>
#include "wall.h"

CWALL::CWALL()
{
type=0;
}


CWALL::CWALL(int x1,int y1,int width1,int height1, int type1)
{
setX(x1);
setY(y1);
setWidth(width1);
setHeight(height1);
type=type1;
}


int CWALL::bot()
{
return y()+height()/2;
}
int CWALL::ri()
{
return x()+width()/2;
}
int CWALL::le()
{
return x()-width()/2;
}
int CWALL::top()
{
return y()-height()/2;
}
