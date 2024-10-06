// TODO: need to determine whether it is better (for precision) to make leading coefficients small at each step (and/or scale everything up/down by a certain amount)

#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using Poly = vector<ld>;
constexpr ld EPS = 1e-9;

// https://en.wikipedia.org/wiki/Polynomial_greatest_common_divisor#Properties

void prune(Poly& p)
{
    while (!p.empty() && abs(p.back()) < EPS)
        p.pop_back();
}

// utilizes gcd(f, g) = gcd(r = f - hg, g), where h is a polynomial (this one performs the full division algorithm at each step)
Poly polyGCD2(Poly p1, Poly p2)
{
    prune(p1), prune(p2);

    while (true)
    {
        if (p1.size() < p2.size())
            swap(p1, p2);
        if (p2.empty())
            break;

        while (p1.size() >= p2.size())
        {
            int o = p1.size() - p2.size();
            ld coef = p1.back() / p2.back();
            for (int i = 0; i < p2.size() - 1; i++)
            {
                if (abs(p2[i]) > EPS)
                    p1[i + o] -= coef * p2[i];
            }
            p1.pop_back();

            prune(p1);
        }
    }

    if (!p1.empty())
    {
        for (ld& x : p1)
            x /= p1.back();
    }

    return p1;
}

