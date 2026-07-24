#include <iostream>
#include <atomic>

#include "term_utils.hpp"

int main(int argc, char **argv)
{
    char c;
    std::cout << "Hello World!" << std::endl;

    enableRaw();

    while (true)
    {
        c = getchar();
        if (c == 'q')
            break;
        std::cout << "Key Pressed: " << c << std::endl;
    }
    disableRaw();

    return 0;
}