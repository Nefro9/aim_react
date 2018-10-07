#ifndef TARGET_H
#define TARGET_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Target
{
    public:
        CircleShape shape;
        Target(Vector2u windowSize);

        bool isHit(Vector2i position);
        void increase();
        void draw(RenderWindow &window);
};

#endif // TARGET_H
