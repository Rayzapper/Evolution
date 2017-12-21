#include "Individual.h"

Individual::Individual()
{
	m_Shape.setRadius(5);
	m_Shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
	m_RelativePosition.x = rand() % 30;
	m_RelativePosition.y = rand() % 30;
}

Individual::~Individual()
{

}

void Individual::Update(float dt, sf::Vector2i mousePosition)
{

}

void Individual::Render(sf::RenderWindow *window)
{
	window->draw(m_Shape);
}

void Individual::Step(int i)
{
	int stepDirection = m_Genome[i];
	Tile *newTile = m_CurrentTile->GetNeighbor(stepDirection);

	if (newTile == nullptr)
	{
		m_Collisions++;
	}
	else if (newTile->GetID() == 1)
	{
		m_Collisions++;
	}
	else
	{
		SetCurrentTile(newTile);
		if (stepDirection % 2 == 1)
			m_PathLength += 1.4;
		else
			m_PathLength += 1;
	}
}

void Individual::CalculateFitness(float pathValue, float collisionValue, float distanceValue)
{
	m_Fitness = m_PathLength * pathValue;
	m_Fitness += m_Collisions * collisionValue;
	m_Fitness += m_DistanceFromEnd * distanceValue;
	m_Fitness = 31.2 / m_Fitness;
}

void Individual::ResetValues()
{
	m_Collisions = 0;
	m_PathLength = 0;
	m_Fitness = 0;
}

void Individual::SetPosition(sf::Vector2f position)
{
	m_Position = position + m_RelativePosition;
	m_Shape.setPosition(position + m_RelativePosition);
}

void Individual::SetGenome(vector<int> genome)
{
	m_Genome = genome;
}

void Individual::SetCurrentTile(Tile *tile)
{
	m_CurrentTile = tile;
	SetPosition(tile->GetPosition());
}

void Individual::SetFitness(float fitness)
{
	m_Fitness = fitness;
}

void Individual::SetDistance(float distance)
{
	m_DistanceFromEnd = distance;
}

vector<int> Individual::GetGenome() const
{
	return m_Genome;
}

int Individual::GetCollisions() const
{
	return m_Collisions;
}

float Individual::GetPathLength() const
{
	return m_PathLength;
}

Tile* Individual::GetCurrentTile() const
{
	return m_CurrentTile;
}

float Individual::GetFitness()
{
	return m_Fitness;
}