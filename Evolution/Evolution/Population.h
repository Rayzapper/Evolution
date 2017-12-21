#ifndef RAYZAPPER_POPULATION_H
#define RAYZAPPER_POPULATION_H

#include "Individual.h"

enum SelectionType
{
	Roulette,
	Tournament
};

enum MutationType
{
	Reset,
	Offset
};

class Population
{
public:
	Population();
	~Population();
	void Render(sf::RenderWindow *window);
	void GenerateRandomPopulation(int popSize, int genomeSize);
	void NewGeneration(int generationNumber);
	void Cross(Individual *ind1, Individual *ind2);
	void SetSelectionType(SelectionType type, int tournamentSize);
	void SetMutationType(MutationType type, int offsetSize);
	vector<Individual*> GetIndividuals();
private:
	void SortByFitness();
	vector<Individual*> m_Individuals;
	SelectionType m_Selection = Roulette;
	MutationType m_Mutation = Reset;
	int m_TournamentSize = 2, m_OffsetSize = 1;
	float m_MutationRate = 0.01;
};

#endif