#include "wasp.h"
#include <cmath>

Wasp::Wasp(Foe *parent) :
    Foe(parent)
{
    QImage sprite_caught = QImage(":/graphics/wasp_caught.png");
    AddSprite(sprite_caught);
}

//MOVE WASP
void Wasp::ApplyMovement(const int ticks, const std::vector<double>& sine)
{
    if (!IsCaught()){
        int phase = floor((1+IsAngry())*ticks+Randomize());
        SetXSpeed( (1.2+(0.2*IsAngry()))*sine[phase%512] );
        SetXSpeed( pow(GetXSpeed(),7-(2*IsAngry())) );

        phase = floor((8*ticks)+Randomize());
        SetYSpeed( (1+IsAngry())*sine[phase%512] );

        if (GetXSpeed() > 0){ FaceRight(); }
        if (GetXSpeed() < 0){ FaceLeft();  }
    }
    if (IsOnGround()){
        SetXSpeed( GetXSpeed() * 0.97 );
        SetRotSpeed( 3 * GetXSpeed() );
    }
    SetX(GetX()+GetXSpeed());
    SetY(GetY()+GetYSpeed());
    SetRotation(GetRotation()+GetRotSpeed());
}
