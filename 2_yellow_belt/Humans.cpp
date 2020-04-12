#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person {
public:
	Person (const string& name_, const string& type_) : name(name_), type(type_) {}

	virtual void Walk (const string& destination) const {
		PrintInfo(); cout << " walks to: " << destination << endl;
	}

	const string name;
	const string type;

protected:
	void PrintInfo () const {
		cout << type << ": " << name;
	}
};

class Student : public Person {
public:

	Student (const string& name, const string& favouriteSong) : Person(name, "Student"), fav_song(favouriteSong) {}

	void Learn() {
		PrintInfo(); cout << " learns" << endl;
	}

	void Walk(const string& destination) const override {
		PrintInfo(); cout << " walks to: " << destination << endl;
		SingSong();
	}

	void SingSong() const {
		PrintInfo(); cout << " sings a song: " << fav_song << endl;
	}

	const string fav_song;
};


class Teacher : public Person {
public:

	Teacher (const string& name,const string& subject_) : Person(name, "Teacher"), subject(subject_) {}

	void Teach() const {
		PrintInfo(); cout << " teaches: " << subject << endl;
	}

	const string subject;
};


class Policeman : public Person {
public:
	explicit Policeman (const string& name) : Person(name, "Policeman") {}

	void Check(const Person& man) const {
		PrintInfo(); cout << " checks " << man.type << ". "
		     << man.type << "'s name is: " << man.name << endl;
	}
};

void VisitPlaces (Person& man, const vector<string>& places) {
	for (auto& p : places) {
		man.Walk(p);
	}
}

int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");


	VisitPlaces(t, {"Moscow", "London"});
	p.Check(s);
	VisitPlaces(s, {"Moscow", "London"});
	return 0;
}