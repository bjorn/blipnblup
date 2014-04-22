#include "dialog.h"
#include "ui_dialog.h"

#include <cassert>
#include <limits>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <cmath>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),

    ticks(0),
    grav(1),
    check_x(16),
    check_y(30),

    blip_x(0),
    blip_y(0),
    blip_yspeed(0),
    blip_step(3),
    blip_stand(false),
    pressed_up(true),
    pressed_left(true),
    pressed_right(false),
    pressed_down(false),

    blup_x(0),
    blup_y(0),
    blup_yspeed(0),
    blup_step(3),
    blup_stand(false),
    pressed_w(true),
    pressed_a(false),
    pressed_s(false),
    pressed_d(true)
{
    ui->setupUi(this);

    blip_x =this->ui->blip->x();
    blip_y =this->ui->blip->y();
    blup_x =this->ui->blup->x();
    blup_y =this->ui->blup->y();

    {
        QTimer * const timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),this, SLOT(OnTimer()));
        timer->setInterval(40);
        timer->start();
    }

    //const int max_int = std::numeric_limits<int>::max();
    //this->setWindowTitle(QString::number(max_int));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::OnTimer()
{
    //EXECUTE FUNCTIONS
    ApplyKeys();
    Wrap();
    Fall();
    ApplyMovement();

    //PASS TIME
    /*
    int i = 7;
    const int j = ++i;
    assert(i == 8);
    assert(j == 8);

    const int k = i++;
    assert(k == 8);
    assert(i == 9;)
    */


    ++ticks;

    //EXPERIMENTAL
    this->ui->wasp->setGeometry(
      this->ui->wasp->x()+std::floor(2.0*std::sin(ticks*0.2)+0.5),this->ui->wasp->y()+floor(4*cos(ticks*0.2)+0.5),40,40);
    this->ui->bubble->setGeometry(200+floor(12.0*sin(ticks*0.08)+6), this->ui->bubble->y()-1, 32+floor(4*cos(ticks*0.1)+0.5), 32+floor(4*cos(ticks*0.1+3)+0.5));
    if(this->ui->bubble->y()<-32)
    {
      this->ui->bubble->setGeometry(this->ui->bubble->x(), 300, 32, 32);
    }
}

//WHEN KEYS ARE PRESSED
void Dialog::keyPressEvent(QKeyEvent *e)
{
    //BLIP KEYS PRESS CHECK
    if (e->key()==Qt::Key_Space)
    {
        ui->level->setVisible(false);
        //Maak een nieuwe label
        QLabel * bubble = new QLabel(this);
        //assert(this->layout());

        bubble->setHidden(false);
        bubble->setVisible(true);
        //bubble->
        assert(!bubble->isHidden());

        //Prepareer de bubbel
        QPixmap pixmap(":/graphics/bubble.png");
        assert(!pixmap.width() > 0);
        bubble->setPixmap(pixmap);
        bubble->setGeometry(32,32,32,32);
        //Voeg die toe aan m_bubbles
        m_bubbles.push_back(bubble);
    }
    if ((e->key()==Qt::Key_Up))
    {
        pressed_up = true;
    }
    if (e->key()==Qt::Key_Left)
    {
        pressed_left = true;
    }
    if (e->key()==Qt::Key_Down)
    {
        pressed_down = true;
    }
    if (e->key()==Qt::Key_Right) pressed_right = true;

    //BLUP KEYS PRESS CHECK
    if ((e->key()==Qt::Key_W))
    {
        pressed_w = true;
    }
    if (e->key()==Qt::Key_A)
    {
        pressed_a = true;
    }
    if (e->key()==Qt::Key_S)
    {
        pressed_s = true;
    }
    if (e->key()==Qt::Key_D)
    {
        pressed_d = true;
    }
}

//KEYS RELEASED
void Dialog::keyReleaseEvent(QKeyEvent *e)
{
    //BLIP KEYS RELEASE CHECK

    if (e->key()==Qt::Key_Up)
    {
        pressed_up = false;
    }
    if (e->key()==Qt::Key_Left)
    {
        pressed_left = false;
    }
    if (e->key()==Qt::Key_Down)
    {
        pressed_down = false;
    }
    if (e->key()==Qt::Key_Right)
    {
        pressed_right = false;
    }

    //BLUP KEYS RELEASE CHECK
    if (e->key()==Qt::Key_W)
    {
        pressed_w = false;
    }
    if (e->key()==Qt::Key_A)
    {
        pressed_a = false;
    }
    if (e->key()==Qt::Key_S)
    {
        pressed_s = false;
    }
    if (e->key()==Qt::Key_D)
    {
        pressed_d = false;
    }
}

