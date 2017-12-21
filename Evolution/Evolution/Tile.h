#ifndef	RAYZAPPER_TILE_H
#define RAYZAPPER_TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile(short ID);
	~Tile();
	virtual void Update(float dt, sf::Vector2i mousePosition);
	virtual void Render(sf::RenderWindow *window);
	void SetID(short ID);
	void SetNeighbors(Tile *neighbors[8]);
	virtual void SetPosition(sf::Vector2f position);
	short GetID() const;
	bool GetMouseover();
	Tile* GetNeighbor(int direction);
private:
	sf::RectangleShape m_Shape;
	sf::IntRect m_Hitbox;
	sf::Vector2i m_MousePosition;
	short m_ID;
	bool m_Mouseover = false, m_Active = true;
	Tile *m_Neighbors[8];
};

#endif