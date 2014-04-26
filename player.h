#ifndef PLAYER_H
#define PLAYER_H

#include <gameobject.h>
#include <bubble.h>

class Player : public GameObject
{
    Q_OBJECT
public:
    explicit Player(GameObject *parent = 0, const char *img_path = ":/graphics/blup.png");

    bool pressed_up;
    bool pressed_left;
    bool pressed_right;
    bool pressed_down;

public slots:
    void ApplyKeys();
    void ApplyMovement(QPixmap background);
    Bubble * Shoot();

private:
    int jump;
};

#endif // PLAYER_H
