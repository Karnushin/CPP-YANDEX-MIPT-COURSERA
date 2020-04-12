#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>

using namespace std;
tuple<string, string> BuildJoinedNames (vector<string>& v) {
    string extra_name, cur_name;
    if (!v.empty()) {
        v.erase(unique(v.begin(), v.end()), v.end());
        cur_name = *(--v.end());
        v.pop_back();
        if (!v.empty()) {
            extra_name += " (" + *(--v.end());
            if (v.size() > 1) {
                for (auto it = --v.rbegin(); it != v.rend(); --it) {
                    extra_name += ", " + *it;
                }
            }
            extra_name += ")";
        }
    }
    return make_tuple(cur_name, extra_name);
}
class Person {
public:
    Person (const string& name, const string& surname, const int& year) {
        CreateInfo(name, surname, year);
    }
    void ChangeFirstName(int year, const string& first_name) {
        if (year > birth.begin()->first)
            m[year].first = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        if (year > birth.begin()->first)
            m[year].second = last_name;
    }
    string GetFullName(int year) const {

        if (m.empty()) {
            return "Incognito";
        } else if (year < birth.begin()->first) {
            return "No person";
        }

        string fn, ln;

        for (const auto& item : m) {
            if (!item.second.first.empty() && year >= item.first) {
                fn = item.second.first;
            }
            if (!item.second.second.empty() && year >= item.first) {
                ln = item.second.second;
            }
        }

        if (fn.empty()) return ln + " with unknown first name";
        else if (ln.empty()) return fn + " with unknown last name";
        else return fn + " " + ln;

    }

    string GetFullNameWithHistory(int year) const {
        if (m.empty()) {
            return "Incognito";
        } else if (birth.begin()->first > year) {
            return "No person";
        }

        vector<string> hist_fn, hist_ln;
        for (const auto& item : m) {
            if (!item.second.first.empty() && year >= item.first) {
                hist_fn.push_back(item.second.first);
            }
            if (!item.second.second.empty() && year >= item.first) {
                hist_ln.push_back(item.second.second);
            }
        }

        string cur_fn, cur_ln;
        string extra_fn, extra_ln;

        tie(cur_fn, extra_fn) = BuildJoinedNames(hist_fn);
        tie(cur_ln, extra_ln) = BuildJoinedNames(hist_ln);

        if (cur_fn.empty()) return cur_ln + extra_ln + " with unknown first name";
        else if (cur_ln.empty()) return cur_fn + extra_fn + " with unknown last name";
        else return cur_fn + extra_fn + " " + cur_ln + extra_ln;

    }


private:
    void CreateInfo (const string& name, const string& surname, const int& year) {
        birth[year].first = name;
        birth[year].second = surname;
        m[year].first = name;
        m[year].second = surname;
    }
    map<int, pair<string, string>> birth;
    map<int, pair<string, string>> m;
};
int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}



