#include "gamewidget.h"
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    QDesktopWidget d;
    w.setWindowState(Qt::WindowFullScreen);
    w.show();
    
    return a.exec();
}
