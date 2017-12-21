#ifndef	RAYZAPPER_PATHFINDER_H
#define RAYZAPPER_PATHFINDER_H

#include "Tile.h"
#include <stack>
#include <queue>

using namespace std;

struct Node
{
	Tile *tile;
	Node *parent;
	float startCost, endCost;
};

class Pathfinder
{
public:
	Pathfinder(vector<vector<Tile*>> *tiles);
	~Pathfinder();
	void ClearData();
	Node* StarSearch(Tile *start, Tile *end);
	float PathCost(Node *path);
private:
	vector<vector<Tile*>> *m_TileMap;

	vector<Node*> m_NodeList;
};

#endif