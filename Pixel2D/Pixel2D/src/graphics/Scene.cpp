#include "Scene.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../utils/Utility.hpp"

//Systems
#include "systems/RenderSystem.hpp"
#include "systems/TransformSystem.hpp"


namespace px
{
	Scene::Scene(sf::RenderTarget & target) : m_entities(m_events), m_systems(m_entities, m_events)
	{
		//Basic entity
		auto entity = m_entities.create();

		Transform transform(sf::Vector2f(500.f, 233.f), sf::Vector2f(1.f, 1.f), 0.f);

		//Circle
		auto shape = std::make_unique<sf::CircleShape>(10.f);

		shape->setFillColor(sf::Color::Yellow);
		utils::centerOrigin(*shape);
		shape->setPosition(transform.position);

		//Apply components
		entity.assign<Render>(std::move(shape), "Circle", "Default");
		entity.assign<Transform>(transform);

		//Layers
		m_layers = { "Default", "Grass" };

		//Systems
		m_systems.add<RenderSystem>(target, m_layers);
		m_systems.add<TransformSystem>();
		m_systems.configure();
	}

	Scene::~Scene()
	{
		destroyEntities();
	}

	void Scene::createEntity(const Scene::Shapes & shape, const sf::Vector2f & position, const std::string & name, ObjectInfo & info)
	{
		//Create default shaped entities
		if (shape == Shapes::CIRCLE)
		{
			auto entity = m_entities.create();
			auto shape = std::make_unique<sf::CircleShape>(5.f);

			Transform transform(position, sf::Vector2f(1.f, 1.f), 0.f);
			shape->setFillColor(sf::Color::Red);
			utils::centerOrigin(*shape);
			shape->setPosition(transform.position);
			shape->setScale(transform.scale);
			shape->setRotation(transform.rotation);

			//Update the GUI display
			info = { name, transform.position, transform.scale, transform.rotation, utils::circleCounter, true, "Default" };
			info.changeName(name);

			//Apply components
			entity.assign<Render>(std::move(shape), name, "Default");
			entity.assign<Transform>(transform);
		}
		else if (shape == Shapes::RECTANGLE)
		{
			auto entity = m_entities.create();
			auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(16.f, 16.f));

			Transform transform(position, sf::Vector2f(1.f, 1.f), 0.f);
			shape->setFillColor(sf::Color::Red);
			utils::centerOrigin(*shape);
			shape->setPosition(transform.position);
			shape->setScale(transform.scale);
			shape->setRotation(transform.rotation);

			//Update the GUI display
			info = { name, transform.position, transform.scale, transform.rotation, utils::rectangleCounter, true, "Default" };
			info.changeName(name);

			//Apply components
			entity.assign<Render>(std::move(shape), name, "Default");
			entity.assign<Transform>(transform);
		}
	}

	void Scene::destroyEntity(const std::string & name)
	{
		ComponentHandle<Render> render;

		//Remove entity which corresponds to the name
		for (Entity & entity : m_entities.entities_with_components(render))
		{
			if (render->name == name)
			{
				m_entities.destroy(entity.id());
				return;
			}
		}
	}

	void Scene::destroyEntities(const std::string & layer)
	{
		ComponentHandle<Render> render;

		for (Entity & entity : m_entities.entities_with_components(render))
			if(render->layer == layer)
				entity.destroy();
	}

	void Scene::destroyEntities()
	{
		ComponentHandle<Render> render;

		for (Entity & entity : m_entities.entities_with_components(render))
			entity.destroy();
	}

	void Scene::updateLayer(std::string & cName, const std::string & layer)
	{
		ComponentHandle<Render> render;

		for (Entity & entity : m_entities.entities_with_components(render))
		{
			if (render->name == cName)
			{
				render->layer = layer;
				return;
			}
		}
	}

	void Scene::updateName(std::string & cName, const std::string & nName)
	{
		ComponentHandle<Render> render;
		
		//Make sure that the new name is not already taken
		for (Entity & entity : m_entities.entities_with_components(render))
			if (render->name == nName)
				return;

		//Assign new name
		for (Entity & entity : m_entities.entities_with_components(render))
		{
			if (render->name == cName)
			{
				render->name = nName;
				cName = nName;
				return;
			}
		}
	}

	void Scene::updateTransform(const ObjectInfo & info)
	{
		ComponentHandle<Render> render;
		ComponentHandle<Transform> transform;

		for (Entity & entity : m_entities.entities_with_components(render, transform))
		{
			if (render->name == info.pickedName && info.picked)
			{
				transform->position = info.position;
				transform->scale = info.scale;
				transform->rotation = info.rotation;
			}
		}
	}

	void Scene::updateTransformSystem(const double & dt)
	{
		m_systems.update<TransformSystem>(dt);
	}

	void Scene::updateRenderSystem(const double & dt)
	{
		m_systems.update<RenderSystem>(dt);
	}

	bool Scene::checkIntersection(const sf::Vector2f & point, ObjectInfo & info)
	{
		ComponentHandle<Render> render;
		ComponentHandle<Transform> transform;

		unsigned int i = 0;
		for (Entity & entity : m_entities.entities_with_components(render, transform))
		{
			if (render->shape->getGlobalBounds().contains(point))
			{
				//Update the GUI display
				info = { render->name, transform->position, transform->scale, transform->rotation, i, true, render->layer };
				info.changeName(render->name);
				return true;
			}
			++i;
		}
		return false;
	}

	std::vector<std::string> & Scene::getLayers()
	{
		return m_layers;
	}

	Entity Scene::getEntity(const std::string & name)
	{
		ComponentHandle<Render> render;
		Entity found;

		for (Entity & entity : m_entities.entities_with_components(render))
			if (render->name == name)
				found = entity;

		return found;
	}

	EntityManager & Scene::getEntities()
	{
		return m_entities;
	}
}