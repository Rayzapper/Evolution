#include "Game.h"
#include "InputManager.h"
#include <string>
#include <iostream>

Game::Game()
{

}

Game::~Game()
{
	for each (Button *b in m_Buttons)
	{
		delete b;
	}
	m_Buttons.clear();

	for each (Dropdown *d in m_Dropdowns)
	{
		delete d;
	}
	m_Dropdowns.clear();
	delete m_Pathfinder;
	delete m_Window;
}

void Game::Run()
{
	int windowWidth = 1600, windowHeight = 900;
	sf::Vector2i mouseScreenPosition;

	// Window creation
	string programName = "EvolutionAI";
	m_Window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), programName, sf::Style::Default);
	m_Window->setFramerateLimit(60);
	m_Window->setVerticalSyncEnabled(true);

	m_Pathfinder = new Pathfinder(&m_TileMap);

	SetupButtons();
	SetupMap();

	m_StartTile = m_TileMap[12][2];
	m_EndTile = m_TileMap[0][19];

	sf::Clock deltaClock;

	m_Population.GenerateRandomPopulation(m_PopSize, m_GenomeSize);
	for each (Individual *i in m_Population.GetIndividuals())
	{
		i->SetCurrentTile(m_StartTile);
	}

	float dt;

	bool running = true, focus = true;

	while (running)
	{
		dt = deltaClock.restart().asSeconds();

		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			if (event.type == sf::Event::GainedFocus)
				focus = true;
			if (event.type == sf::Event::LostFocus)
				focus = false;
			if (event.type == sf::Event::Resized)
			{
				int newWidth = event.size.width, newHeight = event.size.height;
			}
			if (event.type == sf::Event::MouseWheelMoved)
				InputManager::GetInstance().SetMouseWheelValue(event.mouseWheelScroll.wheel);
		}

		if (focus)
		{
			InputManager::GetInstance().Update();

			mouseScreenPosition = sf::Mouse::getPosition(*m_Window);

			// --------------------Update--------------------

			Update(dt, mouseScreenPosition);

			// --------------------Render--------------------
			m_Window->clear();

			Render();

			// End frame
			m_Window->display();

			InputManager::GetInstance().Clear();
		}
		else
		{
			sf::Time time = sf::milliseconds(100);
			sf::sleep(time);
		}
	}
}

void Game::Update(float dt, sf::Vector2i mousePosition)
{
	Button *clickedButton = nullptr;
	bool mouseClick, rightClick;
	mouseClick = InputManager::GetInstance().GetInput(MOUSELEFTCLICK);
	rightClick = InputManager::GetInstance().GetInput(MOUSERIGHTCLICK);

	for each (Button *b in m_Buttons)
	{
		b->Update(dt, mousePosition);
		if (mouseClick && !m_DropdownIsActive)
		{
			if (b->GetMouseover())
			{
				clickedButton = b;
			}
		}
	}

	for each (vector<Tile*> tileRow in m_TileMap)
	{
		for each (Tile *t in tileRow)
		{
			t->Update(dt, mousePosition);

			if (t->GetID() != 1)
			{
				if (mouseClick)
				{
					if (t->GetMouseover())
					{
							
					}
				}
				else if (rightClick)
				{
					if (t->GetMouseover())
					{
							
					}
				}
			}
		}
	}

	for each (Dropdown *d in m_Dropdowns)
	{
		d->Update(dt, mousePosition);
		if (mouseClick)
		{
			if (d->GetMouseover())
			{
				if (m_DropdownIsActive)
				{
					for each (Button *b in d->GetButtons())
					{
						if (b->GetMouseover())
						{
							clickedButton = b;
						}
					}
				}

				if (d->GetActive())
				{
					d->SetActive(false);
					m_DropdownIsActive = false;
				}
				else
				{
					d->SetActive(true);
					m_DropdownIsActive = true;
				}
			}
		}
	}
	m_DropdownIsActive = false;
	for each (Dropdown *d in m_Dropdowns)
	{
		if (d->GetActive() == true)
		{
			m_DropdownIsActive = true;
		}
	}

	if (clickedButton != nullptr)
	{
		short buttonID = clickedButton->GetID();

		if (buttonID == 0)
		{
			m_Autoplay = !m_Autoplay;
			if (m_Autoplay)
				clickedButton->SetString("Autoplay ON");
			else
				clickedButton->SetString("Autoplay OFF");
		}
		else if (buttonID == 1)
		{
			cout << "Roulette Selection" << endl;
			m_Population.SetSelectionType(Roulette, 0);
		}
		else if (buttonID == 2)
		{
			cout << "Tournament 2" << endl;
			m_Population.SetSelectionType(Tournament, 2);
		}
		else if (buttonID == 3)
		{
			cout << "Tournament 4" << endl;
			m_Population.SetSelectionType(Tournament, 4);
		}
		else if (buttonID == 4)
		{
			cout << "Tournament 8" << endl;
			m_Population.SetSelectionType(Tournament, 8);
		}
		else if (buttonID == 5)
		{
			cout << "Tournament 16" << endl;
			m_Population.SetSelectionType(Tournament, 16);
		}
		else if (buttonID == 6)
		{
			cout << "Tournament 32" << endl;
			m_Population.SetSelectionType(Tournament, 32);
		}
		else if (buttonID == 7)
		{
			cout << "Tournament 64" << endl;
			m_Population.SetSelectionType(Tournament, 64);
		}
		else if (buttonID == 8)
		{
			cout << "Reset" << endl;
			m_Population.SetMutationType(Reset, 0);
		}
		else if (buttonID == 9)
		{
			cout << "Offset 1" << endl;
			m_Population.SetMutationType(Offset, 1);
		}
		else if (buttonID == 10)
		{
			cout << "Offset 2" << endl;
			m_Population.SetMutationType(Offset, 2);
		}
		else if (buttonID == 11)
		{
			cout << "Offset 3" << endl;
			m_Population.SetMutationType(Offset, 3);
		}
		else if (buttonID == 12)
		{
			cout << "Offset 4" << endl;
			m_Population.SetMutationType(Offset, 4);
		}
	}

	if (testCounter < m_GenomeSize)
	{
		for each (Individual *i in m_Population.GetIndividuals())
		{
			if (i->GetCurrentTile() != m_EndTile)
				i->Step(testCounter);

			if (testCounter == m_GenomeSize - 1)
			{
				float distanceFromEnd = m_Pathfinder->PathCost(m_Pathfinder->StarSearch(i->GetCurrentTile(), m_EndTile));
				i->SetDistance(distanceFromEnd);
				i->CalculateFitness(1, 2, 5);
			}
		}

		testCounter++;
	}

	if (testCounter >= m_GenomeSize && m_Autoplay == true)
	{
		cout << "New Generation" << endl;
		m_GenerationCounter++;
		m_Population.NewGeneration(m_GenerationCounter);
		for each (Individual *i in m_Population.GetIndividuals())
		{
			i->SetCurrentTile(m_StartTile);
		}
		testCounter = 0;
	}
}

