#include "wasp.h"
#include <cmath>

Wasp::Wasp(GameObject *parent) :
    GameObject(parent)
{
}

void Wasp::ApplyMovement(long ticks)
{
    x_speed = 6*sin( (0.031*ticks)+randomizer );
    y_speed = 4*sin( (0.210*ticks)+randomizer );
    if (x_speed > 0) facing_right = true;
    if (x_speed < 0) facing_right = false;
    x += x_speed;
    y += y_speed;
}
