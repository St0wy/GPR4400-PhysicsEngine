#include "DemoBalls.hpp"

#include <spdlog/spdlog.h>

#include "Consts.hpp"
#include "MathUtils.hpp"
#include "Circle.hpp"

DemoBalls::DemoBalls()
	: _window(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_NAME,
		sf::Style::Close,
		sf::ContextSettings(0, 0, 8)
	)
{
	//_window.setVerticalSyncEnabled(true);
	//_window.setFramerateLimit(FRAMERATE);

	_window.setView(DEFAULT_VIEW);

	_impulseSolver = std::make_unique<ImpulseSolver>();
	_smoothPositionSolver = std::make_unique<SmoothPositionSolver>();
	_world.AddSolver(_impulseSolver.get());
	_world.AddSolver(_smoothPositionSolver.get());
	_world.SetWorldGravity({ 0,0 });
}

void DemoBalls::StartMainLoop()
{
	_entities.push_back(
		std::make_unique<Circle>(_world, 1.0f, Vector2(-3.0f, 3.0f)));
	const Entity* staticBall = _entities[_entities.size() - 1].get();
	staticBall->RigidBody()->SetIsKinematic(false);
	_entities.push_back(
		std::make_unique<Circle>(_world, 1.0f, Vector2(0.0f, 3.0f)));
	_entities.push_back(
		std::make_unique<Circle>(_world, 1.0f, Vector2(3.0f, 3.0f)));

	const Entity* maball = _entities[_entities.size() - 1].get();


	spdlog::debug("Starting main loop");

	sf::Clock clock;
	while (_window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		sf::Event event{};

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				auto posi = sf::Mouse::getPosition(_window);
				auto posf = _window.mapPixelToCoords(posi);
				constexpr float radius = 1.0f;
				posf.x -= radius;
				posf.y -= radius;
				_entities.push_back(
					std::make_unique<Circle>(_world, radius, SfmlPosToSpe(posf)));
			}
		}

		// Step the physics
		_world.Step(deltaTime.asSeconds());

		// Update the entites
		for (const auto& entity : _entities)
		{
			entity->Update(deltaTime);
		}

		maball->Push(Vector2(-2.0f, 0.f));

		// Clear the window
		_window.clear(sf::Color::Black);

		// Render all the entities
		for (const auto& entity : _entities)
		{
			_window.draw(*entity);
		}

		_window.display();
	}
}
