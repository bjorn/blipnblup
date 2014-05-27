#ifndef WASP_H
#define WASP_H

#include <foe.h>

class Wasp : public Foe
{
    Q_OBJECT
public:
    explicit Wasp(Foe * parent = 0);
    void ApplyMovement(const int ticks, const std::vector<double>& sine);
};

#endif // WASP_H
