#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

#include <SFML/Graphics.hpp>
#include "log.hpp"

// ============================================================
// Rainbow
// ============================================================

class Rainbow
{
public:

    static sf::Color color(float t)
    {
        float r = std::sin(t) * 127.f + 128.f;
        float g = std::sin(t + 2.094f) * 127.f + 128.f;
        float b = std::sin(t + 4.188f) * 127.f + 128.f;

        return sf::Color(
            static_cast<std::uint8_t>(r),
            static_cast<std::uint8_t>(g),
            static_cast<std::uint8_t>(b)
        );
    }
};

// ============================================================
// Sound
// ============================================================

class Sound
{
public:

    static void beep(unsigned int frequency,
        unsigned int duration)
    {
#ifdef _WIN32

        // Windows
        Beep(frequency, duration);

#else

        // Linux
        // Terminal bell
        std::cout << '\a' << std::flush;

        // Houd ongeveer dezelfde timing aan
        std::this_thread::sleep_for(
            std::chrono::milliseconds(duration)
        );

#endif
    }

    static void shoot()
    {
        beep(1000, 35);
    }

    static void hit()
    {
        beep(700, 40);
        beep(1100, 40);
        beep(1500, 60);
    }

    static void gameOver()
    {
        beep(500, 100);
        beep(350, 100);
        beep(200, 200);
    }
};

// ============================================================
// Bullet
// ============================================================

class Bullet
{
private:

    sf::RectangleShape shape;
    float speed;

public:

    Bullet(sf::Vector2f position)
        : speed(600.f)
    {
        shape.setSize({
            6.f,
            22.f
            });

        shape.setOrigin({
            3.f,
            11.f
            });

        shape.setPosition(position);
    }

    void update(float dt, float time)
    {
        shape.move({
            0.f,
            -speed * dt
            });

        shape.setFillColor(
            Rainbow::color(time * 8.f)
        );
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(shape);
    }

    bool isOutside() const
    {
        return shape.getPosition().y < -30.f;
    }

    sf::FloatRect getBounds() const
    {
        return shape.getGlobalBounds();
    }

    void destroy()
    {
        shape.setPosition({
            -100.f,
            -100.f
            });
    }
};

// ============================================================
// Explosion
// ============================================================

class Explosion
{
private:

    sf::CircleShape shape;

    float lifetime;
    float maxLifetime;

public:

    Explosion(sf::Vector2f position, float time)
        : lifetime(0.f),
        maxLifetime(0.4f)
    {
        shape.setRadius(8.f);

        shape.setOrigin({
            8.f,
            8.f
            });

        shape.setPosition(position);

        shape.setFillColor(
            Rainbow::color(time * 10.f)
        );
    }

    void update(float dt, float time)
    {
        lifetime += dt;

        float progress =
            lifetime / maxLifetime;

        float size =
            8.f + progress * 45.f;

        shape.setRadius(size);

        shape.setOrigin({
            size,
            size
            });

        shape.setFillColor(
            Rainbow::color(
                time * 10.f +
                progress * 5.f
            )
        );
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(shape);
    }

    bool finished() const
    {
        return lifetime >= maxLifetime;
    }
};

// ============================================================
// Enemy
// ============================================================

class Enemy
{
private:

    sf::RectangleShape shape;

    bool alive;

public:

    Enemy(sf::Vector2f position)
        : alive(true)
    {
        shape.setSize({
            45.f,
            28.f
            });

        shape.setOrigin({
            22.5f,
            14.f
            });

        shape.setPosition(position);
    }

    void update(float dt,
        float direction,
        float time,
        int index)
    {
        if (!alive)
            return;

        shape.move({
            80.f * direction * dt,
            0.f
            });

        shape.setFillColor(
            Rainbow::color(
                time * 2.f +
                index * 0.15f
            )
        );
    }

    void moveDown()
    {
        if (alive)
        {
            shape.move({
                0.f,
                25.f
                });
        }
    }

    void draw(sf::RenderWindow& window) const
    {
        if (alive)
        {
            window.draw(shape);
        }
    }

    bool isAlive() const
    {
        return alive;
    }

    void destroy()
    {
        alive = false;
    }

    sf::Vector2f getPosition() const
    {
        return shape.getPosition();
    }

    sf::FloatRect getBounds() const
    {
        return shape.getGlobalBounds();
    }
};

// ============================================================
// Player
// ============================================================

class Player
{
private:

    sf::RectangleShape shape;

    float speed;

    std::vector<sf::CircleShape> trail;

public:

