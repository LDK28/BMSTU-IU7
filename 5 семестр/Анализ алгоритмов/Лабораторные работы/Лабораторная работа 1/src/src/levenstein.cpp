#include "levenstein.hpp"

size_t matr_method(const string &str1, const string &str2)
{
    size_t n = str1.length() + 1, m = str2.length() + 1;
    auto matr = new size_t *[n];
    for (size_t i = 0; i < n; i++) 
    {
        matr[i] = new size_t[m];
        matr[i][0] = i;
    }
    for (size_t i = 0; i < m; i++)
        matr[0][i] = i;

    for (size_t i = 1; i < n; i++)
        for (size_t j = 1; j < m; j++)
            matr[i][j] = min(min(matr[i - 1][j] + 1, matr[i][j - 1] + 1), matr[i - 1][j - 1] + (str1[i - 1] == str2[j - 1] ? 0 : 1));

    size_t result = matr[n - 1][m - 1];
    for (size_t i = 0; i < n; i++)
        delete matr[i];
    delete matr;
    return result;
}

size_t recur(const string &str1, const size_t len1, const string &str2, const size_t len2)
{
    if (len1 == len2 && len1 == 0)
        return 0;
    else if (len1 == 0)
        return len2;
    else if (len2 == 0)
        return len1;
    else
    {
        bool flag = str1[len1 - 1] != str2[len2 - 1];
        return min(min(recur(str1, len1 - 1, str2, len2) + 1,
                       recur(str1, len1, str2, len2 - 1) + 1),
                   recur(str1, len1 - 1, str2, len2 - 1) + flag);
    }
}

size_t recur_method(const string &str1, const string &str2)
{
    size_t len1 = str1.length(), len2 = str2.length();
    return recur(str1, len1, str2, len2);
}

size_t rec_cache(const string &str1, const size_t len1, const string &str2, const size_t len2, size_t **matr)
{
    if (matr[len1][len2] != 0)
        return matr[len1][len2];
    else if (len1 == len2 && len1 == 0)
        matr[len1][len2] = 0;
    else if (len1 == 0)
        matr[len1][len2] = len2;
    else if (len2 == 0)
        matr[len1][len2] = len1;
    else
    {
        bool flag = str1[len1 - 1] != str2[len2 - 1];
        matr[len1][len2] = min(min(rec_cache(str1, len1 - 1, str2, len2, matr) + 1,
                                   rec_cache(str1, len1, str2, len2 - 1, matr) + 1),
                               rec_cache(str1, len1 - 1, str2, len2 - 1, matr) + flag);
    }
    return matr[len1][len2];
}

size_t rec_cache_method(const string &str1, const string &str2)
{
    size_t len1 = str1.length(), len2 = str2.length();
    auto matr = new size_t *[len1 + 1];
    for (size_t i = 0; i < len1 + 1; i++)
        matr[i] = new size_t[len2 + 1];
    for (size_t i = 0; i < len1 + 1; i++)
        for (size_t j = 0; j < len2 + 1; j++)
            matr[i][j] = 0;

    rec_cache(str1, len1, str2, len2, matr);

    size_t result = matr[len1][len2];
    for (size_t i = 0; i < len1 + 1; i++)
        delete matr[i];
    delete matr;
    return result;
}

size_t Damerau(const string &str1, const size_t len1, const string &str2, const size_t len2, size_t **matr)
{
    if (matr[len1][len2] != 0)
        return matr[len1][len2];
    else if (len1 == len2 && len1 == 0)
        matr[len1][len2] = 0;
    else if (len1 == 0)
        matr[len1][len2] = len2;
    else if (len2 == 0)
        matr[len1][len2] = len1;
    else 
    {
        bool flag = str1[len1 - 1] != str2[len2 - 1];
        matr[len1][len2] = min(min(Damerau(str1, len1 - 1, str2, len2, matr) + 1,
                                   Damerau(str1, len1, str2, len2 - 1, matr) + 1),
                               Damerau(str1, len1 - 1, str2, len2 - 1, matr) + flag);

        if (len1 > 1 && len2 > 1 && str1[len1 - 2] == str2[len2 - 1] && str1[len1 - 1] == str2[len2 - 2])
            matr[len1][len2] = min(Damerau(str1, len1 - 2, str2, len2 - 2, matr) + 1, matr[len1][len2]);
    }
    return matr[len1][len2];
}

size_t Damerau_method(const string &str1, const string &str2)
{
    size_t len1 = str1.length(), len2 = str2.length();
    auto matr = new size_t *[len1 + 1];
    for (size_t i = 0; i < len1 + 1; i++)
        matr[i] = new size_t[len2 + 1];
    for (size_t i = 0; i < len1 + 1; i++)
        for (size_t j = 0; j < len2 + 1; j++)
            matr[i][j] = 0;

    Damerau(str1, len1, str2, len2, matr);

    size_t result = matr[len1][len2];
    for (size_t i = 0; i < len1 + 1; i++)
        delete matr[i];
    delete matr;
    return result;
}
