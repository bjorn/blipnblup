#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QImage>
#include <QPixmap>

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = 0, const char *img_path = ":graphics/wasp.png");

    QImage sprite;
    double randomizer;

    double x;
    double y;
    int    hit_dx;
    int    hit_dy;
    double x_speed;
    double y_speed;

    bool   dead;
    bool   on_ground;
    bool   facing_right;
    int    step;
    int    max_y_speed;

public slots:
    void   Fall(QPixmap, double grav);
    void   ApplyMovement();
    void   Wrap();
    void   Draw(QPainter * painter);
    double Distance(GameObject * other);
};

#endif // GAMEOBJECT_H
