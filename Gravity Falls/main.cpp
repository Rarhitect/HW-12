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

	const auto N_row = 10U;
    
    const auto N_column = 20U;

    const auto init_distance = length(max_point - min_point) * 0.4f / N_row;

	const auto r = 2.5f;
    
    auto position = (max_point - min_point) * 0.5f - sf::Vector2f(N_row * init_distance / 2, N_column * init_distance / 2);

	std::vector < std::vector < System::particle_t > > particles;

	for (auto i = 0U; i < N_row; ++i, position.y += init_distance)
	{
        std::vector < System::particle_t > particles_row;
        
        auto current_position = position;
        
        for (auto j = 0U; i < N_column; ++j)
        {
            particles_row.push_back(std::make_shared < Particle > (current_position, current_position, sf::Vector2f(0.0f, 10.0f), r));
            
            current_position.x += init_distance;
        }
        
        particles.push_back(particles_row);
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
            for (auto j = 0U; j < system.particles()[0].size(); ++j)
            {
                sf::CircleShape circle(2.0f * r);

                circle.setPosition(system.particle(i, j)->position() + sf::Vector2f(r, r));

                circle.setFillColor(sf::Color::Blue);

                window.draw(circle);
            }
		}
	
		window.display();
	}
	
	// system("pause");

	return EXIT_SUCCESS;
}
