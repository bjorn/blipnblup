#include "foe.h"
#include <QPainter>

Foe::Foe(GameObject *parent) :
    GameObject(parent, ":/graphics/wasp.png"),
    caught(false),
    angry(false)
{
    x = rand() % 400;
    y = rand() % 300;
}

//DRAW GAMEOBJECT
void Foe::Draw(QPainter * painter)
{
    QPixmap * bubble = new QPixmap(":/graphics/bubble.png");
    QTransform matrix;
    matrix.rotate(rot-90*dead);
    matrix.scale(1-(2*!facing_right), 1);
    QPixmap sprite_t = QPixmap::fromImage(sprites[caught].transformed(matrix));
    const int width  = sprite_t.width();
    const int height = sprite_t.height();
    const double dx = -(width - sprites[caught].width())/2;
    const double dy = -(height - sprites[caught].height())/2;
    painter->drawPixmap( x+dx, y+dy, width, height, sprite_t);
    if (caught) painter->drawPixmap( x, y, bubble->width(), bubble->height(), *bubble);
    //SPRITE WRAPPING
    //LEFT RIGHT
    if( x <   0){ painter->drawPixmap(x+dx+400, y+dy    , width, height, sprite_t);
        if (caught) painter->drawPixmap( x+400, y, bubble->width(), bubble->height(), *bubble);
    }
    if( x > 400 - width){  painter->drawPixmap(x+dx-400, y+dy    , width, height, sprite_t);
        if (caught) painter->drawPixmap( x-400, y, bubble->width(), bubble->height(), *bubble);
    }
    //TOP BOTTOM
    if( y <   0){          painter->drawPixmap(x+dx    , y+dy+300, width, height, sprite_t);
        if (caught) painter->drawPixmap( x, y+300, bubble->width(), bubble->height(), *bubble);
    }
    if( y > 300 - height){ painter->drawPixmap(x+dx    , y+dy-300, width, height, sprite_t);
        if (caught) painter->drawPixmap( x, y-300, bubble->width(), bubble->height(), *bubble);
    }
    //CORNERS
    if(x <   0         && y <   0){          painter->drawPixmap(x+dx+400, y+dy+300, width, height, sprite_t);
        if (caught) painter->drawPixmap( x+400, y+300, bubble->width(), bubble->height(), *bubble);
    }
    if(x > 400 - width && y <   0){          painter->drawPixmap(x+dx-400, y+dy+300, width, height, sprite_t);
        if (caught) painter->drawPixmap( x-400, y+300, bubble->width(), bubble->height(), *bubble);
    }
    if(x > 400 - width && y > 300 - height){ painter->drawPixmap(x+dx-400, y+dy-300, width, height, sprite_t);
        if (caught) painter->drawPixmap( x-400, y-300, bubble->width(), bubble->height(), *bubble);
    }
    if(x <   0         && y > 300 - height){ painter->drawPixmap(x+dx+400, y+dy-300, width, height, sprite_t);
        if (caught) painter->drawPixmap( x+400, y-300, bubble->width(), bubble->height(), *bubble);
    }
    delete bubble;
}

//DOWNWARD PIXEL COLLITION
void Foe::Fall(QPixmap background,double grav)
{
    int check_x = (x+(sprite.width()/2));
    check_x = check_x%400;
    int check_y = (y+(sprite.height())-8);
    check_y = check_y%300;
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
                if (y_speed > 1 && caught) y_speed = -y_speed/2.0;
                else y_speed = 0;
                y += i;
                on_ground = true;
            }
        }
    }
}
