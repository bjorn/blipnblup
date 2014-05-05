#include "gamewidget.h"
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    QDesktopWidget d;
    w.setGeometry((d.screenGeometry().width()/2)-400, (d.screenGeometry().height()/2)-300, 400, 300);
    w.show();
    
    return a.exec();
}
