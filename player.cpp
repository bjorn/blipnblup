#include "player.h"
#include "bubble.h"
#include <stdio.h>

Player::Player(GameObject *parent, const char *img_path) :
    GameObject(parent, img_path),
    m_pressed_up(false),
    m_pressed_left(false),
    m_pressed_right(false),
    m_pressed_down(false),
    m_jump(12)
{
}

bool Player::GetUp()    const   {return m_pressed_up;}
bool Player::GetLeft()  const   {return m_pressed_left;}
bool Player::GetRight() const   {return m_pressed_right;}
bool Player::GetDown()  const   {return m_pressed_down;}

void Player::SetUp(bool state)    {m_pressed_up    = state;}
void Player::SetLeft(bool state)  {m_pressed_left  = state;}
void Player::SetRight(bool state) {m_pressed_right = state;}
void Player::SetDown(bool state)  {m_pressed_down  = state;}

//SHOOT BUBBLE
Bubble * Player::Shoot()
{
    ResetCharge();
    Bubble * bubble = new Bubble(this);
    bubble->SetX(GetX());
    bubble->SetY(GetY());
    bubble->SetYSpeed(0);
    bubble->SetXSpeed( (10*(-1+2*IsFacingRight() ))+(3*GetRight())-(3*GetLeft()) );
    return bubble;
}



//APPLY INPUT EFFECTS
void Player::ApplyKeys()
{
    if (IsAlive()){
        //JUMP
        if (GetUp() && IsOnGround()){
            SetOnGround(false);
            SetYSpeed(-m_jump);
        }
        //FORCE LEFT
        if (GetLeft()){
            FaceLeft();
            if (GetXSpeed() > -GetStep()){ SetXSpeed( GetXSpeed() - (0.25 + (0.75*IsOnGround())) );}
        }
        //FORCE RIGHT
        if (GetRight()){
            FaceRight();
            if (GetXSpeed() <  GetStep()){ SetXSpeed( GetXSpeed() + (0.25 + (0.75*IsOnGround())) );}
        }
    }
}

//MOVE PLAYER
void Player::ApplyMovement(const QPixmap& background)
{
    QImage sprite = GetSprite(0);
    int check_x = (GetX()+(sprite.width()/2));
    int check_y = (GetY()+sprite.height()-4);
    //COLLISION DETECTION TO THE LEFT
    if (GetXSpeed() < 0){
        for(int i = 0; i < -GetXSpeed(); ++i){
            if (--check_x < 0) check_x += 400;
            if (check_x > 399) check_x -= 400;
            if (--check_y < 0) check_y += 300;
            if (check_y > 299) check_y -= 300;
            const QRgb sidepixel = background.toImage().pixel(check_x, check_y);
            const int red = qRed(sidepixel);
            if ((!red % 2)){
                SetX(GetX()-i);
                SetXSpeed(0);
            }
        }
    }

    //COLLISION DETECTION TO THE RIGHT
    if (GetXSpeed() > 0){
        for(int i = 0; i < GetXSpeed(); ++i){
            if (++check_x < 0) check_x += 400;
            if (check_x > 399) check_x -= 400;
            if (--check_y < 0) check_y += 300;
            if (check_y > 299) check_y -= 300;
            const QRgb sidepixel = background.toImage().pixel(check_x, check_y);
            const int red = qRed(sidepixel);
            if ((!red % 2)){
                SetX(GetX()+i);
                SetXSpeed(0);
            }
        }
    }

    SetX(GetX()+GetXSpeed());
    SetY(GetY()+GetYSpeed());

    //SLOW DOWN
    if (IsOnGround()){ SetXSpeed(GetXSpeed() * 0.7); }
}
