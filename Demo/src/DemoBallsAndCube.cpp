#include "DemoBallsAndCube.hpp"

#include <spdlog/spdlog.h>

#include "Consts.hpp"
#include "Circle.hpp"
#include "AabbBox.hpp"
#include "MathUtils.hpp"
#include "FpsCounter.hpp"

DemoBallsAndCube::DemoBallsAndCube()
	: _window(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_NAME,
		sf::Style::Close,
		sf::ContextSettings(0, 0, 8)
	)
{
	_window.setView(DEFAULT_VIEW);

	_impulseSolver = std::make_unique<ImpulseSolver>();
	_smoothPositionSolver = std::make_unique<SmoothPositionSolver>();
	_world.AddSolver(_impulseSolver.get());
	_world.AddSolver(_smoothPositionSolver.get());

	if (!_lModern.loadFromFile("data/lmodern.otf"))
	{
		spdlog::error("Could not load font");
	}

	_fpsText.setFont(_lModern);
	_fpsText.setCharacterSize(256);
	_fpsText.setFillColor(sf::Color::White);
	_fpsText.setPosition(-CAM_WIDTH/2.0f, -CAM_HEIGHT/2.0f);
	_fpsText.setScale(0.01f, 0.01f);
}

void DemoBallsAndCube::StartMainLoop()
{
	auto ground = std::make_unique<AabbBox>(
		_world,
		Vector2(CAM_WIDTH * 0.8f, 1.0f),
		Vector2(0.0f, -5.0f),
		false
		);
	ground->RigidBody()->SetIsKinematic(false);
	ground->RigidBody()->SetTakesGravity(false);
	_entities.push_back(std::move(ground));

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
				auto physicsPos = SfmlPosToSpe(posf);
				spdlog::debug("Spawn pos : {}", physicsPos);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					_entities.push_back(
						std::make_unique<Circle>(_world, 1.0f, physicsPos));
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					_entities.push_back(std::make_unique<AabbBox>(_world, Vector2(1.0f, 1.0f), physicsPos, true));
				}
			}
		}

		// Step the physics
		_world.Step(deltaTime.asSeconds());

		// Update the entites
		for (const auto& entity : _entities)
		{
			entity->Update(deltaTime);
		}

		_fpsCounter.Update(deltaTime.asSeconds());
		_fpsText.setString(_fpsCounter.GetFpsString());

		// Clear the window
		_window.clear(sf::Color::Black);

		// Render all the entities
		for (const auto& entity : _entities)
		{
			_window.draw(*entity);
		}

		_window.draw(_fpsText);

		_window.display();
	}
}