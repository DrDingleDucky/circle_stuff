#include "circle.h"

int main() {
    std::string winTitle = "circle stuff";
    const int winWidth = 1260;
    const int winHeight = 900;

    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), winTitle, sf::Style::Close);

    int winPositionX = sf::VideoMode::getDesktopMode().width / 2 - winWidth / 2;
    int winPositionY = sf::VideoMode::getDesktopMode().height / 2 - winHeight / 2;
    window.setPosition(sf::Vector2i(winPositionX, winPositionY));

    Circle circle(1000.0f, 100.0f, 5.0f, 0.95f, 1.65f, 50.0f, sf::Color(255, 255, 255, 255), sf::Vector2f(605, 425));

    sf::RectangleShape floor;
    floor.setFillColor(sf::Color(255, 255, 255, 255));
    floor.setSize(sf::Vector2f(winWidth, 25.0f));
    floor.setPosition(sf::Vector2f(0.0f, winHeight - 25.0f));

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        deltaTime = clock.restart().asSeconds();
        circle.update(window, deltaTime, floor);

        window.clear(sf::Color(64, 64, 64));
        circle.draw(window);
        window.draw(floor);
        window.display();
    }
    return EXIT_SUCCESS;
}
