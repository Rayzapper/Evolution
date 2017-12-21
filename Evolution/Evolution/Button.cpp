#include "Button.h"

Button::Button(sf::String buttonString, sf::Font *buttonFont, short ID)
	: m_Font(buttonFont),
	m_ID(ID)
{
	m_Shape.setFillColor(sf::Color(200, 200, 200, 255));
	m_Shape.setOutlineColor(sf::Color::Black);
	m_Shape.setOutlineThickness(-1);
	m_Shape.setSize(sf::Vector2f(200, 40));
	m_Hitbox = sf::IntRect(0, 0, m_Shape.getSize().x, m_Shape.getSize().y);

	m_ButtonText.setString(buttonString);
	m_ButtonText.setFillColor(sf::Color::Black);
	m_ButtonText.setCharacterSize(20);
	m_ButtonText.setFont(*m_Font);
}

Button::~Button()
{

}

void Button::Update(float dt, sf::Vector2i mousePosition)
{
	m_MousePosition = sf::Vector2i(mousePosition);
	m_Mouseover = m_Hitbox.contains(m_MousePosition);
}

void Button::Render(sf::RenderWindow *window)
{
	window->draw(m_Shape);
	window->draw(m_ButtonText);
}

void Button::SetPosition(sf::Vector2f position)
{
	m_Position = position;
	m_Shape.setPosition(m_Position);
	m_ButtonText.setPosition(m_Position + sf::Vector2f(5, 5));
	m_Hitbox.left = m_Position.x;
	m_Hitbox.top = m_Position.y;
}

void Button::SetID(short ID)
{
	m_ID = ID;
}

void Button::SetString(sf::String newString)
{
	m_ButtonText.setString(newString);
}

bool Button::GetMouseover()
{
	return m_Mouseover;
}

short Button::GetID() const
{
	return m_ID;
}