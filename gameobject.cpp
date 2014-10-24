#include "gameobject.h"
#include <QPainter>
#include <cmath>

GameObject::GameObject() :
    QObject(),

    m_randomizer(rand()%512),
    m_charge(0),
    m_charged(23),

    m_x(0.0),
    m_y(0.0),
    m_width(32),
    m_height(32),
    m_hit_dx(16),
    m_hit_dy(16),
    m_x_speed(0.0),
    m_y_speed(0.0),
    m_rot(0.0),
    m_rot_speed(0.0),

    m_step(3),
    m_dead(false),
    m_on_ground(false),
    m_facing_right(true),

    m_current_frame(0),
    m_frame_progression(0)
{
    m_charge = m_charged;
}

//SIMPLE FUNCTIONS
void    GameObject::SetX(const double x) noexcept   {m_x = x;}
double  GameObject::GetX() const noexcept           {return m_x;}
void    GameObject::SetY(const double y) noexcept   {m_y = y;}
double  GameObject::GetY() const noexcept           {return m_y;}

void    GameObject::SetWidth(const int width) noexcept      {m_width = width;}
int     GameObject::GetWidth() const noexcept               {return m_width;}
void    GameObject::SetHeight(const int height) noexcept    {m_height = height;}
int     GameObject::GetHeight() const noexcept              {return m_height;}

void    GameObject::SetHitdX(const double hit_dx) noexcept  {m_hit_dx = hit_dx;}
double  GameObject::GetHitdX() const noexcept               {return m_hit_dx;}
void    GameObject::SetHitdY(const double hit_dy) noexcept  {m_hit_dy = hit_dy;}
double  GameObject::GetHitdY() const noexcept               {return m_hit_dy;}

void    GameObject::SetXSpeed(const double x_speed) noexcept    {m_x_speed = x_speed;}
double  GameObject::GetXSpeed() const noexcept                  {return m_x_speed;}
void    GameObject::SetYSpeed(const double y_speed) noexcept    {m_y_speed = y_speed;}
double  GameObject::GetYSpeed() const noexcept                  {return m_y_speed;}

void    GameObject::SetRotation(const double rot) noexcept          {m_rot = rot;}
double  GameObject::GetRotation() const noexcept                    {return m_rot;}
void    GameObject::SetRotSpeed(const double rot_speed) noexcept    {m_rot_speed = rot_speed;}
double  GameObject::GetRotSpeed() const noexcept                    {return m_rot_speed;}

int     GameObject::GetStep() const noexcept                {return m_step;}
int     GameObject::GetMaxYSpeed() const noexcept           {return m_max_y_speed;}
int     GameObject::Randomize() const noexcept              {return m_randomizer;}
void    GameObject::Kill() noexcept                         {m_dead = true;  m_y_speed = -1;}
void    GameObject::Revive() noexcept                       {m_dead = false; m_y_speed = -1; SetCurrentFrame(0);}
bool    GameObject::IsAlive() const noexcept                {return !m_dead;}
void    GameObject::Charge() noexcept                       {++m_charge;}
void    GameObject::ResetCharge() noexcept                  {m_charge = 0;}
double  GameObject::GetChargeAmount() const noexcept        {return  (double)m_charge / m_charged;}
void    GameObject::FaceLeft() noexcept                     {m_facing_right = false;}
void    GameObject::FaceRight() noexcept                    {m_facing_right = true;}
bool    GameObject::IsFacingRight() const noexcept          {return m_facing_right;}
void    GameObject::SetOnGround(const bool state) noexcept  {m_on_ground = state;}
bool    GameObject::IsOnGround() const noexcept             {return m_on_ground;}

void    GameObject::AddSprite(const QImage sprite) noexcept             {m_sprites.push_back(sprite);}
QImage  GameObject::GetSprite(const int sprite_index) const noexcept    {return m_sprites[sprite_index];}
int     GameObject::GetSpritesAmount() const noexcept{return m_sprites.size();}
void    GameObject::SetCurrentFrame(const int frame) noexcept {m_current_frame = frame;}
int     GameObject::GetCurrentFrame() const noexcept {return m_current_frame;}

