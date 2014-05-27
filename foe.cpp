#include "foe.h"
#include <QPainter>

Foe::Foe(GameObject *parent) :
    GameObject(parent, ":/graphics/wasp.png"),
    m_caught(false),
    m_angry(false),
    m_escape(500),
    m_escape_ticks(5000)
{
    SetX(rand() % 400);
    SetY(rand() % 300);
}

bool Foe::IsAngry() const noexcept {return m_angry;}
bool Foe::IsCaught() const noexcept {return m_caught;}
void Foe::Catch() noexcept {m_caught = true; m_escape_ticks = 0;}

//DRAW FOE
void Foe::Draw(QPainter * painter) const noexcept
{
    QPixmap * bubble = new QPixmap(":/graphics/bubble.png");
    QTransform matrix;
    matrix.rotate(GetRotation()-90*!IsAlive());
    matrix.scale(1-(2*!IsFacingRight()), 1);
    QPixmap sprite = QPixmap::fromImage(GetSprite(IsCaught()).transformed(matrix));
    const int width  = sprite.width();
    const int height = sprite.height();
    const double dx = -(width - GetSprite(IsCaught()).width())/2;
    const double dy = -(height - GetSprite(IsCaught()).height())/2;
    painter->drawPixmap( GetX()+dx, GetY()+dy, width, height, sprite);
    if (IsCaught()) painter->drawPixmap( GetX(), GetY(), bubble->width(), bubble->height(), *bubble);
    //SPRITE WRAPPING
    //LEFT RIGHT
    if( GetX() <   0){ painter->drawPixmap(GetX()+dx+400, GetY()+dy    , width, height, sprite);
        if (IsCaught()) painter->drawPixmap( GetX()+400, GetY(), bubble->width(), bubble->height(), *bubble);
    }
    if( GetX() > 400 - width){  painter->drawPixmap(GetX()+dx-400, GetY()+dy    , width, height, sprite);
        if (IsCaught()) painter->drawPixmap( GetX()-400, GetY(), bubble->width(), bubble->height(), *bubble);
    }
    //TOP BOTTOM
    if( GetY() <   0){          painter->drawPixmap(GetX()+dx    , GetY()+dy+300, width, height, sprite);
        if (IsCaught()) painter->drawPixmap( GetX(), GetY()+300, bubble->width(), bubble->height(), *bubble);
    }
    if( GetY() > 300 - height){ painter->drawPixmap(GetX()+dx    , GetY()+dy-300, width, height, sprite);
        if (IsCaught()) painter->drawPixmap( GetX(), GetY()-300, bubble->width(), bubble->height(), *bubble);
    }
    //CORNERS
    if(GetX() <   0         && GetY() <   0){          painter->drawPixmap(GetX()+dx+400, GetY()+dy+300, width, height, sprite);
        if (IsCaught()) painter->drawPixmap( GetX()+400, GetY()+300, bubble->width(), bubble->height(), *bubble);
    }
    if(GetX() > 400 - width && GetY() <   0){          painter->drawPixmap(GetX()+dx-400, GetY()+dy+300, width, height, sprite);
        if (IsCaught()) painter->drawPixmap( GetX()-400, GetY()+300, bubble->width(), bubble->height(), *bubble);
    }
    if(GetX() > 400 - width && GetY() > 300 - height){ painter->drawPixmap(GetX()+dx-400, GetY()+dy-300, width, height, sprite);
        if (IsCaught()) painter->drawPixmap( GetX()-400, GetY()-300, bubble->width(), bubble->height(), *bubble);
    }
    if(GetX() <   0         && GetY() > 300 - height){ painter->drawPixmap(GetX()+dx+400, GetY()+dy-300, width, height, sprite);
        if (IsCaught()) painter->drawPixmap( GetX()+400, GetY()-300, bubble->width(), bubble->height(), *bubble);
    }
    delete bubble;
}

//DOWNWARD PIXEL COLLITION
void Foe::Fall(QPixmap const background,const double grav) noexcept
{
    int check_x = (GetX()+(GetSprite(0).width()/2));
    check_x = check_x%400;
    int check_y = (GetY()+(GetSprite(0).height())-8);
    check_y = check_y%300;
    const QRgb floorpixel = background.toImage().pixel( check_x , check_y );
    const int red = qRed(floorpixel);
    if (!(red % 2)){
        SetOnGround(false);
        if (GetYSpeed() < GetMaxYSpeed()){ SetYSpeed( GetYSpeed() + grav ); }
    }

    if(GetYSpeed() >= 0){
        for(int i = -(GetStep()+1); i <= GetYSpeed(); ++i){
            const QRgb floorpixel = background.toImage().pixel( check_x , check_y+i );
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
