#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class ActorObject* owner)
	:Component(owner)
	, mRadius(0.0f)
{

}

const Vector3& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// Calculate distance squared
	Vector3 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// Calculate sum of radii squared
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}