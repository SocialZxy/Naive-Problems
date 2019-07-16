#ifndef _BIGFLOATREFERENCE_H_
#define _BIGFLOATREFERENCE_H_

#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <cfloat>
using namespace std;

#define ACCURACY 100

class DividedByZeroException {
public:
    void error();
};

class BigFloat {
private:
    vector<char> integer;
    vector<char> decimal;
    void trim();
    bool tag;
public:

    BigFloat(int);
    BigFloat(string&) ;
    BigFloat();
    BigFloat(const BigFloat&);
    BigFloat operator=(const BigFloat& op);

    BigFloat abs() const;
    BigFloat pow(int a);

    friend BigFloat operator+(const BigFloat&,const BigFloat&);
    friend BigFloat operator-(const BigFloat&,const BigFloat&);
    friend BigFloat operator*(const BigFloat&,const BigFloat&);
    friend BigFloat operator/(const BigFloat&,const BigFloat&) throw(DividedByZeroException);

    friend BigFloat operator-(const BigFloat&);   //negative

    friend bool operator==(const BigFloat&,const BigFloat&);
    friend bool operator==(const BigFloat&,const BigFloat&);
    friend bool operator<(const BigFloat&,const BigFloat&);
    friend bool operator<=(const BigFloat&,const BigFloat&);
    friend bool operator>(const BigFloat&,const BigFloat&);
    friend bool operator>=(const BigFloat&,const BigFloat&);

    friend BigFloat operator+=(BigFloat&,const BigFloat&);
    friend BigFloat operator-=(BigFloat&,const BigFloat&);
    friend BigFloat operator*=(BigFloat&,const BigFloat&);
    friend BigFloat operator/=(BigFloat&,const BigFloat&) throw(DividedByZeroException);

    friend ostream& operator<<(ostream&,const BigFloat&);
    friend istream& operator>>(istream&, BigFloat&);

public:
    static const BigFloat ZERO;
    static const BigFloat ONE;
    static const BigFloat TEN;
};

#endif // _BIGFLOATREFERENCE_H_