void Dialog::ApplyKeys() //APPLY KEY EFFECTS
{
    //BLIP STEP
    if (pressed_up && blip_stand)
    {
        blip_stand = false;
        blip_yspeed = -10;
    }
    if (pressed_left)
    {
        const QRgb blip_leftpixel = ui->level->pixmap()->toImage().pixel(blip_x+check_x-blip_step,blip_y+check_y-(blip_step+1));
        const int red = qRed(blip_leftpixel);
        if (!(red % 2))
        {
            blip_x -= blip_step;
        }
    }

    if (pressed_right)
    {
        const QRgb blip_leftpixel = ui->level->pixmap()->toImage().pixel(
          blip_x + check_x +  blip_step,
          blip_y + check_y - (blip_step+1)
        );
        const int red = qRed(blip_leftpixel);
        if (!(red % 2))
        {
            blip_x += blip_step;
        }
    }

    //BLUP STEP
    if (pressed_w&blup_stand)
    {
        blup_stand = false;
        blup_yspeed = -10;
    }
    if (pressed_a)
    {
        const QRgb blup_leftpixel = ui->level->pixmap()->toImage().pixel(blup_x+check_x-blup_step,blup_y+check_y-(blup_step+1));
        const int red = qRed(blup_leftpixel);
        if (!(red % 2))
        {
            blup_x -= blup_step;
        }
    }

    if (pressed_d)
    {
        const QRgb blup_leftpixel = ui->level->pixmap()->toImage().pixel(blup_x+check_x+blup_step,blup_y+check_y-(blup_step+1));
        const int red = qRed(blup_leftpixel);
        if (!(red % 2))
        {
            blup_x += blup_step;
        }
    }
}

void Dialog::ApplyMovement() //APPLY MOVEMENT
{
    //SET BLIP
    blip_y += blip_yspeed;
    this->ui->blip->setGeometry(blip_x,blip_y,32,32);
    //SET BLUP
    blup_y += blup_yspeed;
    this->ui->blup->setGeometry(blup_x,blup_y,32,32);
}

void Dialog::Fall() //DOWNWARD PIXEL COLLITION
{
    //BLIP FALL
    const QRgb blip_floorpixel = ui->level->pixmap()->toImage().pixel(blip_x+check_x,blip_y+check_y);
    const int red = qRed(blip_floorpixel);
    if (!(red % 2))
    {
        blip_stand = false;
        blip_yspeed += grav;
    }

    if(blip_yspeed >= 0)
    {
        for(int i = -(blip_step+1); i <= blip_yspeed; ++i)
        {
            const QRgb blip_floorpixel = ui->level->pixmap()->toImage().pixel(blip_x+check_x,blip_y+check_y+i);
            const int red = qRed(blip_floorpixel);
            if (red % 2)
            {
                blip_yspeed = 0;
                blip_y += i;
                blip_stand = true;
            }
        }
    }
    //BLUP FALL
    const QRgb blup_floorpixel = ui->level->pixmap()->toImage().pixel(blup_x+check_x,blup_y+check_y);
    const int green = qGreen(blup_floorpixel);
    if (!(green % 2))
    {
        blup_stand = false;
        blup_yspeed += grav;
    }

    if(blup_yspeed >= 0)
    {
        for(int i = -(blup_step+1); i <= blup_yspeed; ++i)
        {
            const QRgb blup_floorpixel = ui->level->pixmap()->toImage().pixel(blup_x+check_x,blup_y+check_y+i);
            const int green = qGreen(blup_floorpixel);
            if (green % 2)
            {
                blup_yspeed = 0;
                blup_y += i;
                blup_stand = true;
            }
        }
    }
}

void Dialog::Wrap() //WRAP
{
    //WRAP BLIP
    if((blip_y > 300)&(blip_yspeed > 0)) //BOTTOM TO TOP
    {
        blip_y = -32;
    }

    if((blip_y < -32)&(blip_yspeed < 0)) //TOP TO BOTTOM
    {
        blip_y = 300;
    }

    if(blip_x < -32) //LEFT TO RIGHT
    {
        blip_x = 400;
    }

    if(blip_x > 400) //RIGHT TO LEFT
    {
        blip_x = -32;
    }

    //WRAP BLUP
    if((blup_y>300)&(blup_yspeed>0)) //BOTTOM TO TOP
    {
        blup_y = -32;
    }

    if((blup_y<-32)&(blup_yspeed<0)) //TOP TO BOTTOM
    {
        blup_y = 300;
    }

    if(blup_x < -32) //LEFT TO RIGHT
    {
        blup_x = 400;
    }

    if(blup_x > 400) //RIGHT TO LEFT
    {
        blup_x = -32;
    }
}
