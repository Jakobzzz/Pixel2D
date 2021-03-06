#pragma once
#include <SFML/System/Vector2.hpp>

namespace sf
{
	class Transform;
}

class b2Body;
class b2World;

//Perhaps inheritance from this class could be a good idea in the future?
//Depends how bloated this class will be...
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
		void setLocalPosition(const sf::Vector2f & position);
		void setRadius(const float & radius);
		void setStaticStatus(const bool & status);

	public:
		Collider getColliderType() const;
		b2Body* getBody() const;
		sf::Vector2f getLocalPosition() const;
		sf::Vector2f getWorldPosition() const;
		sf::Vector2f getSize() const;
		float getRotation() const;
		float getRadius() const;
		bool getStaticStatus();

	private:
		void createBody();

	private:
		bool m_isStatic;
		float m_radius;
		sf::Vector2f m_size;
		sf::Vector2f m_localPosition;
		b2Body* m_body;
		b2World* m_world;
		Collider m_colliderType;
	};
}