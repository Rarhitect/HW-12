#include "system.hpp"

void System::initialize(std::size_t size_row, std::size_t size_col)
{
    const auto size = std::size(m_particles);
    const auto stiffness = 0.3f;


    for (auto i = 0U; i < size_row; i++)
    {
        for (auto j = 0U; j < size_col; j++)
        {
            if (i > 0)
            {
                m_links.push_back(Link(particle(i*size_col + j ), particle((i-1)*size_col + j), stiffness));
                if (j > 0)
                {
                    m_links.push_back(Link(particle(i * size_col + j), particle((i - 1) * size_col + j - 1), stiffness));
                }
                if (j + 1 < size_col)
                {
                    m_links.push_back(Link(particle(i * size_col + j), particle((i - 1) * size_col + j + 1), stiffness));
                }
            }
            if (j > 0)
            {
                m_links.push_back(Link(particle(i * size_col + j), particle(i * size_col + j -1), stiffness));

            }
        }
    }
}

void System::push(const sf::Vector2f force) const
{
    for (auto i = 0U; i < std::size(m_particles); ++i)
    {
        m_particles[i]->move(force);
    }
}

void System::update() const
{
    for (auto i = 0U; i < std::size(m_particles); ++i)
    {
        m_particles[i]->move(0.20f);

        if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y)
        {
            m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
        }

        if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y)
        {
            m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
        }

        if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x)
        {
            m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
        }

        if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x)
        {
            m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
        }
    }

    for (auto i = 0U; i < std::size(m_links); ++i)
    {
        m_links[i].update();
    }
}
