#include <cassert>
#include <limits>
#include <QDebug>

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QResource>
#include <cmath>

#include "gamewidget.h"
#include "player.h"
#include "bubble.h"

GameWidget::GameWidget() :

    background(":/graphics/level2.png"),

    ticks(0),
    grav(2),

    blip(),
    blup()//,

    /*m_players(),
    m_bubbles()*/
{
    /*m_players.push_back(blip);
    m_players.push_back(blup);*/
    blip.pressed_up = true;
    blip.pressed_right = true;

    blup.pressed_up = true;
    blup.pressed_left = true;
    //SET INITIAL VALUES
    blip.x = 120;
    blip.y = 50;

    blup.x = 280;
    blup.y = 200;

    //m_players[0].name("Blip");
    //m_players[0].imgpath(":/graphics/blip.png");

    //m_players[1].name("Blup");
    //m_players[1].imgpath(":/graphics/blup.png");

    {
        QTimer * const timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),this, SLOT(OnTimer()));
        timer->setInterval(36);
        timer->start();
    }

    //const int max_int = std::numeric_limits<int>::max();
    //this->setWindowTitle(QString::number(max_int));
}


//ON EVERY TIMER
void GameWidget::OnTimer()
{
    //EXECUTE PLAYER FUNCTIONS
    blip.Wrap();
    blip.ApplyKeys(background);
    blip.Fall(background, grav);
    blip.ApplyMovement();

    blup.Wrap();
    blup.ApplyKeys(background);
    blup.Fall(background, grav);
    blup.ApplyMovement();

    //USING VECTORS
    /*for (int player = 0; player < m_players.size(); ++player)
    {
        m_players[player].ApplyKeys();
        m_players[player].ApplyMovement();
        m_players[player].Wrap();
        m_players[player].Fall();
    }*/

    //PAINT
    this->repaint();

    //PASS TIME
    ++ticks;

    //EXPERIMENTAL
    /*
    this->ui->wasp->setGeometry(
      this->ui->wasp->x()+std::floor(2.0*std::sin(ticks*0.2)+0.5),this->ui->wasp->y()+floor(4*cos(ticks*0.2)+0.5),40,40);
    this->ui->bubble->setGeometry(200+floor(12.0*sin(ticks*0.08)+6), this->ui->bubble->y()-1, 32+floor(4*cos(ticks*0.1)+0.5), 32+floor(4*cos(ticks*0.1+3)+0.5));
    if(this->ui->bubble->y()<-32)
    {
      this->ui->bubble->setGeometry(this->ui->bubble->x(), 300, 32, 32);
    }
    */

    /*
    int i = 7;
    const int j = ++i;
    assert(i == 8);
    assert(j == 8);

    const int k = i++;
    assert(k == 8);
    assert(i == 9;)
    */
}

void GameWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  //DRAW BACKGROUND
  painter.drawPixmap(0,0,background.width(),background.height(),background);

  //DRAW PLAYERS
  QPixmap blip_flip = QPixmap::fromImage(blip.sprite.mirrored(!blip.facing, false));
  painter.drawPixmap(blip.x,blip.y, blip.sprite.width(), blip.sprite.height(), blip_flip);
  QPixmap blup_flip = QPixmap::fromImage(blup.sprite.mirrored(!blup.facing, false));
  painter.drawPixmap(blup.x,blup.y, blup.sprite.width(), blup.sprite.height(), blup_flip);

  //USING VECTORS
    /*for (char player = 0; player < m_players.size(); ++player)
    {
      QPixmap pixmap(":/graphics/placeholder.png");
      painter.drawPixmap(
        m_players[player].x, m_players[player].y,
        m_players[player].img.width(), m_players[player].img.height(),
        pixmap);
    }*/
}

//ON EVERY KEYPRESS
void GameWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        //BLIP KEYS PRESS CHECK
        case Qt::Key_Up    : blip.pressed_up = true; break;
        case Qt::Key_Left  : blip.pressed_left = true; break;
        case Qt::Key_Right : blip.pressed_right = true; break;
        //BLUP KEYS PRESS CHECK
        case Qt::Key_W     : blup.pressed_up = true; break;
        case Qt::Key_A     : blup.pressed_left = true; break;
        case Qt::Key_D     : blup.pressed_right = true; break;
        default : break;
    }
    //Shoot();
      /*Bubble bubble;
      bubble.x = x;
      bubble.y = y;
      switch (facing)
      {
        case 0 : bubble.x_speed = -20; break;
        case 1 : bubble.x_speed =  20; break;
      }

      m_bubbles.push_back(bubble);

      {
        const int sz = static_cast<int>(m_bubbles.size());
        for (int i=0; i!=sz; ++i)
        {
            ++m_bubbles[i].x;
            m_bubbles[i].y = m_bubbles[i].x +12;
        }
      }

      {
        const int to_kill = 3;
        const int sz = static_cast<int>(m_bubbles.size());
        assert(sz == 6);
        std::swap(m_bubbles[to_kill],m_bubbles[sz - 1]);
        m_bubbles.pop_back();
      }*/
        /*
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
        } //Dat dit niet werkte had waarschijnlijk met het pad te maken (prefix+directory)
        */
}



//ON EVERY KEYRELEASE
void GameWidget::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        //BLIP KEYS RELEASE CHECK
        case Qt::Key_Up : blip.pressed_up = false; break;
        case Qt::Key_Left : blip.pressed_left = false; break;
        case Qt::Key_Right : blip.pressed_right = false; break;
        //BLUP KEYS RELEASE CHECK
        case Qt::Key_W : blup.pressed_up = false; break;
        case Qt::Key_A : blup.pressed_left = false; break;
        case Qt::Key_D : blup.pressed_right = false; break;
        default : break;
    }
}

