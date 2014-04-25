#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

#include "player.h"
#include "bubble.h"

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
    /*std::vector<Player> m_players;
    std::vector<Bubble> m_bubbles;*/

private slots:
    void OnTimer();
};

#endif // GAMEWIDGET_H
