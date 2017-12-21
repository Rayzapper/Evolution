#ifndef RAYZAPPER_BUTTON_H
#define RAYZAPPER_BUTTON_H

#include "Entity.h"

class Button : public Entity
{
public:
	Button(sf::String buttonString, sf::Font *buttonFont, short ID);
	~Button();
	virtual void Update(float dt, sf::Vector2i mousePosition);
	virtual void Render(sf::RenderWindow *window);

	virtual void SetPosition(sf::Vector2f position);
	void SetID(short ID);
	void SetString(sf::String newString);
	bool GetMouseover();
	short GetID() const;
protected:
	sf::RectangleShape m_Shape;
	sf::IntRect m_Hitbox;
	sf::Text m_ButtonText;
	sf::Font *m_Font;
	sf::Vector2i m_MousePosition;
	short m_ID;
	bool m_Mouseover = false;
};

#endif