#ifndef WASP_H
#define WASP_H

#include <foe.h>
#include <bubble.h>

class Wasp : public Foe
{
    Q_OBJECT
public:
    explicit Wasp(Foe *parent = 0);

public slots:
    void ApplyMovement(long ticks, std::vector<double> sine);
};

#endif // WASP_H
