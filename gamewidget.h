#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

#include "player.h"
#include "bubbleaf.h"

struct Wasp;
struct Bubble;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
private:
    //GLOBAL PIXMAPS
    QPixmap background;
    QPixmap full_background;
    QPixmap composit;

    //GENERAL MEMBER VALUES
    long    ticks;
    double  grav;

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
