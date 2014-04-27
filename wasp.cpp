#include "wasp.h"
#include <cmath>

Wasp::Wasp(GameObject *parent) :
    GameObject(parent)
{
}

//MOVE WASP
void Wasp::ApplyMovement(long ticks)
{
    x_speed = 3*sin( (0.015*ticks)+randomizer );
    y_speed = 2*sin( (0.110*ticks)+randomizer );
    if (x_speed > 0) facing_right = true;
    if (x_speed < 0) facing_right = false;
    x += x_speed;
    y += y_speed;
}