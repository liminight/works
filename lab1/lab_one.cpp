#include <iostream>
#include <cstddef>

int main()
{

    size_t count = 0;
    int x = 0;
    int y = 0;
    while (std::cin >> x)
    {
        if (x == 0)
        {
            break;
        }
        if ((x > y) && (y != 0))
        {
            if (count == std::numeric_limits<size_t>::max())
            {
                std::cerr << "the sequence is too long" << std::endl;
                return 2;
            }
        }

        y = x;
    }
    if (std::cin.fail())
    {
        std::cerr << "invalid input" << std::endl;
        return 1;
    }
    std::cout << count << std::endl;
    return 0;
}
