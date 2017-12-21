#ifndef RAYZAPPER_DROPDOWN_H
#define RAYZAPPER_DROPDOWN_H

#include "Button.h"

using namespace std;

class Dropdown : public Button
{
public:
	Dropdown(sf::String nameString, sf::Font *font, short ID);
	~Dropdown();
	virtual void Update(float dt, sf::Vector2i mousePosition);
	virtual void Render(sf::RenderWindow *window);
	void AddButton(Button *button);
	void SetActive(bool active);
	bool GetActive() const;
	vector<Button*> GetButtons();
private:
	vector<Button*> m_Buttons;
	bool m_Active = false;
};

#endif