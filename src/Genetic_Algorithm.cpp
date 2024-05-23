#include "Genetic_Algorithm.h"

void Individual::CalculateFitness(float desiredLandingPos) {
	fitness = 180 - abs(desiredLandingPos - landingPos);
}
void Individual::CalculateLandingPos(float speed, float gravity) {
	float angleRad = angleDeg * PI / 90.0;
	landingPos = speed * speed * sin(angleRad) / gravity;
}


GeneticAlgorithm::GeneticAlgorithm(int populationSize) {
	srand(time(0));
	for (int i = 0; i < populationSize; i++) {
		population.push_back(Individual(rand() % 360));
	}
}
void GeneticAlgorithm::CalculateAllFitness(float desiredLandingPos, float speed, float gravity) {
	for (auto& individual : population) {
		individual.CalculateLandingPos(speed, gravity);
		individual.CalculateFitness(desiredLandingPos);
		stats.avgFitness += individual.fitness;
		stats.avgAngle += individual.angleDeg;
		stats.avgLandingPos += individual.landingPos;
	}
	stats.avgFitness /= population.size();
	stats.avgAngle /= population.size();
	stats.avgLandingPos /= population.size();
}
std::vector<Individual> GeneticAlgorithm::SortPopulation() {
	std::vector<Individual> sortedPopulation = population;
	for (int i = 1; i < population.size(); i++) {
		int crntIndex = i;
		while (crntIndex > 0) {
			if (sortedPopulation[crntIndex].fitness < sortedPopulation[crntIndex - 1].fitness) break;
			Individual temp = sortedPopulation[crntIndex];
			sortedPopulation[crntIndex] = sortedPopulation[crntIndex - 1];
			sortedPopulation[crntIndex - 1] = temp;
			crntIndex--;
		}
	}
	return sortedPopulation;
}
void GeneticAlgorithm::Crossover() {
	std::vector<Individual> newGeneration;
	std::vector<Individual> sortedPopulation = SortPopulation();
	int mutation = (int)(1.0 / mutationRate);
	int numElitists = ceil(0.1 * population.size());
	for (int i = 0; i < numElitists; i++) {
		newGeneration.push_back(sortedPopulation[i]);
	}
	int numElitistsChild = ceil(0.2 * population.size());
	for (int i = 0; i < numElitistsChild; i++) {
		int parent1Index = rand() % numElitists, parent2Index = rand() % numElitists;
		int childDeg = (population[parent1Index].angleDeg & 0b11111) | ((population[parent1Index].angleDeg & (0b11111 << 5)) >> 5);
		Individual child(childDeg);
		int mutation = (int)(1.0 / mutationRate);
		for (int i = 0; i < 8; i++) {
			if (rand() % mutation == 1) {
				child.angleDeg ^= (1 << i);
			}
		}
		newGeneration.push_back(child);
	}

	int halfSize = 0.5 * population.size();
	int remaining = population.size() - newGeneration.size();
	srand(time(0));
	for (int i = 0; i < remaining; i++) {
		int parent1Index = rand() % halfSize, parent2Index = rand() % halfSize;
		int childDeg = (population[parent1Index].angleDeg & 0b11111) | ((population[parent1Index].angleDeg & (0b11111 << 5)) >> 5);
		Individual child(childDeg);
		int mutation = (int)(1.0 / mutationRate);
		for (int i = 0; i < 8; i++) {
			if (rand() % mutation == 1) {
				child.angleDeg ^= (1 << i);
			}
		}
		newGeneration.push_back(child);
	}
	population = newGeneration;
}
void GeneticAlgorithm::Evolve(float desiredLandingPos, float speed, float gravity) {
	CalculateAllFitness(desiredLandingPos, speed, gravity);
	population = SortPopulation();
	stats.bestAngle = population[0].angleDeg;
	stats.bestFitness = population[0].fitness;
	stats.bestLandingPos = population[0].landingPos;
	stats.accuracy = stats.avgFitness / 180;
	Crossover();
}