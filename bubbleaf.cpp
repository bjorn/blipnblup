#include "bubbleaf.h"
#include <wasp.h>
#include <QPainter>
#include <cmath>

#include <qdebug.h>

Bubbleaf::Bubbleaf(GameObject *parent) :
    GameObject(parent, ":/graphics/bubbleaf.png")
{
    SetHitdX(89);
    SetHitdY(15);
}

//MOVE BUBBLEAF
void Bubbleaf::ApplyMovement(const int ticks, const std::vector<double>& sine) noexcept
{
    SetXSpeed(GetXSpeed() * 0.98);

    int phase = floor( (1.25*ticks) + Randomize() );
    SetYSpeed( 0.11 * sine[phase%512] );

    SetX( GetX()+GetXSpeed() );
    SetY( GetY()+GetYSpeed() );
}

//DRAW BUBBLEAF
void Bubbleaf::Draw(QPainter * const painter) noexcept
{
    QPixmap sprite = QPixmap::fromImage(GetSprite(0));
    painter->drawPixmap( GetX(), GetY(), sprite.width(), sprite.height(), sprite);
    //WRAPPING
    if( GetX() <   0)                       painter->drawPixmap(GetX()+400, GetY()    ,sprite.width(), sprite.height(), sprite);
    if( GetX() > 400 -sprite.width())   painter->drawPixmap(GetX()-400, GetY()    ,sprite.width(), sprite.height(), sprite);
    if( GetY() <   0)                       painter->drawPixmap(GetX()    , GetY()+300,sprite.width(), sprite.height(), sprite);
    if( GetY() > 300 - sprite.height()) painter->drawPixmap(GetX()    , GetY()-300,sprite.width(), sprite.height(), sprite);

    if(GetX() <   0         && GetY() <   0)                                   painter->drawPixmap(GetX()+400, GetY()+300,sprite.width(), sprite.height(), sprite);
    if(GetX() > 400 -sprite.width() && GetY() <   0)                       painter->drawPixmap(GetX()-400, GetY()+300,sprite.width(), sprite.height(), sprite);
    if(GetX() > 400 -sprite.width() && GetY() > 300 - sprite.height()) painter->drawPixmap(GetX()-400, GetY()-300,sprite.width(), sprite.height(), sprite);
    if(GetX() <   0         && GetY() > 300 - sprite.height())             painter->drawPixmap(GetX()+400, GetY()-300,sprite.width(), sprite.height(), sprite);
}
