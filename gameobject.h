#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QImage>
#include <QPixmap>

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = 0, const char *img_path = ":graphics/wasp.png");
    virtual ~GameObject() noexcept {}
private:
    QImage      m_sprite;
    const int   m_randomizer;
    int         m_charge;
    const int   m_fullcharge = 30;

    double m_x;
    double m_y;
    int    m_hit_dx;
    int    m_hit_dy;
    double m_x_speed;
    double m_y_speed;
    double m_rot;
    double m_rot_speed;

    const int           m_step;
    static const int    m_max_y_speed = 42;

    bool   m_dead;
    bool   m_on_ground;
    bool   m_facing_right;

    std::vector<QImage> m_sprites;

public:
    void    SetX(const double x);
    double  GetX() const;
    void    SetY(const double y);
    double  GetY() const;

    void    SetHitdX(const double hit_dx);
    double  GetHitdX() const;
    void    SetHitdY(const double hit_dy);
    double  GetHitdY() const;

    void    SetXSpeed(const double m_x_speed);
    double  GetXSpeed() const;
    void    SetYSpeed(const double m_y_speed);
    double  GetYSpeed() const;

    void    SetRotation(const double rot);
    double  GetRotation() const;
    void    SetRotSpeed(const double rot_speed);
    double  GetRotSpeed() const;

    int     GetStep() const;
    int     GetMaxYSpeed() const;
    int     Randomize() const;
    void    Kill();
    void    Revive();
    bool    IsAlive() const;
    void    Charge();
    void    ResetCharge();
    bool    IsCharged() const;  
    void    FaceLeft();
    void    FaceRight();
    bool    IsFacingRight() const;
    void    SetOnGround(const bool state);
    bool    IsOnGround() const;
    void    AddSprite(const QImage sprite);
    QImage  GetSprite(const int sprite_index) const;

    void   Fall(const QPixmap& background, const double grav);
    void   ApplyMovement();
    void   Wrap();
    void   Draw(QPainter * const painter);
    double Distance(const GameObject * const other) const;
};

#endif // GAMEOBJECT_H
