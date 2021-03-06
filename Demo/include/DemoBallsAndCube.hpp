#pragma once

#include <SFML/Graphics.hpp>

#include "dynamics/DynamicsWorld.hpp"
#include "dynamics/ImpulseSolver.hpp"
#include "dynamics/SmoothPositionSolver.hpp"
#include "Entity.hpp"
#include "FpsCounter.hpp"

class DemoBallsAndCube
{
public:
	DemoBallsAndCube();
	void StartMainLoop();

private:
	sf::RenderWindow _window;
	DynamicsWorld _world;
	std::vector<std::unique_ptr<Entity>> _entities;
	std::unique_ptr<ImpulseSolver> _impulseSolver;
	std::unique_ptr<SmoothPositionSolver> _smoothPositionSolver;
	FpsCounter _fpsCounter;
	sf::Font _lModern;
	sf::Text _fpsText;
};
