#include <iostream>
#include "log.hpp"
#include "rekenen.hpp"

namespace MijnRekenNamespace {

    int NameSpaceAdd(int x, int y) {
//        LOG_DEBUG;
        return x + y;
    }

    MijnRekenKlasse::MijnRekenKlasse(void)
    {
        std::cout << "MijnRekenKlasse Constructor(" << __FUNCTION__ <<")" << std::endl;
    }

    MijnRekenKlasse::~MijnRekenKlasse(void)
    {
        std::cout << "MijnRekenKlasse DeConstructor(" << __FUNCTION__ << ")" << std::endl;
    }

    int MijnRekenKlasse::add(int x, int y)
    {
//        LOG_DEBUG;
        return x + y;
    }
}