    Player()
        : speed(450.f)
    {
        shape.setSize({
            60.f,
            20.f
            });

        shape.setOrigin({
            30.f,
            10.f
            });

        shape.setPosition({
            500.f,
            680.f
            });

        // --------------------------------------------
        // Rainbow trail
        // --------------------------------------------

        for (int i = 0; i < 15; ++i)
        {
            sf::CircleShape particle(
                3.f + (15 - i) * 0.15f
            );

            particle.setOrigin({
                particle.getRadius(),
                particle.getRadius()
                });

            trail.push_back(particle);
        }
    }

    void update(float dt, float time)
    {
        // --------------------------------------------
        // Movement
        // --------------------------------------------

        if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::Left))
        {
            shape.move({
                -speed * dt,
                0.f
                });
        }

        if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::Right))
        {
            shape.move({
                speed * dt,
                0.f
                });
        }

        // --------------------------------------------
        // Boundaries
        // --------------------------------------------

        auto position =
            shape.getPosition();

        if (position.x < 30.f)
        {
            shape.setPosition({
                30.f,
                position.y
                });
        }

        if (position.x > 970.f)
        {
            shape.setPosition({
                970.f,
                position.y
                });
        }

        // --------------------------------------------
        // Rainbow player
        // --------------------------------------------

        shape.setFillColor(
            Rainbow::color(time * 4.f)
        );

        // --------------------------------------------
        // Rainbow trail
        // --------------------------------------------

        for (int i = 0;
            i < static_cast<int>(trail.size());
            ++i)
        {
            trail[i].setPosition({
                shape.getPosition().x,
                shape.getPosition().y +
                    18.f +
                    i * 4.f
                });

            trail[i].setFillColor(
                Rainbow::color(
                    time * 5.f +
                    i * 0.3f
                )
            );
        }
    }

    Bullet shoot()
    {
        Sound::shoot();

        return Bullet({
            shape.getPosition().x,
            shape.getPosition().y - 25.f
            });
    }

    void draw(sf::RenderWindow& window) const
    {
        for (const auto& particle : trail)
        {
            window.draw(particle);
        }

        window.draw(shape);
    }
};

// ============================================================
// Game
// ============================================================

class Game
{
private:

    sf::RenderWindow window;

    Player player;

    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<Explosion> explosions;

    float enemyDirection;
    float enemySpeed;

    int score;

    bool gameOver;

    sf::Clock clock;

    float totalTime;

public:

    Game()
        : window(
            sf::VideoMode({ 1000, 750 }),
            "Rainbow Space Invaders"
        ),
        enemyDirection(1.f),
        enemySpeed(80.f),
        score(0),
        gameOver(false),
        totalTime(0.f)
    {
        window.setFramerateLimit(60);

        createEnemies();
    }

    void run()
    {
        while (window.isOpen())
        {
            processEvents();

            float dt =
                clock.restart().asSeconds();

            totalTime += dt;

            if (!gameOver)
            {
                update(dt);
            }

            draw();
        }
    }

private:

    // ========================================================
    // Create enemies
    // ========================================================

    void createEnemies()
    {
        const int rows = 5;
        const int columns = 11;

        for (int row = 0;
            row < rows;
            ++row)
        {
            for (int column = 0;
                column < columns;
                ++column)
            {
                enemies.emplace_back(
                    sf::Vector2f{
                        130.f +
                            column * 70.f,
                        100.f +
                            row * 50.f
                    }
                );
            }
        }
    }

    // ========================================================
    // Events
    // ========================================================

    void processEvents()
    {
        while (const auto event =
            window.pollEvent())
        {
            if (event->is<
                sf::Event::Closed>())
            {
                window.close();
            }

            if (event->is<
                sf::Event::KeyPressed>())
            {
                const auto* key =
                    event->getIf<
                    sf::Event::KeyPressed>();

                if (!key)
                    continue;

                // --------------------------------------------
                // Shoot
                // --------------------------------------------

                if (key->code ==
                    sf::Keyboard::Key::Space &&
                    !gameOver)
                {
                    bullets.push_back(
                        player.shoot()
                    );
                }

                // --------------------------------------------
                // Restart
                // --------------------------------------------

                if (key->code ==
                    sf::Keyboard::Key::R &&
                    gameOver)
                {
                    restart();
                }
            }
        }
    }

    // ========================================================
    // Update
    // ========================================================

    void update(float dt)
    {
        player.update(
            dt,
            totalTime
        );

        updateBullets(dt);

        updateEnemies(dt);

        checkCollisions();

        updateExplosions(dt);

        removeObjects();

        checkGameOver();

        checkWin();
    }

    // ========================================================
    // Bullets
    // ========================================================

    void updateBullets(float dt)
    {
        for (auto& bullet : bullets)
        {
            bullet.update(
                dt,
                totalTime
            );
        }
    }

    // ========================================================
    // Enemies
    // ========================================================

