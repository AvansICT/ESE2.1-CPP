#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "log.hpp"

struct Star
{
    sf::CircleShape shape;
    float speed;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::cout << "Hello SFML (" << __FILE__ << ")\n";
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
        "SFML - Rainbow Universe"
    );

    window.setFramerateLimit(60);

    // ---------------------------------------------------------
    // Planet
    // ---------------------------------------------------------

    sf::CircleShape planet(120.f);
    planet.setOrigin({ 120.f, 120.f });
    planet.setPosition({ 500.f, 350.f });

    // ---------------------------------------------------------
    // Stars
    // ---------------------------------------------------------

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<Star> stars;

    for (int i = 0; i < 100; ++i)
    {
        Star star;

        float size =
            1.f + static_cast<float>(std::rand() % 4);

        star.shape = sf::CircleShape(size);

        star.shape.setPosition({
            static_cast<float>(std::rand() % 1000),
            static_cast<float>(std::rand() % 700)
            });

        star.speed =
            20.f + static_cast<float>(std::rand() % 80);

        stars.push_back(star);
    }

    // ---------------------------------------------------------
    // Clock
    // ---------------------------------------------------------

    sf::Clock clock;
    float time = 0.f;

    // ---------------------------------------------------------
    // Main loop
    // ---------------------------------------------------------

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();
        time += dt;

        // -----------------------------------------------------
        // Animate stars
        // -----------------------------------------------------

        for (auto& star : stars)
        {
            auto position = star.shape.getPosition();

            position.y += star.speed * dt;

            if (position.y > 700.f)
                position.y = 0.f;

            star.shape.setPosition(position);

            // Rainbow stars
            star.shape.setFillColor(sf::Color(
                static_cast<std::uint8_t>(
                    std::sin(time * 2.f + position.x) * 127.f + 128.f),
                static_cast<std::uint8_t>(
                    std::sin(time * 2.f + position.x + 2.f) * 127.f + 128.f),
                static_cast<std::uint8_t>(
                    std::sin(time * 2.f + position.x + 4.f) * 127.f + 128.f)
            ));
        }

        // -----------------------------------------------------
        // Animate planet
        // -----------------------------------------------------

        float y =
            350.f + std::sin(time * 2.f) * 50.f;

        planet.setPosition({ 500.f, y });

        // Rainbow planet
        planet.setFillColor(sf::Color(
            static_cast<std::uint8_t>(
                std::sin(time * 2.f) * 127.f + 128.f),
            static_cast<std::uint8_t>(
                std::sin(time * 2.f + 2.f) * 127.f + 128.f),
            static_cast<std::uint8_t>(
                std::sin(time * 2.f + 4.f) * 127.f + 128.f)
        ));

        // Rotate
        planet.rotate(sf::degrees(60.f * dt));

        // Fake 3D effect
        float scale =
            1.f + std::sin(time * 2.f) * 0.15f;

        planet.setScale({ scale, scale });

        // -----------------------------------------------------
        // Draw
        // -----------------------------------------------------

        window.clear(sf::Color(15, 3, 25));

        // Rainbow stars
        for (const auto& star : stars)
            window.draw(star.shape);

        // Planet
        window.draw(planet);

        // -----------------------------------------------------
        // Pride rainbow
        // -----------------------------------------------------

        const sf::Color pride[] = {
            sf::Color(255, 0, 0),
            sf::Color(255, 165, 0),
            sf::Color(255, 255, 0),
            sf::Color(0, 200, 80),
            sf::Color(0, 150, 255),
            sf::Color(140, 50, 255)
        };

        for (int i = 0; i < 6; ++i)
        {
            sf::RectangleShape stripe({
                1000.f,
                10.f
                });

            stripe.setPosition({
                0.f,
                640.f + i * 10.f
                });

            stripe.setFillColor(pride[i]);

            window.draw(stripe);
        }

        window.display();
    }

    return 0;
}