#include "bubble.h"
#include <wasp.h>
#include <QPainter>
#include <cmath>

#include <qdebug.h>

Bubble::Bubble(GameObject *parent) :
    GameObject(parent, ":/graphics/bubble.png"),
    age(0)
{
}

//MOVE BUBBLE
void Bubble::ApplyMovement(long ticks, std::vector<double> sine)
{
    if (y_speed > -2.5) y_speed -= 0.05;
    x_speed *= 0.96;

    int phase = floor(3*ticks+randomizer);
    x += x_speed + sine[phase%512];
    y += y_speed;
}

//DRAW BUBBLE
void Bubble::Draw(QPainter *painter, long ticks, std::vector<double> sine)
{
    int phase = 3*ticks+randomizer;
    const double width  = sprite.width() - abs(x_speed)/2 + (2*sine[phase%512]);
    const double height = sprite.height()+ abs(x_speed)/4 + (2*sine[phase%512]);
    const double dx = (sprite.width()-width)/2.0;
    const double dy = (sprite.height()-height)/2.0;
    hit_dx = (sprite.width()+dx)/2.0;
    hit_dy = (sprite.height()+dy)/2.0;

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
