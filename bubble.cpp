#include "bubble.h"
#include <QPainter>
#include <cmath>

Bubble::Bubble(GameObject *parent) :
    GameObject(parent, ":/graphics/bubble.png"),
    age(0)
{
}

void Bubble::ApplyMovement()
{
    if (y_speed > -5) y_speed -= 0.1;
    x_speed *= 0.9;

    x += x_speed;
    y += y_speed;
}

void Bubble::Draw(QPainter *painter)
{
    const int width  = sprite.width() - abs(x_speed)/2;
    const int height = sprite.height()+ abs(x_speed)/4;
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
