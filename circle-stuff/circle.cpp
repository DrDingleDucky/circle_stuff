#include "circle.h"

constexpr auto PI = 3.14159265358979323846;

Circle::Circle(float gravity, float mass, float damping, float friction, float bounce, float radius,
               sf::Color color, sf::Vector2f position)
    : gravity(gravity), mass(mass), damping(damping), friction(friction), bounce(bounce),
      mouseTouched(false), direction(sf::Vector2f(0.0f, 0.0f)) {
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setPosition(position);
};

void Circle::update(sf::RenderWindow &window, float deltaTime, sf::RectangleShape floor) {
    mouseCollision(window);
    collision(window);
    movement(window, deltaTime, floor);
}

void Circle::draw(sf::RenderWindow &window) {
    window.draw(circle);
    window.draw(line);
}

void Circle::mouseCollision(sf::RenderWindow &window) {
    float circleX = circle.getPosition().x + circle.getRadius();
    float circleY = circle.getPosition().y + circle.getRadius();

    float distance = sqrt(pow(sf::Mouse().getPosition(window).x - circleX, 2) + pow(sf::Mouse().getPosition(window).y - circleY, 2));

    if (distance <= circle.getRadius()) {
        mouseTouched = true;
    }
}

void Circle::collision(sf::RenderWindow &window) {
    if (circle.getPosition().x > window.getSize().x) {
        circle.setPosition(sf::Vector2f(0.0f - circle.getRadius() * 2, circle.getPosition().y));
    } else if (circle.getPosition().x + circle.getRadius() * 2 < 0.0f) {
        circle.setPosition(sf::Vector2f(window.getSize().x, circle.getPosition().y));
    }
}

void Circle::movement(sf::RenderWindow &window, float deltaTime, sf::RectangleShape floor) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (mouseTouched) {
            float x = sf::Mouse::getPosition(window).x - (circle.getPosition().x + circle.getRadius());
            float y = sf::Mouse::getPosition(window).y - (circle.getPosition().y + circle.getRadius());

            direction.x += x / mass - direction.x * damping * deltaTime;
            direction.y += y / mass - direction.y * damping * deltaTime;

            float circleX = circle.getPosition().x + circle.getRadius();
            float circleY = circle.getPosition().y + circle.getRadius();

            float distance = sqrt(pow(sf::Mouse().getPosition(window).x - circleX, 2) + pow(sf::Mouse().getPosition(window).y - circleY, 2));

            line.setSize(sf::Vector2f(-distance, 4));
            line.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - 2.0f, sf::Mouse::getPosition(window).y - 2.0f));
            line.setRotation(atan2(y, x) * 180 / PI);
            line.setFillColor(sf::Color(255, 255, 255, 255));
        }
    } else {
        mouseTouched = false;
        line.setFillColor(sf::Color(0, 0, 0, 0));
    }

    if (circle.getGlobalBounds().intersects(floor.getGlobalBounds())) {
        if (direction.y > 0.0f) {
            direction.y = -1 * direction.y / bounce;
        }

        if (direction.x > 0.1f) {
            direction.x -= direction.x / friction * deltaTime;
        } else if (direction.x < -0.1f) {
            direction.x -= direction.x / friction * deltaTime;
        } else {
            direction.x = 0.0f;
        }
    } else {
        direction.y += gravity * deltaTime;
    }
    circle.move(sf::Vector2f(direction.x * deltaTime, direction.y * deltaTime));
}
