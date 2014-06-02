#ifndef FOE_H
#define FOE_H
#include <gameobject.h>

class Foe : public GameObject
{
    Q_OBJECT
public:
    explicit Foe(GameObject *parent = 0);
private:
    bool m_caught;
    bool m_angry;
    const int m_escape;
    int m_escape_ticks;

public slots:
    bool IsAngry() const noexcept;
    bool IsCaught() const noexcept;
    void Catch() noexcept;
    void Escape() noexcept;

    void Fall(QPixmap const background, const double grav) noexcept;
    void Draw(QPainter * const painter) const noexcept;
};

#endif // FOE_H
