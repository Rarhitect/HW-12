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

    const auto N = 500U;
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
        
        sf::Vector2f left_up = sf::Vector2f(0.0f, 0.0f);
        sf::Vector2f left_down = sf::Vector2f(0.0f, 100.0f);
        sf::Vector2f right_up = sf::Vector2f(100.0f, 0.0f);
        sf::Vector2f right_down = sf::Vector2f(100.0f, 100.0f);

        for (auto i = 0; i < 10; ++i)
        {
            for (auto j = 0; j < 10; ++j)
            {
                sf::ConvexShape square;
                square.setPointCount(4);

                square.setPoint(0, left_up);
                square.setPoint(1, right_up);
                square.setPoint(2, right_down);
                square.setPoint(3, left_down);

                int counter = 0;

                for (auto i = 0U; i < N; ++i)
                {
                    auto particle = particles[i];
                    
                    if (particle->position().x > left_up.x and particle->position().x < right_up.x)
                    {
                        if(particle->position().y > left_up.y and particle->position().y < left_down.y)
                        {
                            counter++;
                        }
                    }
                }

                if(counter == 0)
                {
                    square.setFillColor(sf::Color(169, 255, 175));
                }
                if(counter == 1 or counter == 2)
                {
                    square.setFillColor(sf::Color(88, 210, 96));
                }
                if(counter == 3 or counter == 4)
                {
                    square.setFillColor(sf::Color(62, 181, 70));
                }
                if(counter == 5 or counter == 6)
                {
                    square.setFillColor(sf::Color(42, 146, 49));
                }
                if(counter >= 7)
                {
                    square.setFillColor(sf::Color(11, 82, 16));
                }
                
                window.draw(square);

                left_up.x    += 100.0f;
                right_up.x   += 100.0f;
                left_down.x  += 100.0f;
                right_down.x += 100.0f;
            }

            left_up.x    = 0.0f;
            right_up.x   = 100.0f;
            left_down.x  = 0.0f;
            right_down.x = 100.0f;

            left_up.y    += 100.0f;
            right_up.y   += 100.0f;
            left_down.y  += 100.0f;
            right_down.y += 100.0f;
        }
        
//        for (auto i = 0U; i < system.particles().size(); ++i)
//        {
//            sf::CircleShape circle(2.0f * r);
//
//            circle.setPosition(system.particle(i)->position() + sf::Vector2f(r, r));
//
//            circle.setFillColor(sf::Color::White);
//
//            window.draw(circle);
//        }
	
		window.display();
	}
	
	// system("pause");

	return EXIT_SUCCESS;
}
