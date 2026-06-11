#ifndef _ROBOT_HPP_ 
#define _ROBOT_HPP_
#include <string>

namespace avans
{
    enum direction { Left,Right=3, Up, Down };
    enum class color { Red, Green, Blue, Yellow }; //  scoped enumeration for colors
    typedef struct _robotInfo
    {
        unsigned int id;
        direction   dir;
        std::string name;
        color       robotcolor;
        uint32_t    ipaddr; // IPv4 address as 32-bit integer
    }RobotInfo;

    class Robot
    {
    private:
        // klassen attributen
        RobotInfo info;
        direction dir;
        // klassen methoden
        void logDirectionChange(direction newDir);
    public:
        // constructor met initialisatie van ip-adres
        Robot(uint32_t ipaddr=0, unsigned int id=0);
        ~Robot(void);
        void setDirection(direction d);
        direction getDirection(void);
    };
}
#endif
