#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

#include <iostream>

namespace ver
{
    template <typename T>
    struct Vector2D{
        T x;
        T y;

        Vector2D(T x, T y) : x(x), y(y) {} 

        Vector2D operator + (const Vector2D& rhs)
        {
            return Vector2D(x + rhs.x,y + rhs.y);
        }
    };

    class Particle{
        public:

        Particle();
        Particle(const Vector2D<float>& pos, const Vector2D<float>& vel, float m_mass);

        Particle(const Particle& obj) = default;

        ~Particle() = default;

        void update(Vector2D<float>& force, float dt);

        void draw(sf::RenderWindow& window);

        Particle& operator= (const Particle& rhs) = default;

        friend std::ostream& operator <<(std::ostream& os, const Particle& obj);

        private:

        Vector2D<float> position;
        Vector2D<float> velocity;
        float mass;

    };

} // end namespace ver

#endif 