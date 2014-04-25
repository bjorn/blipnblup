#include "bubble.h"
#include <QPainter>
#include <cmath>

Bubble::Bubble(GameObject *parent) :
    GameObject(parent, ":/graphics/bubble.png"),
    age(0)
{
}

void Bubble::ApplyMovement(long ticks)
{
    if (y_speed > -5) y_speed -= 0.1;
    x_speed *= 0.9;

    x += x_speed + (2*sin(0.10*ticks+randomizer));
    y += y_speed;
}

void Bubble::Draw(QPainter *painter, long ticks)
{
    const double width  = sprite.width() - abs(x_speed)/2 + (2*sin(0.10*ticks+randomizer));
    const double height = sprite.height()+ abs(x_speed)/4 + (2*sin(0.11*ticks+randomizer));
    const double dx = (sprite.width()-width)/2.0;
    const double dy = (sprite.height()-height)/2.0;

    QPixmap flip = QPixmap::fromImage(sprite.mirrored(!facing_right, false));
    painter->drawPixmap( x+dx, y+dy, width, height, flip);
    //WRAPPING
    if( x <   0)          painter->drawPixmap(x+dx+400, y+dy    , width, height, flip);
    if( x > 400 - width)  painter->drawPixmap(x+dx-400, y+dy    , width, height, flip);
    if( y <   0)          painter->drawPixmap(x+dx    , y+dy+300, width, height, flip);
    if( y > 300 - height) painter->drawPixmap(x+dx    , y+dy-300, width, height, flip);

    if(x <   0         && y <   0)          painter->drawPixmap(x+dx+400, y+dy+300, width, height, flip);
    if(x > 400 - width && y <   0)          painter->drawPixmap(x+dx-400, y+dy+300, width, height, flip);
    if(x > 400 - width && y > 300 - height) painter->drawPixmap(x+dx-400, y+dy-300, width, height, flip);
    if(x <   0         && y > 300 - height) painter->drawPixmap(x+dx+400, y+dy-300, width, height, flip);
}
