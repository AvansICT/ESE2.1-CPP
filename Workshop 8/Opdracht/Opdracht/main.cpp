#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "log.hpp"

#define VIDEO_MODE_WIDTH 1000
#define VIDEO_MODE_HEIGHT 700
#define FRAME_RATE_LIMIT 60

struct Star
{
    int id;
    sf::CircleShape shape;
    float speed;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::cout << "Hello SFML (" << __FILE__ << ")\n";
    std::cout << __DATE__ << " " << __TIME__ << '\n';

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
        sf::VideoMode({ VIDEO_MODE_WIDTH, VIDEO_MODE_HEIGHT }),
        "SFML - Rainbow Universe"
    );

    window.setFramerateLimit(FRAME_RATE_LIMIT);

    // ---------------------------------------------------------
    // Planet
    // ---------------------------------------------------------

    sf::CircleShape planet(120.f);
    planet.setOrigin({ 120.f, 120.f });
    planet.setPosition({ 500.f, 350.f });

    // ---------------------------------------------------------
    // STL containers
    // ---------------------------------------------------------

    std::vector<Star> stars;
    std::deque<Star> newStars;
    std::list<Star> bonusStars;

    std::set<int> starSizes;
    std::map<int, sf::Color> sizeColors;

    std::multiset<float> starSpeeds;
    std::multimap<float, int> starsBySpeed;

    std::unordered_set<int> starIds;
    std::unordered_map<int, float> speedById;

    // ---------------------------------------------------------
    // Create stars
    // ---------------------------------------------------------

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < 100; ++i)
    {
        Star star;

        star.id = i;

        float size =
            1.f + static_cast<float>(std::rand() % 4);

        star.shape = sf::CircleShape(size);

        star.shape.setPosition({
            static_cast<float>(std::rand() % VIDEO_MODE_WIDTH),
            static_cast<float>(std::rand() % VIDEO_MODE_HEIGHT)
        });

        star.speed =
            20.f + static_cast<float>(std::rand() % 80);

        // vector
        stars.push_back(star);

        // deque
        if (i < 5)
            newStars.push_back(star);

        // list
        if (i < 5)
            bonusStars.push_back(star);

        // set
        starSizes.insert(static_cast<int>(size));

        // map
        sizeColors[static_cast<int>(size)] = sf::Color::White;

        // multiset
        starSpeeds.insert(star.speed);

        // multimap
        starsBySpeed.insert({ star.speed, star.id });

        // unordered_set
        starIds.insert(star.id);

        // unordered_map
        speedById[star.id] = star.speed;
    }

    // =========================================================
    // STL ALGORITHMS
    // =========================================================

    std::cout << "\n--- STL algorithms ---\n";

    // ---------------------------------------------------------
    // Iterators: begin() / end()
    // ---------------------------------------------------------

    std::cout << "Star IDs: ";

    for (auto it = starIds.begin(); it != starIds.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << '\n';

    // ---------------------------------------------------------
    // sort(begin, end)
    // ---------------------------------------------------------
    // Sorteer een aparte vector met snelheden.

    std::vector<float> sortedSpeeds;

    for (const auto& star : stars)
    {
        sortedSpeeds.push_back(star.speed);
    }

    std::sort(
        sortedSpeeds.begin(),
        sortedSpeeds.end()
    );

    std::cout << "Laagste snelheid: "
        << sortedSpeeds.front() << '\n';

    // ---------------------------------------------------------
    // find(begin, end, value)
    // ---------------------------------------------------------

    auto foundId = std::find(
        starIds.begin(),
        starIds.end(),
        42
    );

    if (foundId != starIds.end())
    {
        std::cout << "Ster 42 gevonden\n";
    }

    // ---------------------------------------------------------
    // count(begin, end, value)
    // ---------------------------------------------------------
    // Hoe vaak komt een snelheid voor?

    float speedToFind = stars.front().speed;

    auto speedCount = std::count(
        starSpeeds.begin(),
        starSpeeds.end(),
        speedToFind
    );

    std::cout << "Snelheid "
        << speedToFind
        << " komt "
        << speedCount
        << " keer voor\n";

    // ---------------------------------------------------------
    // copy(begin, end, dest)
    // ---------------------------------------------------------

    std::vector<Star> copiedStars;

    std::copy(
        stars.begin(),
        stars.end(),
        std::back_inserter(copiedStars)
    );

    std::cout << "Gekopieerde sterren: "
        << copiedStars.size()
        << '\n';

    // ---------------------------------------------------------
    // std::back_inserter
    // ---------------------------------------------------------
    // Voeg elementen achteraan een container toe.

    std::vector<int> starNumbers;

    std::copy(
        starIds.begin(),
        starIds.end(),
        std::back_inserter(starNumbers)
    );

    // ---------------------------------------------------------
    // for_each(begin, end, func)
    // ---------------------------------------------------------

    std::for_each(
        stars.begin(),
        stars.end(),
        [](Star& star)
        {
            star.shape.setOutlineThickness(0.f);
        }
    );

    // ---------------------------------------------------------
    // copy_if(begin, end, dest, predicate)
    // ---------------------------------------------------------
    // Alleen snelle sterren kopiëren.

    std::vector<Star> fastStars;

    std::copy_if(
        stars.begin(),
        stars.end(),
        std::back_inserter(fastStars),
        [](const Star& star)
        {
            return star.speed > 70.f;
        }
    );

    std::cout << "Snelle sterren (>70): "
        << fastStars.size()
        << '\n';

    // ---------------------------------------------------------
    // Container informatie
    // ---------------------------------------------------------

    std::cout << "\n--- STL containers ---\n";

    std::cout << "vector        : "
        << stars.size() << '\n';

    std::cout << "deque         : "
        << newStars.size() << '\n';

    std::cout << "list          : "
        << bonusStars.size() << '\n';

    std::cout << "set           : "
        << starSizes.size() << " unieke groottes\n";

    std::cout << "map           : "
        << sizeColors.size() << '\n';

    std::cout << "multiset      : "
        << starSpeeds.size() << '\n';

    std::cout << "multimap      : "
        << starsBySpeed.size() << '\n';

    std::cout << "unordered_set : "
        << starIds.size() << '\n';

    std::cout << "unordered_map : "
        << speedById.size() << '\n';

    // =========================================================
    // Clock
    // =========================================================

    sf::Clock clock;
    float time = 0.f;

    // =========================================================
    // Main loop
    // =========================================================

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

            if (position.y > VIDEO_MODE_HEIGHT)
                position.y = 0.f;

            star.shape.setPosition(position);

            // Rainbow stars
            star.shape.setFillColor(sf::Color(
                static_cast<std::uint8_t>(
                    std::sin(time * 2.f + position.x)
                    * 127.f + 128.f),

                static_cast<std::uint8_t>(
                    std::sin(time * 2.f + position.x + 2.f)
                    * 127.f + 128.f),

                static_cast<std::uint8_t>(
                    std::sin(time * 2.f + position.x + 4.f)
                    * 127.f + 128.f)
            ));
        }

        // -----------------------------------------------------
        // Animate planet
        // -----------------------------------------------------

        float y =
            350.f + std::sin(time * 2.f) * 50.f;

        planet.setPosition({ 500.f, y });

        planet.setFillColor(sf::Color(
            static_cast<std::uint8_t>(
                std::sin(time * 2.f)
                * 127.f + 128.f),

            static_cast<std::uint8_t>(
                std::sin(time * 2.f + 2.f)
                * 127.f + 128.f),

            static_cast<std::uint8_t>(
                std::sin(time * 2.f + 4.f)
                * 127.f + 128.f)
        ));

        planet.rotate(sf::degrees(60.f * dt));

        float scale =
            1.f + std::sin(time * 2.f) * 0.15f;

        planet.setScale({ scale, scale });

        // =====================================================
        // Draw
        // =====================================================

        window.clear(sf::Color(15, 3, 25));

        for (const auto& star : stars)
            window.draw(star.shape);

        window.draw(planet);

        // -----------------------------------------------------
        // Pride rainbow
        // -----------------------------------------------------
        // From https://gilbertbaker.com/rainbow-flag-color-meanings/ 
        constexpr int PRIDE_NR_COLORS = 8;
        constexpr int PRIDE_COLOR_HEIGHT = 10;

        const sf::Color pride[PRIDE_NR_COLORS] = {
            sf::Color(223, 25 , 149),   // Hot Pink      Sex
            sf::Color(228, 0  , 43),    // Red          / Life
            sf::Color(254, 80 , 0),     // Orange       / Healing
            sf::Color(255, 255, 0),     // Yellow       / Sunlight
            sf::Color(0  , 132, 61),    // Green        / Nature
            sf::Color(0  , 154, 166),   // Turquoise    / Magic & Art
            sf::Color(0  , 61 , 165),   // Indigo       / Serenity
            sf::Color(166, 52 , 178)    // Violet       / Spirit
        };

        for (int i = 0; i < PRIDE_NR_COLORS; ++i)
        {
            sf::RectangleShape stripe({
                VIDEO_MODE_WIDTH,
                PRIDE_COLOR_HEIGHT
            });

            stripe.setPosition({
                0.f,
                static_cast<float>(
                    VIDEO_MODE_HEIGHT -
                    (PRIDE_NR_COLORS * PRIDE_COLOR_HEIGHT))
                    + i * PRIDE_COLOR_HEIGHT
            });

            stripe.setFillColor(pride[i]);

            window.draw(stripe);
        }

        window.display();
    }

    return 0;
}