#include "gamewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    w.setGeometry(0,0,400,300);
    w.show();
    
    return a.exec();
}
