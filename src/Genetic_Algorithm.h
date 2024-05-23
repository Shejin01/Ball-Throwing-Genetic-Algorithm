#pragma once

#include <vector>
#include <math.h>
#include <random>

#define PI 3.1415926535

class Individual {
public:
	int angleDeg = 0;
	float fitness = 0;
	float landingPos = 0;
	Individual(float angleDeg) : angleDeg(angleDeg) {}
	void CalculateFitness(float desiredLandingPos);
	void CalculateLandingPos(float speed, float gravity);
};

struct Stats {
	float avgFitness = 0;
	float avgAngle = 0;
	float avgLandingPos = 0;
	float bestAngle = 0;
	float bestFitness = 0;
	float bestLandingPos = 0;
	float accuracy = 0;
};

class GeneticAlgorithm {
public:
	std::vector<Individual> population;
	Stats stats;
	float mutationRate = 0.05;

	GeneticAlgorithm(int populationSize);
	void CalculateAllFitness(float desiredLandingPos, float speed, float gravity);
	std::vector<Individual> SortPopulation();
	void Crossover();
	void Evolve(float desiredLandingPos, float speed, float gravity);
};