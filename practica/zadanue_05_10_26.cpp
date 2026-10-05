#include <iostream>
#include <new>
#include <cstddef>
#include <limits>

int main()
{
    size_t n = 0;
    if (!(std::cin >> n))
    {
        return 1;
    }

    if (n == 0)
    {
        return 3;
    }

    int *arr = new (std::nothrow) int[n];
    if (!arr)
    {
        return 2;
    }

    long long sum = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!(std::cin >> arr[i]))
        {
            delete[] arr;
            return 1;
        }
        sum += arr[i];
    }

    double avg = static_cast<double>(sum) / static_cast<double>(n);

    for (int i = 0; i < n; ++i)
    {
        if (i > 0)
        {
            std::cout << ' ';
        }
        std::cout << arr[i];
    }
    std::cout << '\n';
    std::cout << sum << '\n';
    std::cout << avg << '\n';

    delete[] arr;

    return 0;
}
