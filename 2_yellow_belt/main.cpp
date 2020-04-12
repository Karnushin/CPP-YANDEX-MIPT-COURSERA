#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};


using TasksInfo = map<TaskStatus, int>;

ostream& operator <<(ostream& out, const TaskStatus& status) {
	string statusName;
	switch (status) {
		case TaskStatus::NEW:
			statusName = "\"NEW\"";
			break;
		case TaskStatus::IN_PROGRESS:
			statusName = "\"IN_PROGRESS\"";
			break;
		case TaskStatus::TESTING:
			statusName = "\"TESTING\"";
			break;
		case TaskStatus::DONE:
			statusName = "\"DONE\"";
			break;
	}
	return out << statusName;
}
template <typename Collection>
string Join(const Collection& c, const string& d) {
	stringstream ss;
	bool isFirst = true;
	for (const auto& i : c) {
		if(!isFirst) {
			ss << d;
		}
		isFirst = false;
		ss << i;
	}
	return ss.str();
}
template <typename F, typename S>
ostream& operator <<(ostream& out, const pair<F,S>& p) {
	return out << p.first << ": " << p.second;
}
template <typename K, typename V>
ostream& operator <<(ostream& out, const map<K,V>& m){
	return out << '{' << Join(m, ", ") << '}';
}
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& v) {
	return out << '['  << Join(v, ", ") << ']';
}



TasksInfo operator+(TasksInfo lhs, TasksInfo rhs) {
	TasksInfo temp;
	for (int i = 0; i < 4; ++i) {
		temp[static_cast<TaskStatus>(i)] = lhs[static_cast<TaskStatus>(i)] + rhs[static_cast<TaskStatus>(i)];
	}
	return temp;
}

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return PersonTasks.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		++PersonTasks[person][TaskStatus::NEW];
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		TasksInfo updated, untouched;
		TasksInfo& p = PersonTasks[person];

		int undone = p[TaskStatus::NEW] + p[TaskStatus::IN_PROGRESS] + p[TaskStatus::TESTING];
		task_count = min(task_count, undone);

		if (task_count >= p[TaskStatus::NEW] && task_count > 0) {
			updated[TaskStatus::IN_PROGRESS] = p[TaskStatus::NEW];
			task_count -= p[TaskStatus::NEW];
			//p[TaskStatus::NEW] = 0;
		} else if (task_count < p[TaskStatus::NEW] && task_count > 0) {
			updated[TaskStatus::IN_PROGRESS] = task_count;
			//p[TaskStatus::NEW] -= task_count;
			task_count = 0;
		}

		if (task_count >= p[TaskStatus::IN_PROGRESS] && task_count > 0) {
			updated[TaskStatus::TESTING] = p[TaskStatus::IN_PROGRESS];
			task_count -= p[TaskStatus::IN_PROGRESS];
			//p[TaskStatus::IN_PROGRESS] = 0;
		} else if (task_count < p[TaskStatus::IN_PROGRESS] && task_count > 0) {
			updated[TaskStatus::TESTING] = task_count;
			//p[TaskStatus::IN_PROGRESS] -= task_count;
			task_count = 0;
		}

		if (task_count >= p[TaskStatus::TESTING] && task_count > 0) {
			updated[TaskStatus::DONE] = p[TaskStatus::TESTING];
			task_count -= p[TaskStatus::TESTING];
			//p[TaskStatus::TESTING] = 0;
		} else if (task_count < p[TaskStatus::TESTING] && task_count > 0) {
			updated[TaskStatus::DONE] = task_count;

		}

		untouched[TaskStatus::NEW] = p[TaskStatus::NEW] - updated[TaskStatus::IN_PROGRESS];
		untouched[TaskStatus::IN_PROGRESS] = p[TaskStatus::IN_PROGRESS] - updated[TaskStatus::TESTING];
		untouched[TaskStatus::TESTING] = p[TaskStatus::TESTING] - updated[TaskStatus::DONE];

		if (p[TaskStatus::DONE]) {
			untouched[TaskStatus::DONE] = p[TaskStatus::DONE] - updated[TaskStatus::DONE];
		}

		p[TaskStatus::NEW] = untouched[TaskStatus::NEW] + updated[TaskStatus::NEW];
		p[TaskStatus::IN_PROGRESS] = untouched[TaskStatus::IN_PROGRESS] + updated[TaskStatus::IN_PROGRESS];
		p[TaskStatus::TESTING] = untouched[TaskStatus::TESTING] + updated[TaskStatus::TESTING];
		p[TaskStatus::DONE] = untouched[TaskStatus::DONE] + updated[TaskStatus::DONE];


		if (untouched[TaskStatus::NEW] == 0) {
			untouched.erase(TaskStatus::NEW);
		}
		if (untouched[TaskStatus::IN_PROGRESS] == 0) {
			untouched.erase(TaskStatus::IN_PROGRESS);
		}
		if (untouched[TaskStatus::TESTING] == 0) {
			untouched.erase(TaskStatus::TESTING);
		}

		untouched.erase(TaskStatus::DONE);
		updated.erase(TaskStatus::NEW);

		if (updated[TaskStatus::IN_PROGRESS] == 0) {
			updated.erase(TaskStatus::IN_PROGRESS);
		}
		if (updated[TaskStatus::TESTING] == 0) {
			updated.erase(TaskStatus::TESTING);
		}
		if (updated[TaskStatus::DONE] == 0) {
			updated.erase(TaskStatus::DONE);
		}

		if ( p[TaskStatus::NEW] == 0) {
			p.erase(TaskStatus::NEW);
		}

		/*
		if ( p[TaskStatus::IN_PROGRESS] == 0) {
			p.erase(TaskStatus::IN_PROGRESS);
		}
		if ( p[TaskStatus::TESTING] == 0) {
			p.erase(TaskStatus::TESTING);
		}
		if ( p[TaskStatus::DONE] == 0) {
			p.erase(TaskStatus::DONE);
		}
		*/

		return tie(updated, untouched);
	}

private:
	map<string, TasksInfo> PersonTasks; // string = person
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
	     ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
	     ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
	     ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
	TeamTasks tasks;
	while(cin) {
		string command, person;
		int num;
		cin >> command >> person;
		if (command == "AddNewTasks") {
			cin >> num;
			while (num--)
				tasks.AddNewTask(person);
			cout << "[]" << endl;
		} else if (command == "PerformPersonTasks") {
			cin >> num;
			TasksInfo updated_tasks, untouched_tasks;
			tie(updated_tasks, untouched_tasks) =
					tasks.PerformPersonTasks(person, num);
			cout << vector<TasksInfo>{updated_tasks, untouched_tasks } << endl;
		} else if (command == "GetPersonTasksInfo") {
			cout << tasks.GetPersonTasksInfo(person) << endl;
		} else if (command.size() && command[0] != '#'){
			throw invalid_argument("wrong command: " + command);
		}
	}
}