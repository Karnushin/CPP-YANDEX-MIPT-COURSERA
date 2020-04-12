#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <regex>

//White

using namespace std;

class Date {
public:
	Date () {};
	Date (const string& s) {
		stringstream stream(s);
		stream >> year;
		stream.ignore(1);
		stream >> month;
		stream.ignore(1);
		stream >> day;
		string str_date = to_string(year) + to_string(month) + to_string(day);
		if (year > 9999) {
			cout << "y= " << year << endl;
			throw runtime_error("Wrong date format: " + str_date);
		} else if (month < 1 or month > 12) {
			throw runtime_error("Month value is invalid: " + to_string(month));
		} else if (day < 1 or day > 31) {
			throw runtime_error("Day value is invalid: " + to_string(day));
		}
	}
	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}

private:
	int year = 1;
	int month = 1;
	int day = 1;
};

bool operator< (const Date& d1, const Date& d2) {
	if (d1.GetYear() < d2.GetYear()) {
		return true;
	} else if (d1.GetYear() == d2.GetYear() and d1.GetMonth() < d2.GetMonth()) {
		return true;
	} else if (d1.GetMonth() == d2.GetMonth() and d1.GetDay() < d2.GetDay()) {
		return true;
	}

	return false;
}

class DataBase {

public:
	void AddEvent (const Date& date,const string& event) {
		information[date].insert(event);
	}
	void DeleteOnlyOne (const Date& date, const string& event) {
		cout << (information[date].erase(event) ? "Deleted successfully" : "Event not found") << endl;
	}

	void DeleteAllEvents (const Date& date) {
		cout << "Deleted " << information[date].size() << " events" << endl;
		information[date].clear();
	}

	void FindEvents (const Date& date) {
		set<string> cur_events = information[date];
		for (const string& w : cur_events) {
			cout << w << endl;
		}
	}

	void PrintAll() const {
		for (auto& item : information) {
			Date d = item.first;
			for (auto& ev : item.second) {
				cout << setw(4) << setfill('0') << d.GetYear() << '-';
				cout << setw(2) << setfill('0') << d.GetMonth() << '-';
				cout << setw(2) << setfill('0') << d.GetDay() << ' ';
				cout << ev << endl;
			}

		}
	}

private:
	map<Date, set<string>> information;
};

void CheckFormat(const string& date) {
	bool flag = true;
	stringstream stream(date);
	int y, m, d;
	stream >> y;
	if (stream.peek() != '-') {
		flag = false;
	}
	stream.ignore(1);
	stream >> m;
	if (stream.peek() != '-') {
		flag = false;
	}
	stream.ignore(1);
	stream >> d;
	if (stream.peek() != EOF) {
		flag = false;
	}

	if (!flag and !date.empty()) {
		throw runtime_error("Wrong date format: " + date);
	}
}

int main () {
	DataBase info;
	string input;
	set<string> com = {"Add", "Del", "Find", "Print"};
	while (getline(cin, input)) {
		if (input.empty()) {
			continue;
		}
		string command, str_date, event;
		Date date;
		stringstream stream(input);
		try {
			stream >> command;
			if (!com.count(command)) {
				throw runtime_error("Unknown command: " + command);
			}
		} catch (runtime_error &ex) {
			cout << ex.what() << endl;
			continue;
		}
		try {
			stream >> str_date;
			CheckFormat(str_date);
			date = {str_date};
			stream >> event;
			if (command == "Add") {
				info.AddEvent(date, event);
			} else if (command == "Del" and !event.empty()) {
				info.DeleteOnlyOne(date, event);
			} else if (command == "Del" and event.empty()) {
				info.DeleteAllEvents(date);
			} else if (command == "Find") {
				info.FindEvents(date);
			} else if (command == "Print") {
				info.PrintAll();
			}
		} catch (runtime_error& ex) {
			cout << ex.what() << endl;
			continue;
		}
	}

	return 0;
}
