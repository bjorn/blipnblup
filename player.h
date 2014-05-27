#ifndef PLAYER_H
#define PLAYER_H

#include <gameobject.h>
#include <bubble.h>

class Player : public GameObject
{
    Q_OBJECT
public:
    explicit Player(GameObject *parent = 0, const char *img_path = ":/graphics/blup.png");

    bool GetUp()    const;
    bool GetLeft()  const;
    bool GetRight() const;
    bool GetDown()  const;

    void SetUp(bool state);
    void SetLeft(bool state);
    void SetRight(bool state);
    void SetDown(bool state);

    void ApplyKeys();
    void ApplyMovement(const QPixmap& background);
    Bubble * Shoot();

private:
    bool m_pressed_up;
    bool m_pressed_left;
    bool m_pressed_right;
    bool m_pressed_down;
    int  m_jump;
};

#endif // PLAYER_H
