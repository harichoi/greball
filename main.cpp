#include <QApplication>
#include <QTimer>
#include "playwidget.h"
#include "mainwidget.h"

int main(int argc,char **argv)
{
QApplication app(argc,argv);
mainwidget window;
window.show();
return app.exec();
}
