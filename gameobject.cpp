#include "gameobject.h"
#include <QPainter>
#include <cmath>

GameObject::GameObject(QObject *parent, const char *img_path) :
    QObject(parent),

    m_sprite(img_path),
    m_randomizer(rand()%512),
    m_charge(10),

    m_x(0.0),
    m_y(0.0),
    m_hit_dx(0),
    m_hit_dy(0),
    m_x_speed(0.0),
    m_y_speed(0.0),
    m_rot(0.0),
    m_rot_speed(0.0),

    m_dead(false),
    m_on_ground(false),
    m_facing_right(true),
    m_step(3)
{
    m_sprites.push_back(m_sprite);
    m_hit_dx = m_sprite.width() /2;
    m_hit_dy = m_sprite.height()/2;
}

//SIMPLE FUNCTIONS
void    GameObject::SetX(const double x) {m_x = x;}
double  GameObject::GetX() const         {return m_x;}
void    GameObject::SetY(const double y) {m_y = y;}
double  GameObject::GetY() const         {return m_y;}

void    GameObject::SetHitdX(const double hit_dx)   {m_hit_dx = hit_dx;}
double  GameObject::GetHitdX() const                {return m_hit_dx;}
void    GameObject::SetHitdY(const double hit_dy)   {m_hit_dy = hit_dy;}
double  GameObject::GetHitdY() const                {return m_hit_dy;}

void    GameObject::SetXSpeed(const double x_speed) {m_x_speed = x_speed;}
double  GameObject::GetXSpeed() const               {return m_x_speed;}
void    GameObject::SetYSpeed(const double y_speed) {m_y_speed = y_speed;}
double  GameObject::GetYSpeed() const               {return m_y_speed;}

void    GameObject::SetRotation(const double rot)       {m_rot = rot;}
double  GameObject::GetRotation() const                 {return m_rot;}
void    GameObject::SetRotSpeed(const double rot_speed) {m_rot_speed = rot_speed;}
double  GameObject::GetRotSpeed() const                 {return m_rot_speed;}

int     GameObject::GetStep() const                 {return m_step;}
int     GameObject::GetMaxYSpeed() const            {return m_max_y_speed;}
int     GameObject::Randomize() const               {return m_randomizer;}
void    GameObject::Kill()                          {m_dead = true;  m_y_speed = -3;}
void    GameObject::Revive()                        {m_dead = false; m_y_speed = -3;}
bool    GameObject::IsAlive()   const               {return !m_dead;}
void    GameObject::Charge()                        {++m_charge;}
void    GameObject::ResetCharge()                   {m_charge = 0;}
bool    GameObject::IsCharged() const               {if (m_charge > m_fullcharge) return true;}
void    GameObject::FaceLeft()                      {m_facing_right = false;}
void    GameObject::FaceRight()                     {m_facing_right = true;}
bool    GameObject::IsFacingRight() const           {return m_facing_right;}
void    GameObject::SetOnGround(const bool state)   {m_on_ground = state;}
bool    GameObject::IsOnGround() const              {return m_on_ground;}

void    GameObject::AddSprite(const QImage sprite)        {m_sprites.push_back(sprite);}
QImage  GameObject::GetSprite(const int sprite_index) const {return m_sprites[sprite_index];}

//CHECK DISTANCE BETWEEN TWO GAMEOBJECTS
double GameObject::Distance(const GameObject * const other) const
{
    int dx, dy;
    dx = (other->GetX() + other->GetHitdX()) - (GetX() + GetHitdX());
    dy = (other->GetY() + other->GetHitdY()) - (GetY() + GetHitdY());
    dx = dx%(400-23);
    dy = dy%(300-23);
    return sqrt(pow(dx,2)+pow(dy,2));
}

//DOWNWARD PIXEL COLLITION
void GameObject::Fall(const QPixmap& background,const double grav)
{
    int check_x = (m_x+(m_sprite.width()/2));
    check_x = check_x%400;
    int check_y = (m_y+(m_sprite.height())-2);
    check_y = check_y%300;
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
            const QRgb floorpixel = background.toImage().pixel( check_x , check_y+i );
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
void GameObject::ApplyMovement()
{
    m_x += m_x_speed;
    m_y += m_y_speed;
}


//POSITION WRAPPING
void GameObject::Wrap()
{
    if( m_x <  0)                    m_x = 400; //LEFT TO RIGHT
    if( m_x > 400)                   m_x =   0; //RIGHT TO LEFT
    if((m_y > 300) && (m_y_speed > 0)) m_y =   0; //BOTTOM TO TOP
    if((m_y <   0)   && (m_y_speed < 0)) m_y = 300; //TOP TO BOTTOM
}

//DRAW GAMEOBJECT
void GameObject::Draw(QPainter * painter)
{
    QTransform matrix;
    matrix.scale(1-(2*!m_facing_right), 1);
    matrix.rotate(m_rot-90*m_dead);
    QPixmap sprite_t = QPixmap::fromImage(m_sprites[0].transformed(matrix));
    const int width  = sprite_t.width();
    const int height = sprite_t.height();
    painter->drawPixmap( m_x, m_y, width, height, sprite_t);
    //SPRITE WRAPPING
    //LEFT RIGHT
    if( m_x <   0)          painter->drawPixmap(m_x+400, m_y    , width, height, sprite_t);
    if( m_x > 400 - width)  painter->drawPixmap(m_x-400, m_y    , width, height, sprite_t);
    //TOP BOTTOM
    if( m_y <   0)          painter->drawPixmap(m_x    , m_y+300, width, height, sprite_t);
    if( m_y > 300 - height) painter->drawPixmap(m_x    , m_y-300, width, height, sprite_t);
    //CORNERS
    if(m_x <   0         && m_y <   0)          painter->drawPixmap(m_x+400, m_y+300, width, height, sprite_t);
    if(m_x > 400 - width && m_y <   0)          painter->drawPixmap(m_x-400, m_y+300, width, height, sprite_t);
    if(m_x > 400 - width && m_y > 300 - height) painter->drawPixmap(m_x-400, m_y-300, width, height, sprite_t);
    if(m_x <   0         && m_y > 300 - height) painter->drawPixmap(m_x+400, m_y-300, width, height, sprite_t);
}
