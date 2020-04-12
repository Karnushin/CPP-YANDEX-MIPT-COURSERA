#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    return (a % b == 0) ? abs(b) : gcd(b, a % b);
}
int lcm(int a, int b) {
    return abs(a * b) / gcd(a, b);
}

class Rational {
public:
    Rational(): num(0), denom(1) {};
    Rational(int numerator, int denominator) {
        if (!denominator) {
            throw invalid_argument("Invalid argument");
        }
        int tmp = gcd(numerator, denominator);
        num = numerator / tmp;
        denom = denominator / tmp;
        if (denom < 0) {
            num = -num;
            denom = -denom;
        }
    }
    
    int Numerator() const {
        return num;
    }
    int Denominator() const {
        return denom;
    }
    
private:
    int num, denom;
    
};

bool operator== (const Rational& r1, const Rational& r2) {
    return r1.Numerator() == r2.Numerator() && r1.Denominator() == r2.Denominator();
}

Rational operator+ (const Rational& r1, const Rational& r2) {
    int denom = lcm(r1.Denominator(), r2.Denominator());
    int num = denom / r1.Denominator() * r1.Numerator() + denom / r2.Denominator() * r2.Numerator();
    return {num, denom};
}

Rational operator- (const Rational& r1, const Rational& r2) {
    int denom = lcm(r1.Denominator(), r2.Denominator());
    int num = denom / r1.Denominator() * r1.Numerator() - denom / r2.Denominator() * r2.Numerator();
    return {num, denom};
}

Rational operator* (const Rational& r1, const Rational& r2) {
    int num = r1.Numerator() * r2.Numerator();
    int denom = r1.Denominator() * r2.Denominator();
    return {num, denom};
}

Rational operator/ (const Rational& r1, const Rational& r2) {
    if (r2.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    int num = r1.Numerator() * r2.Denominator();
    int denom = r1.Denominator() * r2.Numerator();
    return {num, denom};
}

istream& operator>> (istream& stream, Rational& r) {
    int a, b;
    stream >> a;
    stream.ignore(1);
    stream >> b;
    if (stream) {
        r = {a, b};
    }
    return stream;
}

ostream& operator<< (ostream& stream, const Rational& r) {
    stream << r.Numerator() << "/" << r.Denominator();
    return stream;
}

bool operator< (const Rational& r1, const Rational& r2) {
    return (r1 - r2).Numerator() < 0;
    
}

int main() {
    Rational r1, r2, ans;
    bool flag = false;
    char operation;
    try {
        cin >> r1 >> operation >> r2;
        switch (operation) {
            case '+':
                ans = r1 + r2;
                break;
            case '-':
                ans = r1 - r2;
                break;
            case '*':
                ans = r1 * r2;
                break;
            case '/':
                ans = r1 / r2;
                break;
        }
    } catch(const exception& e) {
        flag = true;
        cout << e.what() << endl;
    }
    if (!flag)
        cout << ans << endl;
    
    return 0;
}



