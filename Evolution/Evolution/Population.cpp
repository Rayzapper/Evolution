#include "Population.h"

#include <iostream>

Population::Population()
{

}

Population::~Population()
{
	for each (Individual *i in m_Individuals)
	{
		delete i;
	}
	m_Individuals.clear();
}

void Population::Render(sf::RenderWindow *window)
{
	for each (Individual *i in m_Individuals)
	{
		i->Render(window);
	}
}

void Population::GenerateRandomPopulation(int popSize, int genomeSize)
{
	for each (Individual *i in m_Individuals)
	{
		delete i;
	}
	m_Individuals.clear();

	for (size_t i = 0; i < popSize; i++)
	{
		Individual *individual = new Individual();

		vector<int> genome;
		for (int j = 0; j < genomeSize; j++)
		{
			genome.push_back(rand() % 8);
		}
		individual->SetGenome(genome);

		m_Individuals.push_back(individual);
	}
}

void Population::NewGeneration(int generationNumber)
{
	int popSize = m_Individuals.size();
	vector<Individual*> temp = m_Individuals;
	m_Individuals.clear();

	if (m_Selection == Roulette)
	{
		float fitnessSum = 0;

		for each (Individual *i in temp)
		{
			fitnessSum += i->GetFitness();
		}
		float fitCounter1 = fitnessSum / (float)rand() / RAND_MAX, fitCounter2 = fitnessSum / (float)rand() / RAND_MAX;

		while (m_Individuals.size() < temp.size())
		{
			Individual *ind1 = nullptr, *ind2 = nullptr;

			for each (Individual *i in temp)
			{
				fitCounter1 -= i->GetFitness();
				if (fitCounter1 <= 0)
				{
					ind1 = i;
					break;
				}
			}
			for each (Individual *i in temp)
			{
				fitCounter2 -= i->GetFitness();
				if (fitCounter2 <= 0)
				{
					ind2 = i;
					break;
				}
			}
			
			Cross(ind1, ind2);
			cout << m_Individuals.size() << endl;
		}
	}
	else
	{
		while (m_Individuals.size() < temp.size())
		{
			Individual *ind1, *ind2;
			ind1 = temp[rand() % popSize];
			ind2 = temp[rand() % popSize];
			for (int i = 1; i < m_TournamentSize; i++)
			{
				Individual *temp1, *temp2;
				temp1 = temp[rand() % popSize];
				temp2 = temp[rand() % popSize];
				if (ind1->GetFitness() < temp1->GetFitness())
					ind1 = temp1;
				if (ind2->GetFitness() < temp2->GetFitness())
					ind2 = temp2;
			}

			Cross(ind1, ind2);
		}
	}

	for each (Individual *i in temp)
	{
		delete i;
	}
	temp.clear();
}

void Population::Cross(Individual *ind1, Individual *ind2)
{
	Individual *child1 = new Individual(), *child2 = new Individual();
	if ((float)rand() / RAND_MAX >= 0.3)
	{
		size_t genomeSize = ind1->GetGenome().size();
		vector<int> genome1, genome2;
		for (size_t i = 0; i < genomeSize; i++)
		{
			if (rand() % 2 == 0)
			{
				genome1.push_back(ind1->GetGenome()[i]);
			}
			else
			{
				genome1.push_back(ind2->GetGenome()[i]);
			}
			if (rand() % 2 == 0)
			{
				genome2.push_back(ind1->GetGenome()[i]);
			}
			else
			{
				genome2.push_back(ind2->GetGenome()[i]);
			}
		}
		for (size_t i = 0; i < genomeSize; i++)
		{
			if ((float)rand() / RAND_MAX < m_MutationRate)
			{
				if (m_Mutation = Reset)
				{
					genome1[i] = rand() % 8;
				}
				else
				{
					int offset = rand() % m_OffsetSize;
					if (rand() % 2 == 0) offset *= -1;
					genome1[i] += offset;
					if (genome1[i] < 0) genome1[i] += 8;
					else if (genome1[i] > 7) genome1[i] -= 8;
				}
			}
			if ((float)rand() / RAND_MAX < m_MutationRate)
			{
				if (m_Mutation = Reset)
				{
					genome2[i] = rand() % 8;
				}
				else
				{
					int offset = rand() % m_OffsetSize;
					if (rand() % 2 == 0) offset *= -1;
					genome2[i] += offset;
					if (genome2[i] < 0) genome2[i] += 8;
					else if (genome2[i] > 7) genome2[i] -= 8;
				}
			}
		}
		child1->SetGenome(genome1);
		child2->SetGenome(genome2);

		m_Individuals.push_back(child1);
		m_Individuals.push_back(child2);
	}
	else
	{
		child1->SetGenome(ind1->GetGenome());
		child2->SetGenome(ind2->GetGenome());
		m_Individuals.push_back(child1);
		m_Individuals.push_back(child2);
	}
}

void Population::SetSelectionType(SelectionType type, int tournamentSize)
{
	m_Selection = type;
	if (type == Tournament)
		m_TournamentSize = tournamentSize;
}

void Population::SetMutationType(MutationType type, int offsetSize)
{
	m_Mutation = type;
	if (type == Offset)
		m_OffsetSize = offsetSize;
}

vector<Individual*> Population::GetIndividuals()
{
	return m_Individuals;
}

void Population::SortByFitness()
{
	vector<Individual*> temp;
	temp.push_back(m_Individuals[0]);

	bool sorted = false;
	size_t popSize = m_Individuals.size();

	for (size_t i = 1; i < popSize; i++)
	{
		Individual *individual = m_Individuals[i];
		for (size_t j = 0; j < i; j++)
		{
			if (individual->GetFitness() < temp[j]->GetFitness())
			{
				temp.insert(temp.begin() + j, individual);
				break;
			}
			if (j == i - 1)
			{
				temp.push_back(individual);
			}
		}
	}

	m_Individuals = temp;

	for (size_t i = 0; i < m_Individuals.size(); i++)
	{
		cout << to_string(m_Individuals[m_Individuals.size() - 1 - i]->GetFitness()) << endl;
	}
}