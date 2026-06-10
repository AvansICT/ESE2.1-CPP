#include <iostream>
#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>
#include <boost/units/quantity.hpp>
#include <boost/random.hpp>
#include <boost/geometry.hpp>

namespace si = boost::units::si;
using namespace boost::units;
namespace bg = boost::geometry;

#define NR_OF_TURNS 5

static void boost_example_with_units(void)
{
    std::cout << "Boost example with units" << std::endl;
    // Define a typedef for a quantity of length using SI units
    typedef quantity<si::length> Length;
    typedef quantity<si::mass> Mass;
    typedef quantity<si::time> Time;
    typedef quantity<si::velocity> Velocity;
    typedef quantity<si::force> Force;
    typedef quantity<si::acceleration> Acceleration;
    typedef decltype(std::declval<Mass>()* std::declval<Velocity>()) Momentum;

    // Maak instanties van eenheden
    Length length(5.0 * si::meters);
    Mass mass(2.0 * si::kilograms);
    Time time(3.0 * si::seconds);
    Acceleration acc = (2.0 * si::meters_per_second_squared);
    Velocity v = (3.0 * si::meters_per_second);

    // Berekeningen met eenheden
    Velocity velocity = length / time;
    Force force = mass * acc;
    Momentum momentum = mass * v;

    // Uitvoer van resultaten
    std::cout << "Length: " << length << std::endl;
    std::cout << "Mass: " << mass << std::endl;
    std::cout << "Time: " << time << std::endl;
    std::cout << "Velocity: " << velocity << std::endl;
    std::cout << "Force: " << force << std::endl;
    std::cout << "Momentum: " << momentum << std::endl;

}

static void boost_example_with_random(void)
{
    std::cout << "Boost example with random number generation" << std::endl;
    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> dist(1, 6);

    // 1 dice
    for (int cnt = 0; cnt < NR_OF_TURNS; ++cnt)
    {
        std::cout << "Worp " << (cnt + 1)
            << ": "
            << dist(rng)
            << std::endl;
    }

    for (int i = 0; i < NR_OF_TURNS; ++i)
    {
        int dice1 = dist(rng);
        int dice2 = dist(rng);

        std::cout << "Worp " << (i + 1)
            << ": "
            << dice1
            << " + "
            << dice2
            << " = "
            << (dice1 + dice2)
            << std::endl;
    }
}

static void boost_example_with_geometry(void)
{
    std::cout << "Boost geometry example" << std::endl;
    //https://en.wikipedia.org/wiki/Cartesian_coordinate_system
    bg::model::point<double, 2, bg::cs::cartesian> p1(0.0, 0.0);
    bg::model::point<double, 2, bg::cs::cartesian> p2(3.0, 4.0);

    double distance = bg::distance(p1, p2);

    std::cout << "Distance: " << distance << std::endl; // Stelling van Pythagoras

}

int main() 
{
    std::cout << "Using boost version: " << BOOST_VERSION << "(" << BOOST_LIB_VERSION << ")" << std::endl;
    std::cout << __DATE__ << " " << __TIME__ << std::endl;

    boost_example_with_units();

    boost_example_with_random();

    boost_example_with_geometry();
    return 0;
}
