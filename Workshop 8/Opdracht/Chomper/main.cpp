#include <iostream>
#include <print>    // C++23
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "log.hpp"

class Player
{
public:
    sf::CircleShape shape;
    float speed = 300.f;

    Player()
    {
        shape.setRadius(20.f);
        shape.setOrigin({ 20.f, 20.f });
        shape.setPosition({ 100.f, 350.f });
    }

    void update(float dt)
    {
        sf::Vector2f direction{ 0.f, 0.f };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            direction.x = -1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            direction.x = 1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            direction.y = -1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            direction.y = 1.f;

        shape.move(direction * speed * dt);

        auto p = shape.getPosition();

        if (p.x < 20.f)  p.x = 20.f;
        if (p.x > 980.f) p.x = 980.f;
        if (p.y < 20.f)  p.y = 20.f;
        if (p.y > 680.f) p.y = 680.f;

        shape.setPosition(p);
    }

    void draw(sf::RenderWindow& window, float time)
    {
        shape.setFillColor(sf::Color(255, 230, 0));

        // Geanimeerde "mond"
        float mouth = 0.15f + std::abs(std::sin(time * 8.f)) * 0.35f;

        sf::ConvexShape pacman;
        pacman.setPointCount(3);

        pacman.setPoint(0, { 20.f, 20.f });
        pacman.setPoint(1, {
            -20.f * std::cos(mouth),
             20.f * std::sin(mouth)
            });
        pacman.setPoint(2, {
            -20.f * std::cos(mouth),
            -20.f * std::sin(mouth)
            });

        pacman.setPosition(shape.getPosition());
        pacman.setFillColor(sf::Color(20, 5, 30));

        window.draw(shape);
        window.draw(pacman);
    }
};

class Pellet
{
public:
    sf::CircleShape shape;
    bool eaten = false;

    Pellet(float x, float y)
    {
        shape.setRadius(6.f);
        shape.setOrigin({ 6.f, 6.f });
        shape.setPosition({ x, y });
    }

    void draw(sf::RenderWindow& window, float time)
    {
        if (!eaten)
        {
            float pulse = 1.f + std::sin(time * 6.f) * 0.2f;

            // Rainbow kleur
            float phase =
                time * 3.f +
                shape.getPosition().x * 0.02f +
                shape.getPosition().y * 0.01f;

            sf::Color color(
                static_cast<std::uint8_t>(
                    std::sin(phase) * 127.f + 128.f),
                static_cast<std::uint8_t>(
                    std::sin(phase + 2.f) * 127.f + 128.f),
                static_cast<std::uint8_t>(
                    std::sin(phase + 4.f) * 127.f + 128.f)
            );

            // Glow
            sf::CircleShape glow(12.f);
            glow.setOrigin({ 12.f, 12.f });
            glow.setPosition(shape.getPosition());
            glow.setScale({ pulse, pulse });
            glow.setFillColor(sf::Color(
                color.r,
                color.g,
                color.b,
                70
            ));

            // Kern
            shape.setScale({ pulse, pulse });
            shape.setFillColor(color);

            window.draw(glow);
            window.draw(shape);
        }
    }
};

class Ghost
{
public:
    sf::CircleShape shape;
    sf::Color color;
    float speed;

    Ghost(sf::Vector2f position, sf::Color color, float speed)
        : color(color), speed(speed)
    {
        shape.setRadius(20.f);
        shape.setOrigin({ 20.f, 20.f });
        shape.setPosition(position);
    }

    void update(float dt, sf::Vector2f target)
    {
        auto p = shape.getPosition();

        sf::Vector2f direction = target - p;

        float length = std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );

        if (length > 0.f)
            direction /= length;

        shape.move(direction * speed * dt);

        p = shape.getPosition();

        if (p.x < 20.f)  p.x = 20.f;
        if (p.x > 980.f) p.x = 980.f;
        if (p.y < 20.f)  p.y = 20.f;
        if (p.y > 680.f) p.y = 680.f;

        shape.setPosition(p);
    }

    void draw(sf::RenderWindow& window)
    {
        shape.setFillColor(color);
        window.draw(shape);

        // Ogen
        sf::CircleShape eye(5.f);
        eye.setFillColor(sf::Color::White);

        eye.setPosition(
            shape.getPosition() + sf::Vector2f(-10.f, -5.f)
        );
        window.draw(eye);

        eye.setPosition(
            shape.getPosition() + sf::Vector2f(5.f, -5.f)
        );
        window.draw(eye);
    }
};

class Game
{
public:
    int score = 0;

    void checkPellets(
        Player& player,
        std::vector<Pellet>& pellets)
    {
        for (auto& pellet : pellets)
        {
            if (!pellet.eaten &&
                player.shape.getGlobalBounds()
                .findIntersection(
                    pellet.shape.getGlobalBounds()))
            {
                pellet.eaten = true;
                score += 10;
            }
        }
    }

    bool checkGhosts(
        Player& player,
        std::vector<Ghost>& ghosts)
    {
        for (auto& ghost : ghosts)
        {
            if (player.shape.getGlobalBounds()
                .findIntersection(
                    ghost.shape.getGlobalBounds()))
            {
                return true;
            }
        }

        return false;
    }
};

int main(
    [[maybe_unused]] int argc,
    [[maybe_unused]] char* argv[])
{
    std::print("Chomper ({})\n", __FILE__);
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
        "Chomper"
    );

    window.setFramerateLimit(60);

    Player player;

    std::vector<Pellet> pellets;

    for (int x = 100; x < 950; x += 70)
    {
        for (int y = 70; y < 650; y += 70)
        {
            pellets.emplace_back(
                static_cast<float>(x),
                static_cast<float>(y)
            );
        }
    }

    std::vector<Ghost> ghosts;

    ghosts.emplace_back(
        sf::Vector2f(800.f, 150.f),
        sf::Color(255, 80, 120),
        100.f
    );

    ghosts.emplace_back(
        sf::Vector2f(800.f, 550.f),
        sf::Color(80, 180, 255),
        120.f
    );

    ghosts.emplace_back(
        sf::Vector2f(600.f, 350.f),
        sf::Color(180, 80, 255),
        140.f
    );

    Game game;

    sf::Clock clock;
    float time = 0.f;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();
        time += dt;

        player.update(dt);

        for (auto& ghost : ghosts)
            ghost.update(dt, player.shape.getPosition());

        game.checkPellets(player, pellets);

        if (game.checkGhosts(player, ghosts))
        {
            player.shape.setPosition({ 100.f, 350.f });
        }

        window.clear(sf::Color(20, 5, 30));

        // Rainbow glow pellets
        for (auto& pellet : pellets)
            pellet.draw(window, time);

        for (auto& ghost : ghosts)
            ghost.draw(window);

        player.draw(window, time);

        window.display();
    }

    return 0;
}
