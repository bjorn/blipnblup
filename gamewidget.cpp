//GAMEWIDGET.CPP INCLUDES
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
#include "bubbleaf.h"
#include "wasp.h"

//CONSTRUCTOR HEAD
GameWidget::GameWidget() :

    background(":/graphics/level2.png"),

    ticks(0),
    grav(0.8),

    blip(0),
    blup(1),
    bubbleaf(),

    sine(),
    players(),
    bubbles(),
    wasps()

//CONSTRUCTOR BODY
{
    setCursor(Qt::BlankCursor);
    setWindowTitle("Blip 'n Blup's Skyward Adventures!");
    //SET INITIAL BUBBLEAF POSITION
    bubbleaf.SetX(100);
    bubbleaf.SetY(50);
    //PUSH PLAYER POINTERS INTO A VECTOR
    players.push_back(&blip);
    players.push_back(&blup);
    //SET INITIAL VALUES FOR PLAYERS
    for (uint i = 0; i < players.size(); ++i){
        players[i]->SetX(51 + ( 101*i ));
        players[i]->SetY(51 + ( 101*i ));
    }
    //SPAWN INITIAL WASPS
    for (int i = 0; i < 1; ++i){
        Wasp * wasp = new Wasp();
        wasps.push_back(wasp);
    }
    //CREATE TIME
    QTimer * const timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(OnTimer()));
    timer->setInterval(16);
    timer->start();
    //CONSTRUCT SINE LOOKUP VECTOR
    double pi = 3.141592653;

    for (int i = 0; i < 512; ++i){
        double val = sin((i/512.0)*2.0*pi);
        sine.push_back(val);
    }
    //const int max_int = std::numeric_limits<int>::max();
}


//ON EVERY TIMER SIGNAL
void GameWidget::OnTimer()
{
    QPixmap full_background = background;
    QPainter background_painter(&full_background);
    double coli_dist = 22;
    //DRAW BUBBLEAF
    bubbleaf.Draw(&background_painter);

    //EXECUTE PLAYER FUNCTIONS
    for (uint i = 0; i < players.size(); ++i){
        players[i]->Wrap();
        players[i]->ApplyKeys();
        players[i]->Fall(full_background, grav);
        players[i]->ApplyMovement(background);
        players[i]->Charge();
        players[i]->Animate();
    }
    //EXECUTE WASP FUNCTIONS
    for (uint i = 0; i < wasps.size(); ++i){
        wasps[i]->Wrap();
        wasps[i]->Escape();
        wasps[i]->Animate();
        if (wasps[i]->IsCaught()) {
            wasps[i]->Fall(full_background, grav);
        }
        wasps[i]->ApplyMovement(ticks, sine);
        //WASP PLAYER INTERACTION
        for (uint j = 0; j < players.size(); ++j){
            if (wasps[i]->Distance(players[j]) < coli_dist){
                if (players[j]->IsAlive() && !wasps[i]->IsCaught()){
                    players[j]->Kill();
                    players[j]->SetYSpeed(-3);
                }
            }
        }
    }
    //Removing bubbles causes crash if the same bubble later tries to interact with another object
    //Solution: Use smart pointers

    //EXECUTE BUBBLE FUNCTIONS
    for (uint i = 0; i < bubbles.size(); ++i){
        bubbles[i]->Wrap();
        bubbles[i]->ApplyMovement(ticks, sine);
        //BUBBLE BUBBLEAF INTERACTION
        Bubbleaf * bubbleaf_ptr = &bubbleaf;
        if (bubbles[i]->Distance(bubbleaf_ptr) < coli_dist){
            bubbleaf.SetXSpeed( bubbleaf.GetXSpeed()+(bubbles[i]->GetXSpeed()/20) );
        }
        //AGE AND REMOVE
        if (bubbles[i]->Age()){
            std::swap(bubbles[bubbles.size()-1], bubbles[i]);
            delete bubbles[bubbles.size()-1];
            bubbles.pop_back();
        }
        //BUBBLE WASP INTERACTION
        for (uint j = 0; j < wasps.size(); ++j){
            if (abs(bubbles[i]->GetXSpeed()) > 2 && bubbles[i]->Distance(wasps[j]) < coli_dist){
                if (!wasps[j]->IsCaught()){
                    //CATCH WASP
                    wasps[j]->Catch();
                    wasps[j]->SetXSpeed((bubbles[i]->GetXSpeed()+3*wasps[j]->GetXSpeed())/4);
                    //REMOVE BUBBLE
                    std::swap(bubbles[bubbles.size()-1], bubbles[i]);
                    delete bubbles[bubbles.size()-1];
                    bubbles.pop_back();
                }
                if (wasps[j]->IsCaught()){
                    (wasps[j]->SetXSpeed( (41 * wasps[j]->GetXSpeed() + bubbles[i]->GetXSpeed())/42.0) );
                }
            }
        }
        //REVIVE PLAYERS
        for (uint j = 0; j < players.size(); ++j){
            if (bubbles[i]->Distance(players[j]) < coli_dist){
                if (!players[j]->IsAlive()){
                    //REVIVE PLAYER
                    players[j]->Revive();
                    //REMOVE BUBBLE
                    std::swap(bubbles[bubbles.size()-1], bubbles[i]);
                    delete bubbles[bubbles.size()-1];
                    bubbles.pop_back();
                }
            }
        }
    }
    //EXECUTE BUBBLEAF FUNCTIONS
    bubbleaf.ApplyMovement(ticks, sine);
    bubbleaf.Wrap();
    //GAME OVER
    if (!players[0]->IsAlive() && !players[1]->IsAlive() && wasps.size() < 99 && !(ticks%(10-(wasps.size()/10))) ){
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
    QPixmap composit = background;
    QPainter compositor(&composit);
    compositor.setRenderHint(QPainter::SmoothPixmapTransform);
    //DRAW BUBBLEAF
    bubbleaf.Draw(&compositor);
    //DRAW PLAYERS
    for(uint i = 0; i < players.size(); ++i) players[i]->Draw(&compositor);
    //DRAW WASPS
    for(uint i = 0; i < wasps.size(); ++i) wasps[i]->Draw(&compositor);
    //DRAW BUBBLES
    for(uint i = 0; i < bubbles.size(); ++i) bubbles[i]->Draw(&compositor, ticks, sine);

    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), composit);
}


