// TODO: this code still needs to be properly tested
// TODO: try to reduce copies a bit more (useful reference: https://en.cppreference.com/w/cpp/language/copy_elision )

#include "All.h"

struct Poly
{
    vd terms;

    Poly() {}

    // creates polynomial cx^e
    Poly(ld coef, int expo = 0) : terms(expo)
    {
        terms.back() = coef;
    }

    // returns the degree (or -1 if it's the 0 polynomial)
    int deg()
    {
        return terms.empty() ? -1 : terms.size() - 1;
    }

    // return the leading term as {coefficient, exponent} (or {NaN, -1} for the 0 polynomial)
    pair<double, int> lt()
    {
        return {terms.empty() ? NAN : terms.back(), (int)terms.size() - 1};
    }

    void prune()
    {
        while (!terms.empty() && isZero(terms.back()))
            terms.pop_back();
    }

    Poly& operator*=(ld scale)
    {
        if (isZero(scale))
            terms.clear();
        else for (ld& coef : terms)
                coef *= scale;

        return *this;
    }

    Poly& operator<<=(int expo)
    {
        if (expo < 0)
            operator>>=(-expo);
        else if (expo > 0)
            terms.insert(terms.begin(), expo, 0);

        return *this;
    }

    Poly& operator>>=(int expo)
    {
        if (expo < 0)
            operator<<=(-expo);
        else if (expo > 0)
            terms.erase(terms.begin(), terms.begin() + min<int>(terms.size(), expo));

        return *this;
    }

    Poly& operator+=(Poly p)
    {
        if (p.deg() > deg())
            swap(terms, p.terms);
        for (int i = 0; i < p.terms.size(); i++)
            terms[i] += p.terms[i];
        prune();

        return *this;
    }

    Poly& operator-=(Poly p)
    {
        return operator+=(p *= -1);
    }

    Poly operator*(ld scale)
    {
        Poly res = *this;
        res *= scale;
        return res;
    }

    Poly operator<<(int expo)
    {
        Poly res = *this;
        res <<= expo;
        return res;
    }

    Poly operator>>(int expo)
    {
        Poly res = *this;
        res >>= expo;
        return res;
    }

    Poly operator+(Poly p)
    {
        p += *this;
        return p;
    }

    Poly operator-(Poly p)
    {
        p *= -1;
        p += *this;
        return p;
    }

private:
    bool isZero(ld coef)
    {
        return abs(coef) < EPS;
    }
};

