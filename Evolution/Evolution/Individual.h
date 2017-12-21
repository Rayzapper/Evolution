#ifndef RAYZAPPER_INDIVIDUAL_H
#define RAYZAPPER_INDIVIDUAL_H

#include "Entity.h"
#include "Tile.h"
using namespace std;

class Individual : public Entity
{
public:
	Individual();
	~Individual();
	virtual void Update(float dt, sf::Vector2i mousePosition);
	virtual void Render(sf::RenderWindow *window);
	void Step(int i);
	void CalculateFitness(float pathValue, float collisionValue, float distanceValue);
	void ResetValues();
	virtual void SetPosition(sf::Vector2f position);
	void SetGenome(vector<int> genome);
	void SetCurrentTile(Tile *tile);
	void SetFitness(float fitness);
	void SetDistance(float distance);
	vector<int> GetGenome() const;
	int GetCollisions() const;
	float GetPathLength() const;
	Tile* GetCurrentTile() const;
	float GetFitness();
private:
	vector<int> m_Genome;
	int m_Collisions = 0;
	float m_PathLength = 0, m_Fitness = 0, m_DistanceFromEnd = 0;
	Tile *m_CurrentTile;
	sf::CircleShape m_Shape;
	sf::Vector2f m_RelativePosition;
};

#endif