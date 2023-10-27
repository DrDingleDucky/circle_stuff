#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

#include <sfml/Graphics.hpp>

class Circle {
public:
  Circle(float gravity, float mass, float damping, float friction, float bounce,
         float radius, sf::Color color, sf::Vector2f position);

  void Update(sf::RenderWindow &window, float deltaTime,
              sf::RectangleShape floor);
  void Draw(sf::RenderWindow &window);

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

  void MouseCollision(sf::RenderWindow &window);
  void Collision(sf::RenderWindow &window);
  void Movement(sf::RenderWindow &window, float deltaTime,
                sf::RectangleShape floor);
};
#endif