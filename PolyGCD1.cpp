// TODO: need to determine whether it is better (for precision) to make leading coefficients small at each step (and/or scale everything up/down by a certain amount)

#include "All.h"

using Poly = vd;

// https://en.wikipedia.org/wiki/Polynomial_greatest_common_divisor#Properties

// utilizes gcd(f, g) = gcd(f - kg, g), where k is a constant (this one is more simplistic)
Poly polyGCD1(Poly p1, Poly p2)
{
    while (true)
    {
        for (Poly& pi : {ref(p1), ref(p2)})
        {
            while (!pi.empty() && abs(pi.back()) < EPS)
                pi.pop_back();
        }

        if (p1.size() < p2.size())
            swap(p1, p2);
        if (p2.empty())
            break;

        int o = p1.size() - p2.size();
        ld coef = p1.back() / p2.back();
        for (int i = 0; i < p2.size() - 1; i++)
        {
            if (abs(p2[i]) > EPS)
                p1[i + o] -= coef * p2[i];
        }
        p1.pop_back();
    }

    if (!p1.empty())
    {
        for (ld& x : p1)
            x /= p1.back();
    }

    return p1;
}

