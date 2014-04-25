<<<<<<< HEAD
#include "gamewidget.h"
=======
#include "dialog.h"
>>>>>>> 7b22a510f3a27ced1d57614279b5f0170d639a4d
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD
    GameWidget w;
    w.setGeometry(0,0,400,300);
=======
    Dialog w;
>>>>>>> 7b22a510f3a27ced1d57614279b5f0170d639a4d
    w.show();
    
    return a.exec();
}
