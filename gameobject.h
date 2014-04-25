#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QImage>
#include <QPixmap>

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = 0);

    QImage sprite;
    bool on_ground;
    double x;
    double y;
    double x_speed;
    double y_speed;
    int step;
    int max_y_speed;
    bool facing;

public slots:
    void Fall(QPixmap, int);
    void ApplyMovement();
    void Wrap();
};

#endif // GAMEOBJECT_H
