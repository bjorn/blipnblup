#ifndef PLAYER_H
#define PLAYER_H

#include <gameobject.h>

class Player : public GameObject
{
    Q_OBJECT
public:
    explicit Player(GameObject *parent = 0);

    bool pressed_up;
    bool pressed_left;
    bool pressed_right;
    bool pressed_down;
public slots:
    void ApplyKeys(QPixmap);
private:
    int jump;
};

#endif // PLAYER_H
