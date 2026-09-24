#define ALLEGRO_STATICLINK
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <filesystem>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "log.hpp"

#define VIDEO_MODE_WIDTH 1000
#define VIDEO_MODE_HEIGHT 700
#define FRAME_RATE_LIMIT 60

struct Star
{
    int id;
    float x;
    float y;
    float size;
    float speed;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::cout << "Hello Allegro (" << __FILE__ << ")\n";
    std::cout << __DATE__ << " " << __TIME__ << '\n';

    LogTargetArchitecture();
    LogRunTimeArchitecture();
    LogTargetOperatingSystem();
    LogTargetCompiler();
    LogTargetCxxStandard();

    std::cout << "Allegro version: "
        << ALLEGRO_VERSION << "."
        << ALLEGRO_SUB_VERSION << "."
        << ALLEGRO_WIP_VERSION << '\n';

    // =========================================================
    // Allegro initialiseren
    // =========================================================

    if (!al_init())
    {
        std::cerr << "Allegro initialisatie mislukt\n";
        return 1;
    }

    if (!al_init_image_addon())
    {
        std::cerr << "Allegro image addon initialisatie mislukt\n";
        return 1;
    }

    if (!al_init_primitives_addon())
    {
        std::cerr << "Allegro primitives addon initialisatie mislukt\n";
        return 1;
    }

    ALLEGRO_DISPLAY* display =
        al_create_display(VIDEO_MODE_WIDTH, VIDEO_MODE_HEIGHT);

    if (!display)
    {
        std::cerr << "Display aanmaken mislukt\n";
        return 1;
    }

    al_set_window_title(display, "Allegro - Hello Universe");

    ALLEGRO_EVENT_QUEUE* eventQueue =
        al_create_event_queue();

    ALLEGRO_TIMER* timer =
        al_create_timer(1.0 / FRAME_RATE_LIMIT);

    if (!eventQueue || !timer)
    {
        std::cerr << "Allegro resources aanmaken mislukt\n";

        if (timer)
            al_destroy_timer(timer);

        if (eventQueue)
            al_destroy_event_queue(eventQueue);

        al_destroy_display(display);
        return 1;
    }

    al_register_event_source(
        eventQueue,
        al_get_display_event_source(display)
    );

    al_register_event_source(
        eventQueue,
        al_get_timer_event_source(timer)
    );

    // =========================================================
    // Planet
    // =========================================================

    float planetX = 500.f;
    float planetY = 350.f;
    float planetRadius = 120.f;

    // =========================================================
    // STL containers
    // =========================================================

    std::vector<Star> stars;
    std::deque<Star> newStars;
    std::list<Star> bonusStars;

    std::set<int> starSizes;
    std::map<int, ALLEGRO_COLOR> sizeColors;

    std::multiset<float> starSpeeds;
    std::multimap<float, int> starsBySpeed;

    std::unordered_set<int> starIds;
    std::unordered_map<int, float> speedById;

