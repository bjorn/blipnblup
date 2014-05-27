#include "bubble.h"
#include <wasp.h>
#include <QPainter>
#include <cmath>

#include <qdebug.h>

Bubble::Bubble(GameObject *parent) :
    GameObject(parent, ":/graphics/bubble.png"),
    m_age(0)
{

}

//AGE BUBBLE AND RETURN TRUE ON OLD
bool Bubble::Age() noexcept{
    ++m_age;
    if (m_age > 201-(Randomize() / 128) ) return true;
    else return false;
}

//MOVE BUBBLE
void Bubble::ApplyMovement(long ticks, const std::vector<double>& sine) noexcept
{
    if ( GetYSpeed() > -2.5 ){ SetYSpeed( GetYSpeed() - 0.05 );}
    SetXSpeed(GetXSpeed() * 0.96);

    int phase = floor( 3 * ticks + Randomize() );
    SetX( GetX() + GetXSpeed() + sine[phase%512] );
    SetY( GetY() + GetYSpeed() );
}

//DRAW BUBBLE
void Bubble::Draw(QPainter * const painter, const int ticks, const std::vector<double>& sine) noexcept
{
    int phase = 3 * ticks + Randomize();
    QImage sprite = GetSprite(0);
    const double width  = sprite.width()  - abs(GetXSpeed())/2 + (2*sine[phase%512]);
    const double height = sprite.height() + abs(GetXSpeed())/4 + (2*sine[phase%512]);
    const double dx = (sprite.width()  - width)  / 2.0;
    const double dy = (sprite.height() - height) / 2.0;
    SetHitdX( (sprite.width()  + dx) / 2.0 );
    SetHitdY( (sprite.height() + dy) / 2.0 );

    QPixmap flip = QPixmap::fromImage(sprite.mirrored(!IsFacingRight(), false));
    painter->drawPixmap( GetX()+dx, GetY()+dy, width, height, flip);
    //WRAPPING
    if( GetX() <   0)          painter->drawPixmap( GetX() + dx + 400, GetY() + dy      , width, height, flip);
    if( GetX() > 400 - width)  painter->drawPixmap( GetX() + dx - 400, GetY() + dy      , width, height, flip);
    if( GetY() <   0)          painter->drawPixmap( GetX() + dx      , GetY() + dy + 300, width, height, flip);
    if( GetY() > 300 - height) painter->drawPixmap( GetX() + dx      , GetY() + dy - 300, width, height, flip);

    if( GetX() <   0         && GetY() <   0)          painter->drawPixmap( GetX() + dx + 400, GetY() + dy + 300, width, height, flip);
    if( GetX() > 400 - width && GetY() <   0)          painter->drawPixmap( GetX() + dx - 400, GetY() + dy + 300, width, height, flip);
    if( GetX() > 400 - width && GetY() > 300 - height) painter->drawPixmap( GetX() + dx - 400, GetY() + dy - 300, width, height, flip);
    if( GetX() <   0         && GetY() > 300 - height) painter->drawPixmap( GetX() + dx + 400, GetY() + dy - 300, width, height, flip);
}
