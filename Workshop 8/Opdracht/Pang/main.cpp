#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "log.hpp"

class Paddle
{
public:
    sf::RectangleShape shape;
    float speed = 500.f;

    Paddle(sf::Vector2f position)
    {
        shape.setSize({ 25.f, 120.f });
        shape.setPosition(position);
    }

    void move(float direction, float dt)
    {
        shape.move({ 0.f, direction * speed * dt });

        if (shape.getPosition().y < 0.f)
            shape.setPosition({ shape.getPosition().x, 0.f });

        if (shape.getPosition().y + shape.getSize().y > 700.f)
            shape.setPosition({
                shape.getPosition().x,
                700.f - shape.getSize().y
                });
    }

    void draw(sf::RenderWindow& window, float time)
    {
        shape.setFillColor(sf::Color(
            static_cast<std::uint8_t>(std::sin(time * 3.f) * 127.f + 128.f),
            static_cast<std::uint8_t>(std::sin(time * 3.f + 2.f) * 127.f + 128.f),
            static_cast<std::uint8_t>(std::sin(time * 3.f + 4.f) * 127.f + 128.f)
        ));

        window.draw(shape);
    }
};

class Ball
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity{ 450.f, 250.f };

    Ball()
    {
        shape.setRadius(15.f);
        shape.setOrigin({ 15.f, 15.f });
        reset();
    }

    void reset()
    {
        shape.setPosition({ 500.f, 350.f });

        velocity.x = velocity.x > 0 ? -450.f : 450.f;
        velocity.y = (std::rand() % 400) - 200.f;
    }

    void update(float dt)
    {
        shape.move(velocity * dt);

        if (shape.getPosition().y < 15.f ||
            shape.getPosition().y > 685.f)
        {
            velocity.y = -velocity.y;
        }
    }

    void draw(sf::RenderWindow& window, float time)
    {
        shape.setFillColor(sf::Color(
            static_cast<std::uint8_t>(std::sin(time * 5.f) * 127.f + 128.f),
            static_cast<std::uint8_t>(std::sin(time * 5.f + 2.f) * 127.f + 128.f),
            static_cast<std::uint8_t>(std::sin(time * 5.f + 4.f) * 127.f + 128.f)
        ));

        window.draw(shape);
    }
};

class Game
{
public:
    int scoreLeft = 0;
    int scoreRight = 0;

    void checkCollision(Ball& ball, Paddle& left, Paddle& right)
    {
        if (ball.shape.getGlobalBounds()
            .findIntersection(left.shape.getGlobalBounds()))
        {
            ball.velocity.x = std::abs(ball.velocity.x);
        }

        if (ball.shape.getGlobalBounds()
            .findIntersection(right.shape.getGlobalBounds()))
        {
            ball.velocity.x = -std::abs(ball.velocity.x);
        }

        if (ball.shape.getPosition().x < 0.f)
        {
            ++scoreRight;
            ball.reset();
        }

        if (ball.shape.getPosition().x > 1000.f)
        {
            ++scoreLeft;
            ball.reset();
        }
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::cout << "Pang(" << __FILE__ << ")\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl;
    LogTargetArchitecture();
    LogRunTimeArchitecture();
    LogTargetOperatingSystem();
    LogTargetCompiler();
    LogTargetCxxStandard();
    std::cout << "SFML version: "
        << SFML_VERSION_MAJOR << "."
        << SFML_VERSION_MINOR << "."
        << SFML_VERSION_PATCH << '\n';

    sf::RenderWindow window(
        sf::VideoMode({ 1000, 700 }),
        "Pang"
    );

    window.setFramerateLimit(60);

    Paddle left({ 40.f, 290.f });
    Paddle right({ 935.f, 290.f });
    Ball ball;
    Game game;

    sf::Clock clock;
    float time = 0.f;

    // Avans Logo
    const auto logoPath =
        std::filesystem::current_path() / "Avans_Logo-RGB.png";
    sf::Texture logoTexture;
    bool logoLoaded = logoTexture.loadFromFile(logoPath.string());
    if (!logoLoaded)
    {
        std::cerr << "Asset kon niet worden geladen: "
            << logoPath << '\n';
    }

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();
        time += dt;

        // Speler links: W / S
        float leftDirection = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            leftDirection = -1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            leftDirection = 1.f;

        // Speler rechts: pijltjes
        float rightDirection = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            rightDirection = -1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            rightDirection = 1.f;

        left.move(leftDirection, dt);
        right.move(rightDirection, dt);

        ball.update(dt);
        game.checkCollision(ball, left, right);

        // Achtergrond
        window.clear(sf::Color(20, 5, 30));

        // Rainbow middenlijn
        for (int i = 0; i < 14; ++i)
        {
            sf::RectangleShape line({ 4.f, 30.f });
            line.setPosition({ 498.f, i * 50.f });

            line.setFillColor(sf::Color(
                static_cast<std::uint8_t>(std::sin(time * 3.f + i) * 127.f + 128.f),
                static_cast<std::uint8_t>(std::sin(time * 3.f + i + 2.f) * 127.f + 128.f),
                static_cast<std::uint8_t>(std::sin(time * 3.f + i + 4.f) * 127.f + 128.f)
            ));

            window.draw(line);
        }

        left.draw(window, time);
        right.draw(window, time);
        ball.draw(window, time);

        if (logoLoaded)
        {
            sf::Sprite logo(logoTexture);
            logo.setPosition({ 20.f, 20.f });
            window.draw(logo);
        }

        window.display();
    }

    return 0;
}