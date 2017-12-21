#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::SetPosition(sf::Vector2f position)
{
	m_Position = position;
}

sf::Vector2f Entity::GetPosition()
{
	return m_Position;
}