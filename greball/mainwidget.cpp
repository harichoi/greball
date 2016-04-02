#include <QApplication>
#include <QTimer>
#include <QVBoxLayout>

#include "playwidget.h"
#include "mainwidget.h"

mainwidget::mainwidget()
{
play=new playwidget();
QVBoxLayout *lay=new QVBoxLayout();
lay->addWidget(play);
setLayout(lay);
resize(800,600);
play->setFocus();
}
