#include "dynamics/DynamicsWorld.hpp"

#include "collision/CollisionBody.hpp"

#include "spdlog/spdlog.h"

void DynamicsWorld::AddRigidbody(Rigidbody* rigidbody)
{
	if (rigidbody->TakesGravity())
	{
		rigidbody->SetGravityForce(_gravity);
	}

	AddCollisionBody(rigidbody);
}

void DynamicsWorld::ApplyGravity() const
{
	for (CollisionBody* body : _bodies)
	{
		if (!body->IsDynamic()) continue;

		// ReSharper disable once CppCStyleCast
		const auto rigidbody = (Rigidbody*)body;
		rigidbody->ApplyForce(rigidbody->GravityForce() * rigidbody->Mass());
	}
}

void DynamicsWorld::MoveBodies(const float deltaTime) const
{
	std::size_t count = 0;
	for (CollisionBody* body : _bodies)
	{
		if (!body->IsDynamic()) continue;

		// ReSharper disable once CppCStyleCast
		const auto rigidbody = (Rigidbody*)body;

		const Vector2 vel = rigidbody->Velocity() + rigidbody->Force() * rigidbody->InvMass() * deltaTime;
		if (count++ % 2 == 1)
			//spdlog::debug(vel);
		rigidbody->SetVelocity(vel);

		//rigidbody->UpdateLastTransform();

		Vector2 pos = rigidbody->Position() + rigidbody->Velocity() * deltaTime;
		rigidbody->SetPosition(pos);

		rigidbody->SetForce({ 0, 0 });
	}
}

void DynamicsWorld::Step(const float deltaTime) const
{
	ApplyGravity();
	ResolveCollisions(deltaTime);
	MoveBodies(deltaTime);
}

void DynamicsWorld::SetWorldGravity(const Vector2 gravity)
{
	_gravity = gravity;
}
