#include "Target.h"

Target::Target(Vector2u windowSize)
{
    shape.setFillColor(Color(100, 250, 50));
    shape.setRadius(20);

    shape.setPosition(rand() % 700 + 50, rand() % 500 + 50);
}


void Target::increase()
{
    shape.setRadius(shape.getRadius() + 0.1);

    shape.setPosition(shape.getPosition().x - 0.1, shape.getPosition().y - 0.1);
}

void Target::draw(RenderWindow &window)
{
    window.draw(shape);
}

bool Target::isHit(Vector2i position)
{
    if (position.x >= shape.getPosition().x
        && position.x <= (shape.getPosition().x + shape.getLocalBounds().width)
        && position.y >= shape.getPosition().y
        && position.y <= (shape.getPosition().y + shape.getLocalBounds().height)) {

        return true;
    } else {
        return false;
    }
}
