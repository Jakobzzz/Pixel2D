#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <Kairos\Timestep.hpp>
#include <Kairos\FpsLite.hpp>

#include "Scene.hpp"

namespace px
{
	class Core
	{
	public:
		struct Player
		{
			Entity entity;
			int b = 24;

			void get(const std::string name);
			void set(int number);
			void setpos(float x, float y);
			void g();
		};

	public:
		Core();
		~Core();

	public:
		void initialize();
		void run();
		void render();
		void processEvents();
		void update();
		void updateGUI();

	private:
		sf::RenderWindow m_window;
		sf::RenderTexture m_sceneTexture;
		sf::View m_sceneView;
		sf::Vector2i m_currentMousePos;
		sf::Vector2i m_previousMousePos;
		bool m_isSceneHovered;

	private:
		static std::unique_ptr<Scene> m_scene;

	private:
		kairos::FpsLite m_fps;
		kairos::Timestep m_timestep;
	};
}