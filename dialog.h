#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <vector>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
private slots:
    void OnTimer();
    void ApplyKeys();
    void ApplyMovement();
    void Fall();
    void Wrap();
private:
    Ui::Dialog *ui;

    double ticks;
    char grav;
    char check_x;
    char check_y;

    //BLIP MEMBER VALUES
    int blip_x;
    int blip_y;
    int blip_yspeed;
    char blip_step;
    bool blip_stand;
    bool pressed_up;
    bool pressed_left;
    bool pressed_right;
    bool pressed_down;

    //BLUP MEMBER VALUES
    int blup_x;
    int blup_y;
    int blup_yspeed;
    char blup_step;
    bool blup_stand;
    bool pressed_w;
    bool pressed_a;
    bool pressed_s;
    bool pressed_d;

    std::vector<QLabel *> m_bubbles;
};

#endif // DIALOG_H
