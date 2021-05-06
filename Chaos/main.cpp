#include <cmath>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(1000U, 1000U), "CHAOS MOVEMENT");

	sf::Vector2f min_point(  0.0f,   0.0f);
	sf::Vector2f max_point(975.0f, 975.0f);

    const auto N = 100U;
	const auto r = 2.5f;
    
	std::vector < System::particle_t > particles;
    
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution < float > uni_x(1.0f, 974.0f);
    std::uniform_real_distribution < float > uni_y(1.0f, 974.0f);
    std::uniform_real_distribution < float > accel_x(-7.0f, 7.0f);
    std::uniform_real_distribution < float > accel_y(-7.0f, 7.0f);

	for (auto i = 0U; i < N; ++i)
	{
        sf::Vector2f position;
        position.x = uni_x(mersenne);
        position.y = uni_y(mersenne);
        float accelx = accel_x(mersenne);
        float accely = accel_y(mersenne);
        particles.push_back(std::make_shared < Particle > (position, position, sf::Vector2f(accelx, accely), r));
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
