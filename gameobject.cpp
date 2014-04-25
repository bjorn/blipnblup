#include "gameobject.h"
#include <QPainter>


GameObject::GameObject(QObject *parent, const char *img_path) :
    QObject(parent),
    sprite(img_path),
    on_ground(false),
    x(0.0),
    y(0.0),
    x_speed(0.0),
    y_speed(0.0),
    step(6),
    max_y_speed(60),
    facing_right(true)
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
    const int half_width  = sprite.width()/2;
    const int half_height = sprite.height()/2;
    //WRAP OBJECT
    if( x <     -half_width)                    x = 400 -half_width; //LEFT TO RIGHT
    if( x > 400 -half_width)                    x =   0 -half_width; //RIGHT TO LEFT
    if((y > 300 -half_height) && (y_speed > 0)) y =   0 -half_height; //BOTTOM TO TOP
    if((y <     -half_height) && (y_speed < 0)) y = 300 -half_height; //TOP TO BOTTOM
}

void GameObject::Draw(QPainter *painter)
{
    const int width  = sprite.width();
    const int height = sprite.height();
    QPixmap flip = QPixmap::fromImage(sprite.mirrored(!facing_right, false));
    painter->drawPixmap( x, y, width, height, flip);
    //WRAPPING
    if( x <   0)          painter->drawPixmap(x+400, y    , width, height, flip);
    if( x > 400 - width)  painter->drawPixmap(x-400, y    , width, height, flip);
    if( y <   0)          painter->drawPixmap(x    , y+300, width, height, flip);
    if( y > 300 - height) painter->drawPixmap(x    , y-300, width, height, flip);

    if(x <   0         && y <   0)          painter->drawPixmap(x+400, y+300, width, height, flip);
    if(x > 400 - width && y <   0)          painter->drawPixmap(x-400, y+300, width, height, flip);
    if(x > 400 - width && y > 300 - height) painter->drawPixmap(x-400, y-300, width, height, flip);
    if(x <   0         && y > 300 - height) painter->drawPixmap(x+400, y-300, width, height, flip);
}
