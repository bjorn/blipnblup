#include <cassert>
#include <limits>
#include <QDebug>

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QResource>
#include <cmath>
#include <memory>

#include "gamewidget.h"
#include "player.h"
#include "bubble.h"

GameWidget::GameWidget() :

    background(":/graphics/level2.png"),

    ticks(0),
    grav(0.8),

    blip(0, ":/graphics/blip.png"),
    blup(0, ":/graphics/blup.png"),

    players(),
    bubbles(),
    wasps()

//ONLY ONCE
{
    setWindowTitle("Blip 'n Blup's Skyward Adventures!");

    //PUSH PLAYER POINTERS INTO A VECTOR
    players.push_back(&blip);
    players.push_back(&blup);
    //SET INITIAL VALUES FOR PLAYERS
    for (uint i = 0; i < players.size(); ++i){
        players[i]->x = 51 + ( 101*i );
        players[i]->y = 51 + ( 101*i );
    }
    //SPAWN WASPS
    for (int i = 0; i < 1; ++i){
        Wasp * wasp = new Wasp();
        wasp->x = rand() % 400;
        wasp->y = rand() % 300;
        wasps.push_back(wasp);
    }
    //CREATE TIME
    QTimer * const timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(OnTimer()));
    timer->setInterval(16);
    timer->start();

    //const int max_int = std::numeric_limits<int>::max();
}


//ON EVERY TIMER
void GameWidget::OnTimer()
{
    //EXECUTE PLAYER FUNCTIONS
    for (uint i = 0; i < players.size(); ++i){
        players[i]->Wrap();
        players[i]->ApplyKeys();
        players[i]->Fall(background, grav);
        players[i]->ApplyMovement(background);
    }

    //EXECUTE WASP FUNCTIONS
    for (uint i = 0; i < wasps.size(); ++i){
        wasps[i]->Wrap();
        if (wasps[i]->caught) wasps[i]->Fall(background, grav);
        wasps[i]->ApplyMovement(ticks);
        //WASP PLAYER INTERACTION
        for (uint j = 0; j < players.size(); ++j){
            if (wasps[i]->Distance(players[j]) < 23){
                if (!players[j]->dead && !wasps[i]->caught){
                    players[j]->dead = true;
                    players[j]->y_speed = -3;
                }
                /*if (!players[j]->dead && wasps[i]->caught){
                    wasps[i]->x_speed += ((wasps[i]->x-players[j]->x)/10.0)*-players[j]->x_speed;
                    std::swap(wasps[wasps.size()-1], wasps[i]);
                    delete wasps[wasps.size()-1];
                    wasps.pop_back();
                }*/
            }
        }
    }

    //EXECUTE BUBBLE FUNCTIONS
    for (uint i = 0; i < bubbles.size(); ++i){
        bubbles[i]->Wrap();
        bubbles[i]->ApplyMovement(ticks);
        //AGE AND REMOVE
      ++bubbles[i]->age;
        if (bubbles[i]->age > 201-4*bubbles[i]->randomizer){
            std::swap(bubbles[bubbles.size()-1], bubbles[i]);
            delete bubbles[bubbles.size()-1];
            bubbles.pop_back();
        }
        //BUBBLE WASP INTERACTION
        for (uint j = 0; j < wasps.size(); ++j){
            if (abs(bubbles[i]->x_speed) > 2 && bubbles[i]->Distance(wasps[j]) < 23){
                if (!wasps[j]->caught){
                    //CATCH WASP
                    wasps[j]->caught = true;
                    //REMOVE BUBBLE
                    std::swap(bubbles[bubbles.size()-1], bubbles[i]);
                    delete bubbles[bubbles.size()-1];
                    bubbles.pop_back();
                }
                if (wasps[j]->caught){
                    wasps[j]->x_speed += bubbles[i]->x_speed/20.0;
                }
            }
        }
        //REVIVE
        for (uint j = 0; j < players.size(); ++j){
            if (bubbles[i]->Distance(players[j]) < 23){
                if (players[j]->dead){
                    //REVIVE PLAYER
                    players[j]->dead = false;
                    players[j]->y_speed = -3;
                    //REMOVE BUBBLE
                    std::swap(bubbles[bubbles.size()-1], bubbles[i]);
                    delete bubbles[bubbles.size()-1];
                    bubbles.pop_back();
                }
            }
        }
    }
    //GAME OVER
    if (players[0]->dead && players[1]->dead && wasps.size() < 101 && !(ticks%10) ){
        Wasp*wasp = new Wasp();
        wasps.push_back(wasp);
    }
    //CALL PAINTER
    this->repaint();

    //PASS TIME
    ++ticks;
}


//ON EVERY REPAINT
void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    //DRAW BACKGROUND
    painter.drawPixmap(0, 0, background.width(), background.height(), background);

    //DRAW PLAYERS
    for(uint i = 0; i < players.size(); ++i) players[i]->Draw(&painter);

    //DRAW WASPS
    for(uint i = 0; i < wasps.size(); ++i) wasps[i]->Draw(&painter);

    //DRAW BUBBLES
    for(uint i = 0; i < bubbles.size(); ++i) bubbles[i]->Draw(&painter, ticks);
}


//ON EVERY KEYS PRESS
void GameWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()){
        //BLIP KEYS PRESS CHECK
        case Qt::Key_Up     : players[0]->pressed_up    = true;       break;
        case Qt::Key_Left   : players[0]->pressed_left  = true;       break;
        case Qt::Key_Right  : players[0]->pressed_right = true;       break;
        case Qt::Key_Control: if (!players[0]->dead) bubbles.push_back(players[0]->Shoot()); break;

        //BLUP KEYS PRESS CHECK
        case Qt::Key_W      : players[1]->pressed_up    = true;       break;
        case Qt::Key_A      : players[1]->pressed_left  = true;       break;
        case Qt::Key_D      : players[1]->pressed_right = true;       break;
        case Qt::Key_Space  : if (!players[1]->dead && bubbles.size()<5) bubbles.push_back(players[1]->Shoot()); break;

        //SPAWN WASPS (1)
        case Qt::Key_1      : {Wasp*wasp = new Wasp();
                               wasps.push_back(wasp);}
                               break;
        default : break;
    }
}


//ON EVERY KEYS RELEASE
void GameWidget::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()){
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

