#ifndef  BUBBLEAF_H
#define  BUBBLEAF_H
#include <gameobject.h>
#include <wasp.h>

class Bubbleaf : public GameObject
{
    Q_OBJECT
public:
    explicit Bubbleaf(GameObject *parent = 0);
    int  age;

public slots:
    void ApplyMovement(long ticks, std::vector<double> sine);
    void Draw(QPainter * painter);
};

#endif // BUBBLEAF_H