//ON EVERY KEYS PRESS
void GameWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()){
        //BLIP KEYS PRESS CHECK
        case Qt::Key_Up     : players[0]->SetUp(true);
        break;
        case Qt::Key_Left   : players[0]->SetLeft(true);
        break;
        case Qt::Key_Right  : players[0]->SetRight(true);
        break;
        case Qt::Key_Control:   if (players[0]->IsAlive() && players[0]->GetChargeAmount() > 1.0){
                                    bubbles.push_back(players[0]->Shoot());
                                }
        break;

        //BLUP KEYS PRESS CHECK
        case Qt::Key_W      : players[1]->SetUp(true);
        break;
        case Qt::Key_A      : players[1]->SetLeft(true);
        break;
        case Qt::Key_D      : players[1]->SetRight(true);
        break;
        case Qt::Key_Space  :   if (players[1]->IsAlive() && players[1]->GetChargeAmount() > 1.0){
                                    bubbles.push_back(players[1]->Shoot());
                                }
        break;

        //SPAWN WASPS (1)
        case Qt::Key_1      : { Wasp*wasp = new Wasp();
                                wasps.push_back(wasp);
        }
        break;
        case Qt::Key_Escape : { close();
        }
        break;
        default :
        break;
    }
}


//ON EVERY KEYS RELEASE
void GameWidget::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()){
        //BLIP KEYS RELEASE CHECK
        case Qt::Key_Up    : players[0]->SetUp(false); break;
        case Qt::Key_Left  : players[0]->SetLeft(false); break;
        case Qt::Key_Right : players[0]->SetRight(false); break;
        //BLUP KEYS RELEASE CHECK
        case Qt::Key_W : players[1]->SetUp(false); break;
        case Qt::Key_A : players[1]->SetLeft(false); break;
        case Qt::Key_D : players[1]->SetRight(false); break;
        default : break;
    }
}

