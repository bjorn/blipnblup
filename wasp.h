#ifndef WASP_H
#define WASP_H

#include <gameobject.h>
#include <bubble.h>

class Wasp : public GameObject
{
    Q_OBJECT
public:
    explicit Wasp(GameObject *parent = 0);

public slots:
    void ApplyMovement(long ticks);
};

#endif // WASP_H