    // =========================================================
    // Create stars
    // =========================================================

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < 100; ++i)
    {
        Star star;

        star.id = i;

        star.size =
            1.f + static_cast<float>(std::rand() % 4);

        star.x =
            static_cast<float>(
                std::rand() % VIDEO_MODE_WIDTH);

        star.y =
            static_cast<float>(
                std::rand() % VIDEO_MODE_HEIGHT);

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
        starSizes.insert(static_cast<int>(star.size));

        // map
        sizeColors[static_cast<int>(star.size)] =
            al_map_rgb(255, 255, 255);

        // multiset
        starSpeeds.insert(star.speed);

        // multimap
        starsBySpeed.insert({
            star.speed,
            star.id
            });

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
            // Geen outline nodig bij Allegro.
            star.size = star.size;
        }
    );

    // ---------------------------------------------------------
    // copy_if(begin, end, dest, predicate)
    // ---------------------------------------------------------

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

    // =========================================================
    // Container informatie
    // =========================================================

    std::cout << "\n--- STL containers ---\n";

    std::cout << "vector        : "
        << stars.size() << '\n';

    std::cout << "deque         : "
        << newStars.size() << '\n';

    std::cout << "list          : "
        << bonusStars.size() << '\n';

    std::cout << "set           : "
        << starSizes.size()
        << " unieke groottes\n";

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
    // Timer
    // =========================================================

    double time = 0.0;

    bool running = true;
    bool redraw = true;

    // Avans Logo
    const auto logoPath =
    std::filesystem::current_path() / "Avans_Logo-RGB.png";

    ALLEGRO_BITMAP* logo = al_load_bitmap(logoPath.string().c_str());
    if (!logo)
    {
        std::cerr << "Asset kon niet worden geladen: "
            << logoPath << '\n';
    }

    al_start_timer(timer);

    // =========================================================
    // Main loop
    // =========================================================

    while (running)
    {
        ALLEGRO_EVENT event;

        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            constexpr float dt =
                1.0f / FRAME_RATE_LIMIT;

            time += dt;

            // -------------------------------------------------
            // Animate stars
            // -------------------------------------------------

            for (auto& star : stars)
            {
                star.y += star.speed * dt;

                if (star.y > VIDEO_MODE_HEIGHT)
                    star.y = 0.f;
            }

            // -------------------------------------------------
            // Animate planet
            // -------------------------------------------------

            planetY =
                350.f +
                std::sin(
                    static_cast<float>(time) * 2.f
                ) * 50.f;

            planetRadius =
                120.f +
                std::sin(
                    static_cast<float>(time) * 2.f
                ) * 18.f;

            redraw = true;
        }

        // =====================================================
        // Draw
        // =====================================================

        if (redraw &&
            al_is_event_queue_empty(eventQueue))
        {
            redraw = false;

            al_clear_to_color(
                al_map_rgb(15, 3, 25)
            );

            // -------------------------------------------------
            // Stars
            // -------------------------------------------------

            for (const auto& star : stars)
            {
                const float phase =
                    static_cast<float>(time) * 2.f
                    + star.x;

                const auto red =
                    static_cast<unsigned char>(
                        std::sin(phase)
                        * 127.f + 128.f);

                const auto green =
                    static_cast<unsigned char>(
                        std::sin(phase + 2.f)
                        * 127.f + 128.f);

                const auto blue =
                    static_cast<unsigned char>(
                        std::sin(phase + 4.f)
                        * 127.f + 128.f);

                al_draw_filled_circle(
                    star.x,
                    star.y,
                    star.size,
                    al_map_rgb(
                        red,
                        green,
                        blue
                    )
                );
            }

            // -------------------------------------------------
            // Planet
            // -------------------------------------------------

            const float planetPhase =
                static_cast<float>(time) * 2.f;

            const auto planetRed =
                static_cast<unsigned char>(
                    std::sin(planetPhase)
                    * 127.f + 128.f);

            const auto planetGreen =
                static_cast<unsigned char>(
                    std::sin(planetPhase + 2.f)
                    * 127.f + 128.f);

            const auto planetBlue =
                static_cast<unsigned char>(
                    std::sin(planetPhase + 4.f)
                    * 127.f + 128.f);

            al_draw_filled_circle(
                planetX,
                planetY,
                planetRadius,
                al_map_rgb(
                    planetRed,
                    planetGreen,
                    planetBlue
                )
            );

            // -------------------------------------------------
            // Pride rainbow
            // -------------------------------------------------
            // From https://gilbertbaker.com/rainbow-flag-color-meanings/ 
            constexpr int PRIDE_NR_COLORS = 8;
            constexpr int PRIDE_COLOR_HEIGHT = 10;

            const ALLEGRO_COLOR pride[
                PRIDE_NR_COLORS
            ] = {
                al_map_rgb(223, 25, 149),   // Hot Pink      Sex
                al_map_rgb(228, 0, 43),     // Red          / Life
                al_map_rgb(254, 80, 0),     // Orange       / Healing
                al_map_rgb(255, 255, 0),    // Yellow       / Sunlight
                al_map_rgb(0, 132, 61),     // Green        / Nature
                al_map_rgb(0, 154, 166),    // Turquoise    / Magic & Art
                al_map_rgb(0, 61, 165),     // Indigo       / Serenity
                al_map_rgb(166, 52, 178)    // Violet       / Spirit
            };

            for (int i = 0; i < PRIDE_NR_COLORS; ++i)
            {
                al_draw_filled_rectangle(
                    0.f,
                    static_cast<float>(
                        VIDEO_MODE_HEIGHT -
                        PRIDE_NR_COLORS *
                        PRIDE_COLOR_HEIGHT +
                        i * PRIDE_COLOR_HEIGHT
                        ),
                    static_cast<float>(
                        VIDEO_MODE_WIDTH
                        ),
                    static_cast<float>(
                        VIDEO_MODE_HEIGHT -
                        PRIDE_NR_COLORS *
                        PRIDE_COLOR_HEIGHT +
                        (i + 1) *
                        PRIDE_COLOR_HEIGHT
                        ),
                    pride[i]
                );
            }
            if (logo)
            {
                al_draw_bitmap(logo, 20, 20, 0);
            }
            al_flip_display();
        }
    }

    // =========================================================
    // Opruimen
    // =========================================================
    if (logo)
    {
        al_destroy_bitmap(logo);
    }
    al_shutdown_image_addon();
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);

    al_shutdown_primitives_addon();

    return 0;
}