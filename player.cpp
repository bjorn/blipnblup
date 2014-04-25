#include "player.h"
#include "bubble.h"
#include <stdio.h>

Player::Player(GameObject *parent, const char *img_path) :
    GameObject(parent, img_path),
    pressed_up(false),
    pressed_left(false),
    pressed_right(false),
    pressed_down(false),
    jump(20)
{
}

Bubble * Player::Shoot()
{
    Bubble * bubble = new Bubble(this);
    bubble->x = x;
    bubble->y = y;
    bubble->y_speed = 0;
    bubble->x_speed = (20*(-1+2*facing_right))+(5*pressed_right)-(5*pressed_left);
    return bubble;
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
        facing_right = false;
        const QRgb sidepixel = background.toImage().pixel(
          x + sprite.width()/2  -  step,
          y + sprite.height() - (step+1)
        );
        const int red = qRed(sidepixel);
        if (!(red % 2)) x -= step;
    }

    if (pressed_right)
    {
        facing_right = true;
        const QRgb sidepixel = background.toImage().pixel(
          x + sprite.width()/2  +  step,
          y + sprite.height() - (step+1)
        );
        const int red = qRed(sidepixel);
        if (!(red % 2)) x += step;
    }
}
