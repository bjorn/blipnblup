#include "wasp.h"
#include <cmath>

Wasp::Wasp() :
    Foe()
{
    SetWidth(42);
    SetHeight(42);
    int sprite_size = 84;
    QImage waspImage = QImage(":/graphics/wasp.png");
    for (int i = 0; i < (waspImage.width()/sprite_size); i++){
        AddSprite(waspImage.copy(
                      i*sprite_size, IsAngry()*sprite_size,
                      sprite_size, sprite_size));
    }
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
    else SetCurrentFrame(GetSpritesAmount()-1);
    if (IsOnGround()){
        SetXSpeed( GetXSpeed() * 0.97 );
        SetRotSpeed( 3 * GetXSpeed() );
    }
    SetX(GetX()+GetXSpeed());
    SetY(GetY()+GetYSpeed());
    SetRotation(GetRotation()+GetRotSpeed());
}

void Wasp::Animate() noexcept{
    if (!IsCaught()) m_frame_progression += 0.5;
    if (m_frame_progression > 1){
        m_frame_progression = 0;
        int next_frame = GetCurrentFrame()+1;
        if (next_frame > 1) next_frame = 0;
        SetCurrentFrame(next_frame);
    }
}
