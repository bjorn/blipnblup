#include "foe.h"
#include <QPainter>

Foe::Foe() :
    GameObject(),
    m_caught(false),
    m_angry(false),
    m_escape(500),
    m_escape_ticks(5000),
    m_bubble(QPixmap::fromImage(QImage(":/graphics/bubbles.png").copy(0, 0, 64, 64)))
{
    SetX(rand() % 400);
    SetY(rand() % 300);
}

bool Foe::IsAngry() const noexcept {return m_angry;}
bool Foe::IsCaught() const noexcept {return m_caught;}
void Foe::Catch() noexcept {m_caught = true; m_escape_ticks = 0;}


//FOE ESCAPE FUNCTION
void Foe::Escape() noexcept
{
    if (std::floor(GetXSpeed() + 0.5) == 0){
        ++m_escape_ticks;
        if (m_escape_ticks < m_escape && m_escape_ticks > m_escape - 100){
            SetX( GetX() + 2 - (m_escape_ticks%5) );
        }
    }
    if (m_escape_ticks > m_escape && IsCaught()){
        m_caught = false;
        m_angry = true;
        SetOnGround(false);
        SetRotation(0);
        SetRotSpeed(0);
    }
}


//DOWNWARD PIXEL COLLITION
void Foe::Fall(QPixmap const background,const double grav) noexcept
{
    int check_x = (GetX()+(GetWidth()/2));
    check_x = check_x%background.width();
    int check_y = (GetY()+(GetHeight())-8);
    check_y = check_y%background.height();
    const QRgb floorpixel = background.toImage().pixel( check_x , check_y );
    const int red = qRed(floorpixel);
    if (!(red % 2)){
        SetOnGround(false);
        if (GetYSpeed() < GetMaxYSpeed()){ SetYSpeed( GetYSpeed() + grav ); }
    }

    if(GetYSpeed() >= 0){
        for(int i = -(GetStep()+1); i <= GetYSpeed(); ++i){
            check_y = (check_y+1)%background.height();
            const QRgb floorpixel = background.toImage().pixel( check_x , check_y);
            const int red = qRed(floorpixel);
            if (red % 2){
                if (GetYSpeed() > 1 && IsCaught()){ SetYSpeed(-GetYSpeed()/2.0); }
                else { SetYSpeed(0); }
                SetY( GetY() + i );
                SetOnGround(true);
            }
        }
    }
}


//DRAW FOE
void Foe::Draw(QPainter * painter) const noexcept
{
    int device_width = painter->device()->width();
    int device_height = painter->device()->height();

    QTransform matrix;
    matrix.rotate(GetRotation());
    matrix.scale(1-(2*!IsFacingRight()), 1);
    QImage sprite_o = GetSprite(GetCurrentFrame());
    QPixmap sprite_t = QPixmap::fromImage( sprite_o.transformed(matrix) );

    double scale = 0.5;

    const int width  = sprite_t.width()*scale;
    const int height = sprite_t.height()*scale;

    int bubble_width = m_bubble.width()*scale;
    int bubble_height = m_bubble.height()*scale;

    const double dx = -(width - GetSprite(GetCurrentFrame()).width()*scale)*0.5;
    const double dy = -(height - GetSprite(GetCurrentFrame()).height()*scale)*0.5;
    const double bubble_dx = (GetWidth() - bubble_width)/2;
    const double bubble_dy = (GetHeight() - bubble_height)/2;
    //DRAW FOE
    painter->drawPixmap(
                GetX()+dx, GetY()+dy,
                width, height,
                sprite_t);
    //DRAW BUBBLE
    if (IsCaught()) painter->drawPixmap(
                GetX()+bubble_dx, GetY()+bubble_dy,
                bubble_width, bubble_height,
                m_bubble);
    //SPRITE WRAPPING
    //LEFT RIGHT
    if( GetX() < 0){ painter->drawPixmap(
                    GetX()+dx+device_width, GetY()+dy,
                    width, height,
                    sprite_t);
        if (IsCaught()) painter->drawPixmap(
                        GetX()+bubble_dx+device_width, GetY()+bubble_dy,
                        bubble_width, bubble_height,
                        m_bubble);
    }
    if( GetX() > device_width - width){ painter->drawPixmap(
                    GetX()+dx-device_width, GetY()+dy,
                    width, height,
                    sprite_t);
        if (IsCaught()) painter->drawPixmap(
                        GetX()+bubble_dx-device_width, GetY()+bubble_dy,
                        bubble_width, bubble_height,
                        m_bubble);
    }
    //TOP BOTTOM
    if( GetY() < 0){ painter->drawPixmap(
                    GetX()+dx    , GetY()+dy+device_height,
                    width, height,
                    sprite_t);
        if (IsCaught()) painter->drawPixmap(
                        GetX()+bubble_dx, GetY()+bubble_dy+device_height,
                        bubble_width, bubble_height,
                        m_bubble);
    }
    if( GetY() > device_height - height){ painter->drawPixmap(
                    GetX()+dx, GetY()+dy-device_height,
                    width, height,
                    sprite_t);
        if (IsCaught()) painter->drawPixmap(
                        GetX()+bubble_dx, GetY()+bubble_dy-device_height,
                        bubble_width, bubble_height,
                        m_bubble);
    }
    //CORNERS
    if(GetX() < 0 && GetY() < 0){ painter->drawPixmap(
                    GetX()+dx+device_width, GetY()+dy+device_height,
                    width, height,
                    sprite_t);
        if (IsCaught()) painter->drawPixmap(
                        GetX()+bubble_dx+device_width, GetY()+bubble_dy+device_height,
                        bubble_width, bubble_height,
                        m_bubble);
    }
    if(GetX() > device_width - width && GetY() < 0){ painter->drawPixmap(
                    GetX()+dx-device_width, GetY()+dy+device_height,
                    width, height,
                    sprite_t);
        if (IsCaught()) painter->drawPixmap(
                        GetX()+bubble_dx-device_width, GetY()+bubble_dy+device_height,
                        bubble_width, bubble_height,
                        m_bubble);
    }
    if(GetX() > device_width - width && GetY() > device_height - height){ painter->drawPixmap(
                    GetX()+dx-device_width, GetY()+dy-device_height,
                    width, height,
                    sprite_t);
        if (IsCaught()) painter->drawPixmap(
                        GetX()+bubble_dx-device_width, GetY()+bubble_dy-device_height,
                        bubble_width, bubble_height,
                        m_bubble);
    }
    if(GetX() < 0 && GetY() > device_height - height){ painter->drawPixmap(
                    GetX()+dx+device_width, GetY()+dy-device_height,
                    width, height,
                    sprite_t);
        if (IsCaught()) painter->drawPixmap(
                        GetX()+bubble_dx+device_width, GetY()+bubble_dy-device_height,
                        bubble_width, bubble_height,
                        m_bubble);
    }
}
