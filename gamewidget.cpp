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

    blip(0, ":/graphics/blip.png"),
    blup(0, ":/graphics/blup.png"),

    players(),
    bubbles(),
    wasps()

{
    setWindowTitle("Blip 'n Blip's Skyward Adventures!");

    //PUSH PLAYER POINTERS INTO A VECTOR
    players.push_back(&blip);
    players.push_back(&blup);

    //SET INITIAL VALUES FOR PLAYERS
    for (uint i = 0; i < players.size(); ++i)
    {
        players[i]->x = 100 + ( 100*i );
        players[i]->y = 50 + (50*i);
    }

    //N WASPS
    for (int i = 0; i < 3; ++i)
    {
        Wasp * wasp = new Wasp();
        wasp->x = rand() % 400;
        wasp->y = rand() % 300;
        wasps.push_back(wasp);
    }

    //CREATE TIME
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
    for (uint i = 0; i < players.size(); ++i)
    {
        players[i]->Wrap();
        players[i]->ApplyKeys(background);
        players[i]->Fall(background, grav);
        players[i]->ApplyMovement();
    }

    //EXECUTE BUBBLE FUNCTIONS
    for (uint i = 0; i < bubbles.size(); ++i)
    {
        bubbles[i]->Wrap();
        bubbles[i]->ApplyMovement(ticks);
      ++bubbles[i]->age;
        if (bubbles[i]->age > 100-2*bubbles[i]->randomizer)
        {
            std::swap(bubbles[bubbles.size()-1], bubbles[i]);
            bubbles.pop_back();
        }
    }

    //EXECUTE WASP FUNCTIONS
    for (uint i = 0; i < wasps.size(); ++i)
    {
        wasps[i]->Wrap();
        wasps[i]->ApplyMovement(ticks);
    }


    //CALL PAINTER
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
  for(uint i = 0; i < players.size(); ++i) players[i]->Draw(&painter);

  //DRAW WASPS
  for(uint i = 0; i < wasps.size(); ++i) wasps[i]->Draw(&painter);

  //DRAW BUBBLES
  for(uint i = 0; i < bubbles.size(); ++i) bubbles[i]->Draw(&painter, ticks);
}

//ON EVERY KEYPRESS
void GameWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        //BLIP KEYS PRESS CHECK
        case Qt::Key_Up     : players[0]->pressed_up    = true; break;
        case Qt::Key_Left   : players[0]->pressed_left  = true; break;
        case Qt::Key_Right  : players[0]->pressed_right = true; break;
        case Qt::Key_Control: bubbles.push_back(players[0]->Shoot()); break;
        //BLUP KEYS PRESS CHECK
        case Qt::Key_W      : players[1]->pressed_up    = true; break;
        case Qt::Key_A      : players[1]->pressed_left  = true; break;
        case Qt::Key_D      : players[1]->pressed_right = true; break;
        case Qt::Key_Space  : bubbles.push_back(players[1]->Shoot()); break;
        default : break;
    }
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

