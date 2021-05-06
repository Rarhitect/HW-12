#include "system.hpp"

void System::initialize()
{
	const auto size_row = std::size(m_particles);
    const auto size_col = std::size(m_particles[0]);

	for (auto i = 0U; i < size_row; ++i)
	{
        for (auto j = 0U; i < size_col; ++j)
        {
            if (i == 0 and j == 0)
            {
                m_links.push_back(Link(particle(i, j), particle(i, j+1), 0.5f));
                m_links.push_back(Link(particle(i, j), particle(i+1, j), 0.5f));
                m_links.push_back(Link(particle(i, j), particle(i+1, j+1), 0.5f));
            }
            else if (i == 0 and j == size_col)
            {
                m_links.push_back(Link(particle(i, j), particle(i+1, j), 0.5f));
                m_links.push_back(Link(particle(i, j), particle(i+1, j-1), 0.5f));
            }
            else if (i == size_row and j != size_col)
            {
                m_links.push_back(Link(particle(i, j), particle(i, j+1), 0.5f));
            }
            else if (i == size_row and j == size_col)
            {
                //do nothing
            }
            else
            {
                m_links.push_back(Link(particle(i, j), particle(i, j+1), 0.5f));
                m_links.push_back(Link(particle(i, j), particle(i+1, j), 0.5f));
                m_links.push_back(Link(particle(i, j), particle(i+1, j+1), 0.5f));
                m_links.push_back(Link(particle(i, j), particle(i+1, j-1), 0.5f));
            }
        }
	}
}

void System::push(const sf::Vector2f force) const
{
    const auto size_row = std::size(m_particles);
    const auto size_col = std::size(m_particles[0]);
    
	for (auto i = 0U; i < size_row; ++i)
	{
        for (auto j = 0U; j < size_col; ++j)
        {
            m_particles[i][j]->move(force);
        }
	}
}

void System::update() const
{
    const auto size_row = std::size(m_particles);
    const auto size_col = std::size(m_particles[0]);
    
    for (auto i = 0U; i < size_row; ++i)
    {
        for (auto j = 0U; j < size_col; ++j)
        {
            m_particles[i][j]->move(0.25f);

            if (m_particles[i][j]->position().y + m_particles[i][j]->radius() > m_max_point.y)
            {
                m_particles[i][j]->set_y(m_max_point.y - m_particles[i][j]->radius());
            }

            if (m_particles[i][j]->position().y - m_particles[i][j]->radius() < m_min_point.y)
            {
                m_particles[i][j]->set_y(m_min_point.y + m_particles[i][j]->radius());
            }

            if (m_particles[i][j]->position().x + m_particles[i][j]->radius() > m_max_point.x)
            {
                m_particles[i][j]->set_x(m_max_point.x - m_particles[i][j]->radius());
            }

            if (m_particles[i][j]->position().x - m_particles[i][j]->radius() < m_min_point.x)
            {
                m_particles[i][j]->set_x(m_min_point.x + m_particles[i][j]->radius());
            }
        }
	}

	for (auto i = 0U; i < std::size(m_links); ++i)
	{
		m_links[i].update();
	}
}
