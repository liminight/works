#include <iostream>
#include <new>

void freeMatrix(int **a, int rows)
{
    if (a == nullptr)
        return;
    for (int i = 0; i < rows; ++i)
    {
        delete[] a[i];
    }
    delete[] a;
}

int main()
{
    size_t lines = 0, columns = 0;
    if (!(std::cin >> lines >> columns))
    {
        return 1;
    }

    int **a = new (std::nothrow) int *[lines];

    if (a == nullptr)
    {
        return 2;
    }

    for (int i = 0; i < lines; ++i)
    {
        a[i] = nullptr;
    }

    for (int i = 0; i < lines; ++i)
    {
        a[i] = new (std::nothrow) int[columns];
        if (a[i] == nullptr)
        {
            freeMatrix(a, i);
            return 2;
        }
    }

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (!(std::cin >> a[i][j]))
            {
                freeMatrix(a, lines);
                return 1;
            }
        }
    }
    std::cout << '\n';
    for (int j = 0; j < columns; ++j)
    {
        for (int i = 0; i < lines; ++i)
        {
            if (i > 0)
                std::cout << ' ';
            std::cout << a[i][j];
        }
        std::cout << '\n';
    }
    freeMatrix(a, lines);
    return 0;
}
// исправлено
