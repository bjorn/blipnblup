#ifndef  BUBBLE_H
#define  BUBBLE_H
#include <gameobject.h>
#include <wasp.h>

class Bubble : public GameObject
{
    Q_OBJECT
public:
    explicit Bubble(GameObject *parent = 0);
    int  age;

public slots:
    void ApplyMovement(long ticks);
    void Draw(QPainter * painter, long ticks);
};

#endif // BUBBLE_H
