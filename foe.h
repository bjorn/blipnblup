#ifndef FOE_H
#define FOE_H
#include <gameobject.h>

class Foe : public GameObject
{
    Q_OBJECT
public:
    explicit Foe(GameObject *parent = 0);
    bool caught;
    bool angry;
signals:

public slots:
    void Draw(QPainter *painter);
    void Fall(QPixmap background,double grav);
};

#endif // FOE_H
