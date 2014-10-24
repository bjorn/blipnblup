#include "bubbleaf.h"
#include <wasp.h>
#include <QPainter>
#include <cmath>

#include <qdebug.h>

Bubbleaf::Bubbleaf() :
    GameObject()
{
    SetWidth(32*3);
    SetHeight(32);
    int sprite_height = 64;
    SetHitdX(GetWidth()/2);
    SetHitdY(GetHeight()/2);
    QImage bubble_image = QImage(":/graphics/bubbles.png");
    AddSprite(bubble_image.copy(
                        sprite_height, 0,
                        sprite_height*3, sprite_height)
    );
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
    int device_width = painter->device()->width();
    int device_height = painter->device()->height();
    QPixmap sprite = QPixmap::fromImage(GetSprite(0));
    painter->drawPixmap( GetX(), GetY(), GetWidth(), GetHeight(), sprite);
    //WRAPPING
    if( GetX() < 0){ painter->drawPixmap(
        GetX()+device_width, GetY(),
        GetWidth(), GetHeight(),
        sprite);
    }
    if( GetX() > device_width -GetWidth()){ painter->drawPixmap(
                    GetX()-device_width, GetY(),
                    GetWidth(), GetHeight(),
                    sprite);
    }
    if( GetY() < 0){ painter->drawPixmap(
        GetX(), GetY()+device_height,
        GetWidth(), GetHeight(),
        sprite);
    }
    if( GetY() > device_height - GetHeight()){ painter->drawPixmap(
        GetX(), GetY()-device_height,
        GetWidth(), GetHeight(),
        sprite);
    }

    if(GetX() < 0 && GetY() < 0){ painter->drawPixmap(
        GetX()+device_width, GetY()+device_height,
        GetWidth(), GetHeight(),
        sprite);
    }
    if(GetX() > device_width -GetWidth() && GetY() < 0){ painter->drawPixmap(
        GetX()-device_width, GetY()+device_height,
        GetWidth(), GetHeight(),
        sprite);
    }
    if(GetX() > device_width -GetWidth() && GetY() > device_height - GetHeight()){ painter->drawPixmap(
        GetX()-device_width, GetY()-device_height,
        GetWidth(), GetHeight(),
        sprite);
    }
    if(GetX() < 0 && GetY() > device_height - GetHeight()){ painter->drawPixmap(
        GetX()+device_width, GetY()-device_height,
        GetWidth(), GetHeight(),
        sprite);
    }
}
