#include "gameobject.h"
#include <QPainter>
#include <cmath>

GameObject::GameObject(QObject *parent, const char *img_path) :
    QObject(parent),
    sprite(img_path),
    randomizer(((rand()%256)*0.128)+1),

    x(0.0),
    y(0.0),
    hit_dx(0),
    hit_dy(0),
    x_speed(0.0),
    y_speed(0.0),

    dead(false),
    on_ground(false),
    facing_right(true),
    step(3),
    max_y_speed(42)
{
    hit_dx = sprite.width() /2;
    hit_dy = sprite.height()/2;
}

//CHECK DISTANCE BETWEEN TWO GAMEOBJECTS
double GameObject::Distance(GameObject * other)
{
    double dx, dy;
    dx = other->x - x;
    dy = other->y - y;
    return sqrt((dx*dx)+(dy*dy));
}

//DOWNWARD PIXEL COLLITION
void GameObject::Fall(QPixmap background,double grav)
{
    const int check_x = (x+(sprite.width()/2));
    const int check_y = (y+(sprite.height())-2);
    const QRgb floorpixel = background.toImage().pixel( check_x , check_y );
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
            const QRgb floorpixel = background.toImage().pixel( check_x , check_y+i );
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


//POSITION WRAPPING
void GameObject::Wrap()
{
    const int half_width  = sprite.width()/2;
    const int half_height = sprite.height()/2;

    if( x <     - half_width)                    x = 400 - half_width; //LEFT TO RIGHT
    if( x > 400 - half_width)                    x =   0 - half_width; //RIGHT TO LEFT
    if((y > 300 - half_height) && (y_speed > 0)) y =   0 - half_height;//BOTTOM TO TOP
    if((y <     - half_height) && (y_speed < 0)) y = 300 - half_height;//TOP TO BOTTOM
}

//DRAW GAMEOBJECT
void GameObject::Draw(QPainter * painter)
{
    QTransform matrix;
    matrix.scale(1-(2*!facing_right), 1);
    matrix.rotate(-90*dead);
    QPixmap result = QPixmap::fromImage(sprite.transformed(matrix));
    const int width  = result.width();
    const int height = result.height();
    painter->drawPixmap( x, y, width, height, result);
    //SPRITE WRAPPING
    //LEFT RIGHT
    if( x <   0)          painter->drawPixmap(x+400, y    , width, height, result);
    if( x > 400 - width)  painter->drawPixmap(x-400, y    , width, height, result);
    //TOP BOTTOM
    if( y <   0)          painter->drawPixmap(x    , y+300, width, height, result);
    if( y > 300 - height) painter->drawPixmap(x    , y-300, width, height, result);
    //CORNERS
    if(x <   0         && y <   0)          painter->drawPixmap(x+400, y+300, width, height, result);
    if(x > 400 - width && y <   0)          painter->drawPixmap(x-400, y+300, width, height, result);
    if(x > 400 - width && y > 300 - height) painter->drawPixmap(x-400, y-300, width, height, result);
    if(x <   0         && y > 300 - height) painter->drawPixmap(x+400, y-300, width, height, result);
}
