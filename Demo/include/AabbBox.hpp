#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "collision/Collider.hpp"

class AabbBox final : public Entity
{
public:
	AabbBox(DynamicsWorld& dynWorld, Vector2 size, Vector2 pos, bool takesGravity);
	~AabbBox() override;

	sf::RectangleShape& Shape();
	void SetColor(const sf::Color& color);

	void Update(sf::Time deltaTime) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RectangleShape _shape;
	std::unique_ptr<AabbCollider> _collider;
	
};