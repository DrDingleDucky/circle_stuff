#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

#include <sfml/Graphics.hpp>

class Circle {
  public:
    Circle(float gravity, float mass, float damping, float friction, float bounce, float radius, sf::Color color, sf::Vector2f position);

    void update(sf::RenderWindow &window, float deltaTime, sf::RectangleShape floor);
    void draw(sf::RenderWindow &window);

  private:
    float gravity;
    float mass;
    float damping;
    float friction;
    float bounce;
    sf::Vector2f direction;
    bool mouseTouched;
    sf::CircleShape circle;
    sf::RectangleShape line;

    void mouseCollision(sf::RenderWindow &window);
    void collision(sf::RenderWindow &window);
    void movement(sf::RenderWindow &window, float deltaTime, sf::RectangleShape floor);
};
#endif
