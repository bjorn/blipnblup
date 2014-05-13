#include "player.h"
#include "bubble.h"
#include <stdio.h>

Player::Player(GameObject *parent, const char *img_path) :
    GameObject(parent, img_path),
    pressed_up(false),
    pressed_left(false),
    pressed_right(false),
    pressed_down(false),
    jump(12)
{
}

//SHOOT BUBBLE
Bubble * Player::Shoot()
{
    charge = 0;
    Bubble * bubble = new Bubble(this);
    bubble->x = x;
    bubble->y = y;
    bubble->y_speed = 0;
    bubble->x_speed = (10*(-1+2*facing_right))+(3*pressed_right)-(3*pressed_left);
    return bubble;
}



//APPLY INPUT EFFECTS
void Player::ApplyKeys()
{
    if (!dead){
        //JUMP
        if (pressed_up && on_ground){
            on_ground = false;
            y_speed -= jump;
        }
        //FORCE LEFT
        if (pressed_left){
            facing_right = false;
            if (x_speed > -step) x_speed -= 0.25+(0.75*on_ground);
        }
        //FORCE RIGHT
        if (pressed_right){
            facing_right = true;
            if (x_speed < step) x_speed += 0.25+(0.75*on_ground);
        }
    }
}

//MOVE PLAYER
void Player::ApplyMovement(QPixmap background)
{
    //COLLISION DETECTION TO THE LEFT
    if (x_speed < 0){
        int check_x = (x+(sprite.width()/2));
        int check_y = (y+(sprite.height())-4);
        for(int i = 0; i < -x_speed; ++i){
            if (--check_x < 0) check_x += 400;
            if (check_x > 399) check_x -= 400;
            if (--check_y < 0) check_y += 300;
            if (check_y > 299) check_y -= 300;
            const QRgb sidepixel = background.toImage().pixel(check_x, check_y);
            const int red = qRed(sidepixel);
            if ((!red % 2)){
                x -= i;
                x_speed = 0;
            }
        }
    }

    //COLLISION DETECTION TO THE RIGHT
    if (x_speed > 0){
        int check_x = (x+(sprite.width()/2));
        int check_y = (y+(sprite.height())-4);
        for(int i = 0; i < x_speed; ++i){
            if (++check_x < 0) check_x += 400;
            if (check_x > 399) check_x -= 400;
            if (--check_y < 0) check_y += 300;
            if (check_y > 299) check_y -= 300;
            const QRgb sidepixel = background.toImage().pixel(check_x, check_y);
            const int red = qRed(sidepixel);
            if ((!red % 2)){
                x += i;
                x_speed = 0;
            }
        }
    }

    x += x_speed;
    y += y_speed;

    //SLOW DOWN
    if (on_ground) x_speed *= 0.7;
}
