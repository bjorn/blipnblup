#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

#include "player.h"
#include "bubble.h"
#include "wasp.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
private:
    //BACKGROUND

    QPixmap background;
    //GENERAL MEMBER VALUES
    double ticks;
    int grav;

    //PLAYERS
    Player blip;
    Player blup;

    //VECTORS
    std::vector<Player*> players;
    std::vector<Bubble*> bubbles;
    std::vector<Wasp*>   wasps;

private slots:
    void OnTimer();
};

#endif // GAMEWIDGET_H
