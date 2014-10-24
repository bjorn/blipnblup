#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGLWidget>

#include "player.h"
#include "bubbleaf.h"

struct Player;
struct Wasp;


class GameWidget : public QGLWidget
{
    Q_OBJECT
public:
    GameWidget();
public slots:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
private:
    //PIXMAPS
    const QPixmap background;

    //GENERAL MEMBER VALUES
    long            ticks;
    const double    grav;

    //PLAYERS
    Player  blip;
    Player  blup;

    //BUBBLEAF
    Bubbleaf bubbleaf;

    //VECTORS
    std::vector<double>  sine;

    std::vector<Player*> players;
    std::vector<Bubble*> bubbles;
    std::vector<Wasp*>   wasps;

private slots:
    void    OnTimer();
};

#endif // GAMEWIDGET_H
