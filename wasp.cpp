#include "wasp.h"
#include <cmath>

Wasp::Wasp(Foe *parent) :
    Foe(parent)
{
    QImage * sprite_caught = new QImage(":/graphics/wasp_caught.png");
    sprites.push_back(*sprite_caught);
}

//MOVE WASP
void Wasp::ApplyMovement(long ticks, std::vector<double> sine)
{
    if (!caught){
        int phase = floor(ticks+randomizer);
        x_speed = 1.2*sine[phase%512];
        x_speed = pow(x_speed,9);

        phase = floor((8*ticks)+randomizer);
        y_speed = sine[phase%512];

        if (x_speed > 0) facing_right = true;
        else             facing_right = false;
    }
    if (on_ground){
        x_speed  *= 0.97;
        rot_speed = 3*x_speed;
    }

    x += x_speed;
    y += y_speed;
    rot += rot_speed;
}
