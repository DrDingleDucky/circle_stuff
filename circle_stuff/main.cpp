#include <iostream>
#include <sfml/Graphics.hpp>

constexpr auto PI = 3.14159265358979323846;

class Circle
{
public:
	Circle(float gravity, float mass, float damping, float friction, float bounce, float radius, sf::Color color, sf::Vector2f position)
	{
		this->gravity = gravity;
		this->mass = mass;
		this->damping = damping;
		this->friction = friction;
		this->bounce = bounce;
		circle.setRadius(radius);
		circle.setFillColor(color);
		circle.setPosition(position);
	};

	void update(sf::RenderWindow& window, float deltaTime, sf::RectangleShape floor)
	{
		mouseCollision(window);
		collision(window);
		movement(window, deltaTime, floor);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(circle);
		window.draw(line);
	}

private:
	float gravity;
	float mass;
	float damping;
	float friction;
	float bounce;
	sf::Vector2f direction = sf::Vector2f(0.0f, 0.0f);
	bool mouseTouched = true;
	sf::CircleShape circle;
	sf::RectangleShape line;

	void mouseCollision(sf::RenderWindow& window)
	{
		float circleX = circle.getPosition().x + circle.getRadius();
		float circleY = circle.getPosition().y + circle.getRadius();

		float distance = sqrt(pow(sf::Mouse().getPosition(window).x - circleX, 2) + pow(sf::Mouse().getPosition(window).y - circleY, 2));

		if (distance <= circle.getRadius())
		{
			mouseTouched = true;
		}
	}

	void collision(sf::RenderWindow& window)
	{
		if (circle.getPosition().x > window.getSize().x)
		{
			circle.setPosition(sf::Vector2f(0.0f - circle.getRadius() * 2, circle.getPosition().y));
		}
		else if (circle.getPosition().x + circle.getRadius() * 2 < 0.0f)
		{
			circle.setPosition(sf::Vector2f(window.getSize().x, circle.getPosition().y));
		}
	}

	void movement(sf::RenderWindow& window, float deltaTime, sf::RectangleShape floor)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (mouseTouched)
			{
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
		}
		else
		{
			mouseTouched = false;
			line.setFillColor(sf::Color(0, 0, 0, 0));
		}

		if (circle.getGlobalBounds().intersects(floor.getGlobalBounds()))
		{
			if (direction.y > 0.0f)
			{
				direction.y = -1 * direction.y / bounce;
			}

			if (direction.x > 0.1f)
			{
				direction.x -= direction.x / friction * deltaTime;
			}
			else if (direction.x < -0.1f)
			{
				direction.x -= direction.x / friction * deltaTime;
			}
			else
			{
				direction.x = 0.0f;
			}
		}
		else
		{
			direction.y += gravity * deltaTime;
		}

		circle.move(sf::Vector2f(direction.x * deltaTime, direction.y * deltaTime));
	}
};

int main()
{
	std::string winTitle = "circle stuff";
	int winWidth = 1260;
	int winHeight = 900;

	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), winTitle, sf::Style::Close);

	int winPositionX = sf::VideoMode::getDesktopMode().width / 2 - winWidth / 2;
	int winPositionY = sf::VideoMode::getDesktopMode().height / 2 - winHeight / 2;
	window.setPosition(sf::Vector2i(winPositionX, winPositionY));

	Circle circle(
		1000.0f,                       // gravity
		100.0f,                        // mass
		5.0f,                          // damping
		0.95f,                         // friction
		1.65f,                         // bounce
		50.0f,                         // radius
		sf::Color(255, 255, 255, 255), // colour
		sf::Vector2f(605, 425));       // position

	sf::RectangleShape floor;
	floor.setFillColor(sf::Color(255, 255, 255, 255));
	floor.setSize(sf::Vector2f(winWidth, 25.0f));
	floor.setPosition(sf::Vector2f(0.0f, winHeight - 25.0f));

	sf::Clock clock;
	float deltaTime;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
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
