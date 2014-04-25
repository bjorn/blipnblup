#include "player.h"

Player::Player(GameObject *parent) :
    GameObject(parent),
    pressed_up(false),
    pressed_left(false),
    pressed_right(false),
    pressed_down(false),
    jump(20)
{
}

//APPLY INPUT EFFECTS
void Player::ApplyKeys(QPixmap background)
{
    //BLIP STEP
    if (pressed_up && on_ground)
    {
        on_ground = false;
        y_speed -= jump;
    }
    if (pressed_left)
    {
        facing = false;
        const QRgb sidepixel = background.toImage().pixel(
          x + sprite.width()/2  -  step,
          y + sprite.height() - (step+1)
        );
        const int red = qRed(sidepixel);
        if (!(red % 2)) x -= step;
    }

    if (pressed_right)
    {
        facing = true;
        const QRgb sidepixel = background.toImage().pixel(
          x + sprite.width()/2  +  step,
          y + sprite.height() - (step+1)
        );
        const int red = qRed(sidepixel);
        if (!(red % 2)) x += step;
    }
}
