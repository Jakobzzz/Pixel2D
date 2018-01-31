#pragma once
#include <SFML/System/Vector2.hpp>

namespace sf
{
	class Transform;
}

class b2Body;
class b2World;

namespace px
{
	class RigidbodyShape
	{
	public:
		enum class Collider
		{
			Circle,
			Box
		};

	public:
		RigidbodyShape(Collider colliderType, b2World* world);

	public:
		void setTransform(const sf::Vector2f & position, const float & angle, const sf::Vector2f & scale = sf::Vector2f());
		void setTransform(const sf::Vector2f & position, const float & radius, const float & angle);
		void destroyBody();

	public:
		Collider getColliderType() const;
		b2Body* getBody() const;
		sf::Transform getTransform() const;
		sf::Vector2f & getLocalPositionRef();
		sf::Vector2f getLocalPosition() const;
		sf::Vector2f getWorldPosition() const;
		float getRotation() const;

	private:
		void createBody();

	private:
		sf::Vector2f m_localPosition;
		b2Body* m_body;
		b2World* m_world;
		Collider m_colliderType;
	};
}