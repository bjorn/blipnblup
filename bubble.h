#ifndef  BUBBLE_H
#define  BUBBLE_H
#include <gameobject.h>

class Bubble : public GameObject
{
    Q_OBJECT
public:
    explicit Bubble();

    bool Age() noexcept;

    void ApplyMovement(long ticks, const std::vector<double>& sine) noexcept;
    void Draw(QPainter * const painter, const int ticks, const std::vector<double>& sine) noexcept;
private:
    int  m_age;
};

#endif // BUBBLE_H
