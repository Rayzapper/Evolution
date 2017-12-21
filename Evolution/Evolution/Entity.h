#ifndef RAYZAPPER_ENTITY_H
#define RAYZAPPER_ENTITY_H

#include <SFML/Graphics.hpp>
#include "InputManager.h"

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Update(float dt, sf::Vector2i mousePosition) = 0;
	virtual void Render(sf::RenderWindow *window) = 0;

	virtual void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();
protected:
	sf::Vector2f m_Position;
};

#endif