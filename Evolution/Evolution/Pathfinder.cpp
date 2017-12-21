#include "Pathfinder.h"

Pathfinder::Pathfinder(vector<vector<Tile*>> *tiles)
	: m_TileMap(tiles)
{

}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::ClearData()
{
	for each (Node *n in m_NodeList)
	{
		delete n;
	}
	m_NodeList.clear();
}

float GetEndCost(Tile *start, Tile *end)
{
	float xDifference, yDifference, distance;

	xDifference = abs(start->GetPosition().x - end->GetPosition().x);
	yDifference = abs(start->GetPosition().y - end->GetPosition().y);
	xDifference /= 40;
	yDifference /= 40;

	if (xDifference >= yDifference)
	{
		distance = yDifference * 1.4;
		xDifference -= yDifference;
		distance += xDifference;
	}
	else
	{
		distance = xDifference * 1.4;
		yDifference -= xDifference;
		distance += yDifference;
	}

	return distance;
}

Node* Pathfinder::StarSearch(Tile *start, Tile *end)
{
	ClearData();

	vector<Node*> open, closed;

	Node *startNode;
	startNode = new Node;
	startNode->tile = start;
	startNode->parent = nullptr;
	startNode->startCost = 0;
	startNode->endCost = GetEndCost(start, end);

	open.push_back(startNode);
	m_NodeList.push_back(startNode);

	bool loop = true;

	Node *current = startNode;
	while (loop)
	{
		current = open[0];
		closed.push_back(current);
		open.erase(open.begin());

		// Examination
		if (current->tile == end)
		{
			loop = false;
			break;
		}

		// Expansion
		for (int i = 0; i < 8; i++)
		{
			Node *newNode;
			newNode = new Node;
			bool diagonal = false;
			if (i % 2 == 1) diagonal = true;

			newNode->tile = current->tile->GetNeighbor(i);

			newNode->parent = current;

			newNode->startCost = current->startCost;

			bool add = true;

			if (newNode->tile == nullptr) add = false;
			else if (newNode->tile->GetID() == 1) add = false;
			else
			{
				for each (Node *n in m_NodeList)
				{
					if (newNode->tile == n->tile)
					{
						add = false;
						break;
					}
				}
			}

			if (add)
			{
				newNode->endCost = GetEndCost(newNode->tile, end);

				if (diagonal) newNode->startCost += 1.4;
				else newNode->startCost++;
				bool added = false;
				size_t j = 0;
				while (!added && j < open.size())
				{
					if (open[j]->startCost + open[j]->endCost > newNode->startCost + newNode->endCost)
					{
						open.insert(open.begin() + j, newNode);
						added = true;
					}
					j++;
				}
				if (!added) open.push_back(newNode);
				m_NodeList.push_back(newNode);
			}
			else delete newNode;
		}
	}

	return current;
}

float Pathfinder::PathCost(Node *path)
{
	float distance = 0;

	return distance;
}