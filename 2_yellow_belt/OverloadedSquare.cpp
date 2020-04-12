#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>

using namespace std;

//можно вместо перегрузки оператора * и написания вида a * a
//пользоваться Sqr(a * a), тогда для составных объектов тоже все будет ок
//так как будет вызываться еще одна функция на квадрат, а в конце уже на простое число

//для простого числа
template <typename T> T Sqr(const T& x);
//для вектора чисел
template <typename T> vector<T> Sqr (const vector<T>& v);
//для пары чисел
template <typename first, typename second>
pair<first, second> Sqr (const pair<first, second>& p);
//для map чисел (в квадрат только значение, не ключ!)
template <typename key, typename val> map<key, val> Sqr(const map<key, val>& m);

//перегрузка произведения для вектора
template <typename T>
vector<T> operator* (const vector<T>& v1, const vector<T>& v2) {
    vector<T> product_vec;
    for (auto it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2) {
        product_vec.push_back(*it1 * *it2);
    }

    return product_vec;
}
//перегрузка произведения для map (в квадрат только ключ)
template <typename key, typename value>
map<key, value> operator* (const map<key, value>& m1, const map<key, value>& m2) {
     map<key, value> product_map;
     for (const auto& item : m1) {
         product_map[item.first] = item.second * item.second;
     }
    return product_map;
}
//перегрузка произведения для пары
template <typename first, typename second>
pair<first, second> operator* (const pair<first, second>& p1, const pair<first, second>& p2) {
    auto product_pair = make_pair(p1.first * p1.first, p1.second * p2.second);
    return product_pair;
}

template <typename T>
T Sqr(const T& x) {
    return x * x;
}

template <typename T>
vector<T> Sqr (const vector<T>& v) {
    vector<T> result;
    for (const T& x : v) {
        // Здесь важно, что вместо x * x вызывается функция Sqr:
        // это позволяет возводить в квадрат составные объекты
        result.push_back(Sqr(x));
    }

    return result;
}

template <typename first, typename second>
pair<first, second> Sqr (const pair<first, second>& p) {
    return p * p;
}

template <typename key, typename val>
map<key, val> Sqr(const map<key, val>& m) {
    return m * m;
}

