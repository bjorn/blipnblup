#ifndef WASP_H
#define WASP_H

#include <gameobject.h>

class Wasp : public GameObject
{
    Q_OBJECT
public:
    explicit Wasp(GameObject *parent = 0);

    double randomizer;
public slots:
    void ApplyMovement(int ticks);
};

#endif // WASP_H
