#ifndef WASP_H
#define WASP_H

#include <foe.h>

class Wasp : public Foe
{
    Q_OBJECT
public:
    explicit Wasp();
    void ApplyMovement(const int ticks, const std::vector<double>& sine);
    void Animate() noexcept;
};

#endif // WASP_H
