#ifndef  BUBBLE_H
#define  BUBBLE_H
#include <gameobject.h>

class Bubble : public GameObject
{
    Q_OBJECT
public:
    explicit Bubble(GameObject *parent = 0);
};

#endif // BUBBLE_H