//CHECK DISTANCE BETWEEN TWO GAMEOBJECTS
//HARDCODED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NEED MORE FLEXIBLE WRAP FUNCTION
double GameObject::Distance(const GameObject * const other) const noexcept
{
    int dx, dy;
    dx = (other->GetX() + other->GetHitdX()) - (GetX() + GetHitdX());
    dy = (other->GetY() + other->GetHitdY()) - (GetY() + GetHitdY());
    dx = abs(dx);
    dy = abs(dy);
    if (dx > 199) dx = 400 - dx;
    if (dy > 149) dy = 300 - dy;
    return sqrt(pow(dx,2)+pow(dy,2));
}

//DOWNWARD PIXEL COLLITION
void GameObject::Fall(const QPixmap& background,const double grav) noexcept
{
    int check_x = (m_x+(GetWidth()/2));
    check_x = check_x%background.width();
    int check_y = (m_y+(GetHeight())-6);
    check_y = check_y%background.height();
    const QRgb floorpixel = background.toImage().pixel( check_x , check_y );
    const int red = qRed(floorpixel);
    if (!(red % 2))
    {
        m_on_ground = false;
        if (m_y_speed < m_max_y_speed) m_y_speed += grav;
    }

    if(m_y_speed >= 0)
    {
        for(int i = -(m_step+1); i <= m_y_speed; ++i)
        {
            check_y = (check_y+1)%background.height();

            const QRgb floorpixel = background.toImage().pixel( check_x , check_y);
            const int red = qRed(floorpixel);
            if (red % 2)
            {
                m_y_speed = 0;
                m_y += i;
                m_on_ground = true;
            }
        }
    }
}


//APPLY MOVEMENT
void GameObject::ApplyMovement() noexcept
{
    m_x += m_x_speed;
    m_y += m_y_speed;
}


//POSITION WRAPPING
//HARDCODED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NEED MORE FLEXIBLE WRAP FUNCTION
void GameObject::Wrap() noexcept
{
    if( m_x <  0)                    m_x = 400; //LEFT TO RIGHT
    if( m_x > 400)                   m_x =   0; //RIGHT TO LEFT
    if((m_y > 300) && (m_y_speed > 0)) m_y =   0; //BOTTOM TO TOP
    if((m_y <   0)   && (m_y_speed < 0)) m_y = 300; //TOP TO BOTTOM
}

//DRAW GAMEOBJECT
void GameObject::Draw(QPainter * painter) noexcept
{
    int device_width = painter->device()->width();
    int device_height = painter->device()->height();
    QTransform matrix;
    matrix.scale(1-(2*!m_facing_right), 1);
    QPixmap sprite_t = QPixmap::fromImage( GetSprite(GetCurrentFrame()).transformed(matrix) );
    const int width  = GetWidth();
    const int height = GetHeight();
    painter->drawPixmap( m_x, m_y, width, height, sprite_t);
    //SPRITE WRAPPING
    //LEFT RIGHT
    if( m_x <   0)          painter->drawPixmap(m_x+device_width, m_y    , width, height, sprite_t);
    if( m_x > device_width - width)  painter->drawPixmap(m_x-device_width, m_y    , width, height, sprite_t);
    //TOP BOTTOM
    if( m_y <   0)          painter->drawPixmap(m_x    , m_y+device_height, width, height, sprite_t);
    if( m_y > device_height - height) painter->drawPixmap(m_x    , m_y-device_height, width, height, sprite_t);
    //CORNERS
    if(m_x <   0         && m_y <   0)          painter->drawPixmap(m_x+device_width, m_y+device_height, width, height, sprite_t);
    if(m_x > device_width - width && m_y <   0)          painter->drawPixmap(m_x-device_width, m_y+device_height, width, height, sprite_t);
    if(m_x > device_width - width && m_y > device_height - height) painter->drawPixmap(m_x-device_width, m_y-device_height, width, height, sprite_t);
    if(m_x <   0         && m_y > device_height - height) painter->drawPixmap(m_x+device_width, m_y-device_height, width, height, sprite_t);
}