    void updateEnemies(float dt)
    {
        bool hitEdge = false;

        for (const auto& enemy : enemies)
        {
            if (!enemy.isAlive())
                continue;

            float x =
                enemy.getPosition().x;

            if (x > 950.f ||
                x < 50.f)
            {
                hitEdge = true;
                break;
            }
        }

        if (hitEdge)
        {
            enemyDirection *= -1.f;

            for (auto& enemy : enemies)
            {
                enemy.moveDown();
            }
        }

        for (int i = 0;
            i < static_cast<int>(
                enemies.size());
            ++i)
        {
            enemies[i].update(
                dt,
                enemyDirection,
                totalTime,
                i
            );
        }
    }

    // ========================================================
    // Collision detection
    // ========================================================

    void checkCollisions()
    {
        for (auto& bullet : bullets)
        {
            for (auto& enemy : enemies)
            {
                if (!enemy.isAlive())
                    continue;

                if (bullet.getBounds()
                    .findIntersection(
                        enemy.getBounds()))
                {
                    enemy.destroy();

                    bullet.destroy();

                    score += 10;

                    explosions.emplace_back(
                        enemy.getPosition(),
                        totalTime
                    );

                    Sound::hit();

                    break;
                }
            }
        }
    }

    // ========================================================
    // Explosions
    // ========================================================

    void updateExplosions(float dt)
    {
        for (auto& explosion : explosions)
        {
            explosion.update(
                dt,
                totalTime
            );
        }
    }

    // ========================================================
    // Remove dead objects
    // ========================================================

    void removeObjects()
    {
        bullets.erase(
            std::remove_if(
                bullets.begin(),
                bullets.end(),
                [](const Bullet& bullet)
                {
                    return bullet.isOutside();
                }),
            bullets.end()
        );

        explosions.erase(
            std::remove_if(
                explosions.begin(),
                explosions.end(),
                [](const Explosion& explosion)
                {
                    return explosion.finished();
                }),
            explosions.end()
        );
    }

    // ========================================================
    // Game over
    // ========================================================

    void checkGameOver()
    {
        for (const auto& enemy : enemies)
        {
            if (!enemy.isAlive())
                continue;

            if (enemy.getPosition().y >
                630.f)
            {
                gameOver = true;

                Sound::gameOver();

                return;
            }
        }
    }

    // ========================================================
    // Win / new level
    // ========================================================

    void checkWin()
    {
        for (const auto& enemy : enemies)
        {
            if (enemy.isAlive())
                return;
        }

        enemySpeed += 30.f;

        createEnemies();
    }

    // ========================================================
    // Restart
    // ========================================================

    void restart()
    {
        enemies.clear();
        bullets.clear();
        explosions.clear();

        enemyDirection = 1.f;
        enemySpeed = 80.f;

        score = 0;

        gameOver = false;

        createEnemies();
    }

    // ========================================================
    // Draw
    // ========================================================

    void draw()
    {
        window.clear(
            sf::Color(8, 3, 20)
        );

        drawStars();

        player.draw(window);

        for (const auto& bullet : bullets)
        {
            bullet.draw(window);
        }

        for (const auto& enemy : enemies)
        {
            enemy.draw(window);
        }

        for (const auto& explosion : explosions)
        {
            explosion.draw(window);
        }

        window.display();
    }

    // ========================================================
    // Stars
    // ========================================================

    void drawStars()
    {
        for (int i = 0; i < 100; ++i)
        {
            float x =
                static_cast<float>(
                    (i * 97) % 1000
                    );

            float baseY =
                static_cast<float>(
                    (i * 53) % 750
                    );

            float y =
                std::fmod(
                    baseY +
                    totalTime *
                    (20.f + i % 30),
                    750.f
                );

            sf::CircleShape star(
                1.f + (i % 3)
            );

            star.setOrigin({
                star.getRadius(),
                star.getRadius()
                });

            star.setPosition({
                x,
                y
                });

            star.setFillColor(
                Rainbow::color(
                    totalTime * 2.f +
                    i * 0.2f
                )
            );

            window.draw(star);
        }
    }


};

// ============================================================
// MAIN
// ============================================================

int main([[maybe_unused]] int argc,
    [[maybe_unused]] char* argv[])
{
    std::cout << "Invaders ("
        << __FILE__
        << ")\n";

    std::cout << __DATE__
        << " "
        << __TIME__
        << std::endl;

    LogTargetArchitecture();
    LogRunTimeArchitecture();
    LogTargetOperatingSystem();
    LogTargetCompiler();
    LogTargetCxxStandard();

    std::cout << "SFML version: "
        << SFML_VERSION_MAJOR << "."
        << SFML_VERSION_MINOR << "."
        << SFML_VERSION_PATCH << '\n';

    Game game;

    game.run();

    return 0;
}