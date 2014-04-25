#include "gameobject.h"


GameObject::GameObject(QObject *parent) :
    QObject(parent),
    sprite(":/graphics/blip.png"),
    on_ground(false),
    x(0.0),
    y(0.0),
    x_speed(0.0),
    y_speed(0.0),
    step(6),
    max_y_speed(60),
    facing(true)
{
}



//DOWNWARD PIXEL COLLITION
void GameObject::Fall(QPixmap background,int grav)
{
    const QRgb floorpixel = background.toImage().pixel( x+(sprite.width()/2) , y+sprite.height()-2 );
    const int red = qRed(floorpixel);
    if (!(red % 2))
    {
        on_ground = false;
        if (y_speed < max_y_speed) y_speed += grav;
    }

    if(y_speed >= 0)
    {
        for(int i = -(step+1); i <= y_speed; ++i)
        {
            const QRgb floorpixel = background.toImage().pixel( x+(sprite.width()/2) , y+sprite.height()+i-2 );
            const int red = qRed(floorpixel);
            if (red % 2)
            {
                y_speed = 0;
                y += i;
                on_ground = true;
            }
        }
    }
}


//APPLY MOVEMENT
void GameObject::ApplyMovement()
{
    x += x_speed;
    y += y_speed;
}


//WRAP
void GameObject::Wrap()
{
    if( x < -32)                   x = 400; //LEFT TO RIGHT
    if( x > 400)                   x = -32; //RIGHT TO LEFT
    if((y > 300) && (y_speed > 0)) y = -32; //BOTTOM TO TOP
    if((y < -32) && (y_speed < 0)) y = 300; //TOP TO BOTTOM
}
