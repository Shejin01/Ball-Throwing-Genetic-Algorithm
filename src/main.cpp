#include <iostream>
#include <SFML/Graphics.hpp>
#include "Genetic_Algorithm.h"

const int WIDTH = 500, HEIGHT = 500;
const int FPS = 60;

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ball Throwing Genetic Algorithm", 7U, settings);
	window.setFramerateLimit(FPS);

	GeneticAlgorithm generation(900);
	int numGeneration = 0;
	int desiredLandingPos = 40;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}

			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Space:
					generation.Evolve(desiredLandingPos, 30, 10);
					numGeneration++;
					std::cout << "[*] Generation: " << numGeneration
						<< "  Accuracy: " << generation.stats.accuracy
						<< "  Average_Angle: " << generation.stats.avgAngle
						<< "  Average_Fitness: " << generation.stats.avgFitness
						<< "  Average_LandingPos: " << generation.stats.avgLandingPos
						/* << "  Best_Angle: " << generation.stats.bestAngle
						<< "  Best_Fitness: " << generation.stats.bestFitness*/
						<< "  Best_LandingPos: " << generation.stats.bestLandingPos
						<< '\n';
					break;
				case sf::Keyboard::Left:
					desiredLandingPos -= 1;
					std::cout << "[*] Desired Landing Pos: " << desiredLandingPos << '\n';
					break;
				case sf::Keyboard::Right:
					desiredLandingPos += 1;
					std::cout << "[*] Desired Landing Pos: " << desiredLandingPos << '\n';
					break;
				}
			}
		}

		window.clear();
		window.display();
	}

	return 0;
}