#include "particle.hpp"

namespace ver
{


    Particle::Particle(const Vector2D<float>& pos, const Vector2D<float>& vel,  float mass) : 
        position(pos), velocity(vel),  mass(mass) {}



    void Particle::update(Vector2D<float>& force, float dt)
    {
        Vector2D<float> acceleration(force.x/mass, force.y/mass);
        
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        velocity.x += acceleration.x * dt;
        velocity.y += acceleration.y * dt;
    }

    void Particle::draw(sf::RenderWindow& window)
    {
        sf::CircleShape circle(20.0f);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(sf::Vector2f{position.x, position.y});
        window.draw(circle);
    }


    std::ostream& operator <<(std::ostream& os, const Particle& obj)
    {
        os  << "x: " << obj.position.x << ", y: " << obj.position.y
            << ", vx: " << obj.velocity.x  << ", vy: " << obj.velocity.y 
            << ", mass: " << obj.mass << "\n";

        return os;
    }

} // end namespace ver