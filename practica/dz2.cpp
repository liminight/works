#include <iostream>
#include <algorithm>
#include <new>
#include <cstddef>

void free_matrix(int **matrix, size_t n)
{
    if (matrix == nullptr)
    {
        return;
    }
    for (size_t i = 0; i < n; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int **concat_rows(const int *const *lhs, size_t n1, size_t m1, const int *const *rhs, size_t n2, size_t m2)
{
    size_t max_n = std::max(n1, n2);

    int **res = new (std::nothrow) int *[max_n];

    if (res == nullptr)
    {
        return nullptr;
    }

    for (size_t i = 0; i < max_n; ++i)
    {
        size_t len = 0;
        if (i < n1)
        {
            len += m1;
        }
        if (i < n2)
        {
            len += m2;
        }

        res[i] = new (std::nothrow) int[len];

        if (res[i] == nullptr)
        {
            free_matrix(res, i);
            return nullptr;
        }

        size_t k = 0;

        if (i < n1)
        {
            for (size_t j = 0; j < m1; ++j)
            {
                res[i][k] = lhs[i][j];
                ++k;
            }
        }

        if (i < n2)
        {
            for (size_t j = 0; j < m2; ++j)
            {
                res[i][k] = rhs[i][j];
                ++k;
            }
        }
    }
    return res;
}
int **read_matrix(size_t &n, size_t &m, int &err)
{
    if (!(std::cin >> n >> m))
    {
        std::cerr << "Input error: the matrix size could not be read\n";
        err = 1;
        return nullptr;
    }

    int **mat = new (std::nothrow) int *[n];
    if (n > 0 && mat == nullptr)
    {
        std::cerr << "Memory error: failed to allocate memory for the array of pointers\n";
        err = 2;
        return nullptr;
    }

    for (size_t i = 0; i < n; ++i)
    {
        mat[i] = new (std::nothrow) int[m];

        if (m > 0 && mat[i] == nullptr)
        {
            std::cerr << "Memory error: failed to allocate memory for the string\n";
            free_matrix(mat, i);
            err = 2;
            return nullptr;
        }
        for (size_t j = 0; j < m; ++j)
        {
            if (!(std::cin >> mat[i][j]))
            {
                std::cerr << "Input error: unable to read element\n";
                free_matrix(mat, i + 1);
                err = 1;
                return nullptr;
            }
        }
    }
    err = 0;
    return mat;
}

int main()
{
    size_t n1, m1, n2, m2;
    int err;

    int **lhs = read_matrix(n1, m1, err);
    if (err != 0)
    {
        return err;
    }

    int **rhs = read_matrix(n2, m2, err);
    if (err != 0)
    {
        free_matrix(lhs, n1);
        return err;
    }
    int **res = concat_rows(lhs, n1, m1, rhs, n2, m2);
    size_t max_n = std::max(n1, n2);

    if (max_n > 0 && res == nullptr)
    {
        std::cerr << "Memory error: failed to allocate memory for the resulting array\n";
        free_matrix(lhs, n1);
        free_matrix(rhs, n2);
        return 2;
    }

    std::cout << " ";
    std::cout << "result: \n";
    for (size_t i = 0; i < max_n; ++i)
    {
        size_t len = 0;
        if (i < n1)
        {
            len += m1;
        }
        if (i < n2)
        {
            len += m2;
        }

        for (size_t j = 0; j < len; ++j)
        {
            std::cout << res[i][j] << " ";
        }
        std::cout << "\n";
    }
    free_matrix(lhs, n1);
    free_matrix(rhs, n2);
    free_matrix(res, max_n);

    return 0;
}