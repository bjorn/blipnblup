#include "wasp.h"
#include <cmath>

Wasp::Wasp(GameObject *parent) :
    GameObject(parent)
{
    x = rand() % 400;
    y = rand() % 300;
}

//MOVE WASP
void Wasp::ApplyMovement(long ticks)
{
    x_speed = 1.2*sin( (0.015*ticks)+randomizer );
    x_speed *= x_speed*x_speed;
    x_speed *= x_speed*x_speed;

    y_speed = (sin( (0.110*ticks)+randomizer ));

    if (x_speed > 0) facing_right = true;
    else             facing_right = false;

    x += x_speed;
    y += y_speed;
}
