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
    const int   m_charged = 10;

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
    void    SetX(const double x) noexcept;
    double  GetX() const noexcept;
    void    SetY(const double y) noexcept;
    double  GetY() const noexcept;

    void    SetHitdX(const double hit_dx) noexcept;
    double  GetHitdX() const noexcept;
    void    SetHitdY(const double hit_dy) noexcept;
    double  GetHitdY() const noexcept;

    void    SetXSpeed(const double m_x_speed) noexcept;
    double  GetXSpeed() const noexcept;
    void    SetYSpeed(const double m_y_speed) noexcept;
    double  GetYSpeed() const noexcept;

    void    SetRotation(const double rot) noexcept;
    double  GetRotation() const noexcept;
    void    SetRotSpeed(const double rot_speed) noexcept;
    double  GetRotSpeed() const noexcept;

    int     GetStep() const noexcept;
    int     GetMaxYSpeed() const noexcept;
    int     Randomize() const noexcept;
    void    Kill() noexcept;
    void    Revive() noexcept;
    bool    IsAlive() const noexcept;
    void    Charge() noexcept;
    void    ResetCharge() noexcept;
    bool    IsCharged() const noexcept;
    void    FaceLeft() noexcept;
    void    FaceRight() noexcept;
    bool    IsFacingRight() const noexcept;
    void    SetOnGround(const bool state) noexcept;
    bool    IsOnGround() const noexcept;
    void    AddSprite(const QImage sprite) noexcept;
    QImage  GetSprite(const int sprite_index) const noexcept;

    void   Fall(const QPixmap& background, const double grav) noexcept;
    void   ApplyMovement() noexcept;
    void   Wrap() noexcept;
    void   Draw(QPainter * const painter) noexcept;
    double Distance(const GameObject * const other) const noexcept;
};

#endif // GAMEOBJECT_H