void Game::Render()
{
	for each (Button *b in m_Buttons)
	{
		b->Render(m_Window);
	}

	Dropdown *activeDropdown = nullptr;

	for each (Dropdown *d in m_Dropdowns)
	{
		if (d->GetActive()) activeDropdown = d;
		else d->Render(m_Window);
	}
	if (activeDropdown != nullptr) activeDropdown->Render(m_Window);

	for each (vector<Tile*> tileRow in m_TileMap)
	{
		for each (Tile *t in tileRow)
		{
			t->Render(m_Window);
		}
	}

	m_Population.Render(m_Window);
}

void Game::SetupButtons()
{
	if (!m_ButtonFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;

	Button *button = new Button(sf::String("Autoplay OFF"), &m_ButtonFont, 0);
	button->SetPosition(sf::Vector2f(830, 30));
	m_Buttons.push_back(button);

	Dropdown *dropdown = new Dropdown(sf::String("Selection type"), &m_ButtonFont, -1);
	dropdown->SetPosition(sf::Vector2f(830, 80));
	m_Dropdowns.push_back(dropdown);

	button = new Button(sf::String("Roulette"), &m_ButtonFont, 1);
	dropdown->AddButton(button);
	button = new Button(sf::String("Tournament 2"), &m_ButtonFont, 2);
	dropdown->AddButton(button);
	button = new Button(sf::String("Tournament 4"), &m_ButtonFont, 3);
	dropdown->AddButton(button);
	button = new Button(sf::String("Tournament 8"), &m_ButtonFont, 4);
	dropdown->AddButton(button);
	button = new Button(sf::String("Tournament 16"), &m_ButtonFont, 5);
	dropdown->AddButton(button);
	button = new Button(sf::String("Tournament 32"), &m_ButtonFont, 6);
	dropdown->AddButton(button);
	button = new Button(sf::String("Tournament 64"), &m_ButtonFont, 7);
	dropdown->AddButton(button);

	dropdown = new Dropdown(sf::String("Mutation type"), &m_ButtonFont, -1);
	dropdown->SetPosition(sf::Vector2f(1040, 80));
	m_Dropdowns.push_back(dropdown);

	button = new Button(sf::String("Reset"), &m_ButtonFont, 8);
	dropdown->AddButton(button);
	button = new Button(sf::String("Offset 1"), &m_ButtonFont, 9);
	dropdown->AddButton(button);
	button = new Button(sf::String("Offset 2"), &m_ButtonFont, 10);
	dropdown->AddButton(button);
	button = new Button(sf::String("Offset 3"), &m_ButtonFont, 11);
	dropdown->AddButton(button);
	button = new Button(sf::String("Offset 4"), &m_ButtonFont, 12);
	dropdown->AddButton(button);
}

void Game::SetupMap()
{
	for (size_t y = 0; y < 20; y++)
	{
		vector<Tile*> tileRow;
		for (size_t x = 0; x < 20; x++)
		{
			Tile *tile;
			tile = new Tile(m_Map[y][x]);

			tile->SetPosition(sf::Vector2f(x * 40 + 10, y * 40 + 10));

			tileRow.push_back(tile);
		}
		m_TileMap.push_back(tileRow);
	}

	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 20; x++)
		{
			Tile *neighbors[8];
			for (size_t i = 0; i < 8; i++)
			{
				neighbors[i] = nullptr;
			}

			if (y > 0)
			{
				if (x < 19) neighbors[1] = m_TileMap[y - 1][x + 1];

				neighbors[0] = m_TileMap[y - 1][x];

				if (x > 0) neighbors[7] = m_TileMap[y - 1][x - 1];
			}

			if (y < 19)
			{
				if (x < 19) neighbors[3] = m_TileMap[y + 1][x + 1];

				neighbors[4] = m_TileMap[y + 1][x];

				if (x > 0) neighbors[5] = m_TileMap[y + 1][x - 1];
			}

			if (x < 19) neighbors[2] = m_TileMap[y][x + 1];

			if (x > 0) neighbors[6] = m_TileMap[y][x - 1];

			m_TileMap[y][x]->SetNeighbors(neighbors);
		}
	}
}