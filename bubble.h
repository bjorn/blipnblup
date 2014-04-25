#ifndef  BUBBLE_H
#define  BUBBLE_H
#include <gameobject.h>

class Bubble : public GameObject
{
    Q_OBJECT
public:
    explicit Bubble(GameObject *parent = 0);
    int age;

public slots:
    void ApplyMovement();
    void Draw(QPainter *painter);
};

#endif // BUBBLE_H
