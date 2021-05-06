#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(800U, 600U), "PHYSICS");

	sf::Vector2f min_point(  0.0f,   0.0f);
	sf::Vector2f max_point(775.0f, 575.0f);

	const auto N_row = 3U;
    
    const auto N_column = 5U;

    const auto init_distance = length(max_point - min_point) * 0.3f / N_row;

	const auto r = 2.5f;
    
    auto initial_position = (max_point - min_point) * 0.5f - sf::Vector2f(N_row * init_distance / 2, N_column * init_distance / 2);

    auto position = initial_position;
    
	std::vector < System::particle_t > particles;

	for (auto i = 0U; i < N_row * N_column; ++i)
	{
        particles.push_back(std::make_shared < Particle > (position, position, sf::Vector2f(0.0f, 10.0f), r));
        
        if (i != 0 and (i+1) % N_column == 0)
        {
            position.y -= init_distance;
            position.x = initial_position.x;
            particles.push_back(std::make_shared < Particle > (position, position, sf::Vector2f(0.0f, 10.0f), r));
        }
        
        position.x += init_distance;
	}

	System system(min_point, max_point, particles);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		system.update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			system.push(sf::Vector2f(0.0f, -2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			system.push(sf::Vector2f(0.0f, 2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			system.push(sf::Vector2f(-2.0f, 0.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			system.push(sf::Vector2f(2.0f, 0.0f));
		}

		window.clear();
		
        for (auto i = 0U; i < system.particles().size(); ++i)
        {
            sf::CircleShape circle(2.0f * r);

            circle.setPosition(system.particle(i)->position() + sf::Vector2f(r, r));

            circle.setFillColor(sf::Color(65, 247, 95));

            window.draw(circle);
        }
	
		window.display();
	}
	
	// system("pause");

	return EXIT_SUCCESS;
}
