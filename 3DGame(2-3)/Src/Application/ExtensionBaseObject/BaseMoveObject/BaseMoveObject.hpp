#pragma once

class BaseMoveObject // Not Inherited KdGameObject
{
public:
	BaseMoveObject() noexcept = default;
	virtual ~BaseMoveObject() noexcept = default;

protected:
	inline auto SetMemberPos(const Math::Vector3& pos) noexcept { m_pos = pos; }

	const auto MoveLinear(const Math::Vector3& currentPosition, const Math::Vector3& speed, const float deltaTime) noexcept { return currentPosition + speed * deltaTime; }

	const auto MoveWithAcceleration(const Math::Vector3& currentPosition, Math::Vector3& speed, const Math::Vector3& maxAcceleration, const float deltaTime) noexcept
	{
		speed += maxAcceleration * deltaTime;
		return currentPosition + speed * deltaTime;
	}

	const auto MoveWithAccelerationAndInertia(const Math::Vector3& currentPosition, Math::Vector3& speed, const Math::Vector3& maxAcceleration, const float inertia, const float deltaTime) noexcept 
	{
		speed += maxAcceleration * deltaTime;
		speed *= inertia;
		return currentPosition + speed * deltaTime;
	}

	const auto MoveJump(const Math::Vector3& currentPosition, Math::Vector3& velocity, const float gravity, const float deltaTime) noexcept
	{
		velocity.y += gravity * deltaTime;
		return currentPosition + velocity * deltaTime;
	}

	Math::Vector3 m_pos;
};