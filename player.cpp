#include "player.h"
#include "bubble.h"
#include <stdio.h>

Player::Player(bool blup) :
    GameObject(),
    m_pressed_up(false),
    m_pressed_left(false),
    m_pressed_right(false),
    m_pressed_down(false),
    m_jump(12)
{
    int sprite_size = 64;
    SetHitdX(GetWidth()/2);
    SetHitdY(GetHeight()/2);
    QImage playerImage = QImage(":/graphics/blipnblup.png");
    for (int i = 0; i < (playerImage.width()/sprite_size); i++){
        AddSprite(playerImage.copy(
                      i*sprite_size, blup*sprite_size,
                      sprite_size, sprite_size));
    }
}

bool Player::GetUp()    const noexcept  {return m_pressed_up;}
bool Player::GetLeft()  const noexcept  {return m_pressed_left;}
bool Player::GetRight() const noexcept  {return m_pressed_right;}
bool Player::GetDown()  const noexcept  {return m_pressed_down;}

void Player::SetUp(bool state) noexcept     {m_pressed_up    = state;}
void Player::SetLeft(bool state) noexcept   {m_pressed_left  = state;}
void Player::SetRight(bool state) noexcept  {m_pressed_right = state;}
void Player::SetDown(bool state) noexcept   {m_pressed_down  = state;}

//SHOOT BUBBLE
Bubble * Player::Shoot()
{
    ResetCharge();
    Bubble * bubble = new Bubble();
    bubble->SetX(GetX());
    bubble->SetY(GetY());
    bubble->SetYSpeed(0);
    bubble->SetXSpeed( (10*(-1+2*IsFacingRight() ))+(3*GetRight())-(3*GetLeft()) );
    return bubble;
}



//APPLY INPUT EFFECTS
void Player::ApplyKeys() noexcept{
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
    int check_x = (GetX()+(GetWidth()/2));
    int check_y = (GetY()+GetHeight()-4);
    //COLLISION DETECTION TO THE LEFT
    if (GetXSpeed() < 0){
        for(int i = 0; i < -GetXSpeed(); ++i){
            if (--check_x < 0) check_x += background.width();
            if (check_x > background.width()-1) check_x -= background.width();
            if (--check_y < 0) check_y += background.height();
            if (check_y > background.height()-1) check_y -= background.height();
            const QRgb sidepixel = background.toImage().pixel(check_x, check_y);
            const int red = qRed(sidepixel);
            if ((!red % 2)){
                SetX(GetX()-i);
                SetXSpeed(0);
            }
        }
    }

    //COLLISION DETECTION TO THE RIGHT
    if (GetXSpeed() > 0) {
        for(int i = 0; i < GetXSpeed(); ++i){
            if (++check_x < 0) check_x += background.width();
            if (check_x > background.width()-1) check_x -= background.width();
            if (--check_y < 0) check_y += background.height();
            if (check_y > background.height()-1) check_y -= background.height();
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

void Player::Animate() noexcept{
    double abs_x_speed = GetXSpeed();
    if (abs_x_speed < 0) abs_x_speed = -abs_x_speed;
    m_frame_progression += (abs_x_speed/10.0);

    int next_frame = GetCurrentFrame();
    if (m_frame_progression > 1){
        m_frame_progression = 0;
        next_frame = GetCurrentFrame()+1;
        if (next_frame >= GetSpritesAmount()-2) next_frame = 0;
    }
    if (!IsAlive()){
        next_frame = 4;
    }
    else if (GetChargeAmount() < 0.3){
        next_frame = 3;
    }
    else if (abs_x_speed < 1){
        next_frame = 0;
    }
    SetCurrentFrame(next_frame);
}
