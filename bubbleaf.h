#ifndef  BUBBLEAF_H
#define  BUBBLEAF_H
#include <gameobject.h>

class Bubbleaf : public GameObject
{
    Q_OBJECT
public:
    explicit Bubbleaf(GameObject *parent = 0);

public slots:
    void ApplyMovement(const int ticks, const std::vector<double>& sine) noexcept;
    void Draw(QPainter * const painter) noexcept;
};

#endif // BUBBLEAF_H
