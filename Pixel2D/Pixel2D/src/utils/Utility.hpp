#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace px
{
	namespace utils
	{
		sf::Vector2f linearInterpolation(sf::Vector2f start, sf::Vector2f end, float alpha)
		{
			return (start * (1 - alpha) + end * alpha);
		}

		sf::Keyboard::Key toKey(const std::string key)
		{
			//Is there a cleaner way to do this with defines?
			if (key == "W" || key == "w")
				return sf::Keyboard::Key::W;
			if (key == "A" || key == "a")
				return sf::Keyboard::Key::A;
			if (key == "S" || key == "s")
				return sf::Keyboard::Key::S;
			if (key == "D" || key == "d")
				return sf::Keyboard::Key::D;
			if (key == "SPACE" || key == "space")
				return sf::Keyboard::Key::Space;
			if (key == "ENTER" || key == "enter")
				return sf::Keyboard::Key::Return;

			return sf::Keyboard::Key::Unknown;
		}
	}
}
