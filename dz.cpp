#include <iostream>
#include <new>

void freeMatrix(int **a, int rows)
{
    if (!a)
        return;

    for (int i = 0; i < rows; ++i)
    {
        delete[] a[i];
    }
    delete[] a;
}

int main()
{
    int lines, columns;

    if (!(std::cin >> lines >> columns) || lines <= 0 || columns <= 0)
    {
        return 1;
    }

    int **a = new (std::nothrow) int *[lines];

    if (!a)
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
        if (!a[i])
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
