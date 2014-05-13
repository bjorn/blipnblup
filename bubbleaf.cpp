#include "bubbleaf.h"
#include <wasp.h>
#include <QPainter>
#include <cmath>

#include <qdebug.h>

Bubbleaf::Bubbleaf(GameObject *parent) :
    GameObject(parent, ":/graphics/bubbleaf.png"),
    age(0)
{
    hit_dx = 89;
    hit_dy = 15;
}

//MOVE BUBBLEAF
void Bubbleaf::ApplyMovement(long ticks, std::vector<double> sine)
{
    x_speed *= 0.98;

    int phase = floor((1.25*ticks)+randomizer);
    y_speed = 0.11 * sine[phase%512];

    x += x_speed;
    y += y_speed;
}

//DRAW BUBBLEAF
void Bubbleaf::Draw(QPainter *painter)
{
    QPixmap sprite_pxm = QPixmap::fromImage(sprite);
    painter->drawPixmap( x, y, sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);
    //WRAPPING
    if( x <   0)                       painter->drawPixmap(x+400, y    ,sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);
    if( x > 400 -sprite_pxm.width())   painter->drawPixmap(x-400, y    ,sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);
    if( y <   0)                       painter->drawPixmap(x    , y+300,sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);
    if( y > 300 - sprite_pxm.height()) painter->drawPixmap(x    , y-300,sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);

    if(x <   0         && y <   0)                                   painter->drawPixmap(x+400, y+300,sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);
    if(x > 400 -sprite_pxm.width() && y <   0)                       painter->drawPixmap(x-400, y+300,sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);
    if(x > 400 -sprite_pxm.width() && y > 300 - sprite_pxm.height()) painter->drawPixmap(x-400, y-300,sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);
    if(x <   0         && y > 300 - sprite_pxm.height())             painter->drawPixmap(x+400, y-300,sprite_pxm.width(), sprite_pxm.height(), sprite_pxm);
}
