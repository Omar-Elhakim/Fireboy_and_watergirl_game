#pragma once
#include <SFML/Graphics.hpp>
class collison
{
public:
	collison(sf::RectangleShape& body);

	~collison();

	bool checkcollison(collison& other, float push);
	sf::Vector2f GetPostion() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
private:
	sf::RectangleShape& body;
};

