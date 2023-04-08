#include "collison.h"

collison::collison(sf::RectangleShape& body):
    body(body)
{
}

collison::~collison()
{
}

bool collison::checkcollison(collison& other, float push)

{
    sf::Vector2f otherpostion = other. GetPostion();
    sf::Vector2f otherHalfSize = other.GetPostion();
    sf::Vector2f thispostion = GetPostion();
    sf::Vector2f thisHalfSize = GetPostion();
    float deltax = otherpostion.x - thispostion.x;
    float deltax = otherpostion.y - thispostion.y;
    float intersectX = abs(deltax) - (otherHalfSize.x + thisHalfSize.x);
    float intersecty = abs(delta) - (otherHalfSize .y + thisHalfSize.y);

    return false;
}
