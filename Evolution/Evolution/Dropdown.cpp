#include "Dropdown.h"

Dropdown::Dropdown(sf::String nameString, sf::Font *font, short ID)
	: Button(nameString, font, ID)
{

}

Dropdown::~Dropdown()
{
	for each (Button *b in m_Buttons)
	{
		delete b;
	}
	m_Buttons.clear();
}

void Dropdown::Update(float dt, sf::Vector2i mousePosition)
{
	m_MousePosition = sf::Vector2i(mousePosition);

	if (m_Active)
	{
		m_Hitbox.height = 40 * m_Buttons.size() + 40;
	}
	else
	{
		m_Hitbox.height = 40;
	}

	m_Mouseover = m_Hitbox.contains(m_MousePosition);
	if (!m_Mouseover)
	{
		m_Active = false;
	}
	for each (Button *b in m_Buttons)
	{
		b->Update(dt, mousePosition);
	}
}

void Dropdown::Render(sf::RenderWindow *window)
{
	window->draw(m_Shape);
	window->draw(m_ButtonText);
	if (m_Active)
	{
		for each (Button *b in m_Buttons)
		{
			b->Render(window);
		}
	}
}

void Dropdown::AddButton(Button *button)
{
	button->SetPosition(m_Position + sf::Vector2f(0, m_Buttons.size() * 40 + 40));

	m_Buttons.push_back(button);
}

void Dropdown::SetActive(bool active)
{
	m_Active = active;
}

bool Dropdown::GetActive() const
{
	return m_Active;
}

vector<Button*> Dropdown::GetButtons()
{
	return m_Buttons;
}
