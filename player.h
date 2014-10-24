#ifndef PLAYER_H
#define PLAYER_H

#include <gameobject.h>
#include <bubble.h>

class Player : public GameObject
{
    Q_OBJECT
public:
    explicit Player(bool blup);

    bool GetUp()    const noexcept;
    bool GetLeft()  const noexcept;
    bool GetRight() const noexcept;
    bool GetDown()  const noexcept;

    void SetUp(bool state) noexcept;
    void SetLeft(bool state) noexcept;
    void SetRight(bool state) noexcept;
    void SetDown(bool state) noexcept;

    void ApplyKeys() noexcept;
    void ApplyMovement(const QPixmap& background);
    Bubble * Shoot();

    void Animate() noexcept;

private:
    bool m_pressed_up;
    bool m_pressed_left;
    bool m_pressed_right;
    bool m_pressed_down;
    int  m_jump;
};

#endif // PLAYER_H
