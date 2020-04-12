
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


void SendSms(const string& number, const string& message);
void SendEmail(const string& email, const string& message);

class INotifier {
public:
	INotifier (const string& adress) : adress_(adress) {}

	virtual void Notify(const string& message) = 0;

protected:
	const string adress_;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier (const string& number) : INotifier(number) {}
	virtual void Notify(const string& message) override {
		SendSms(adress_, message);
	}
};
class EmailNotifier : public INotifier {
public:
	EmailNotifier (const string& mail) : INotifier(mail) {}
	void Notify(const string& message) override {
		SendEmail(adress_, message);
	}
};
void SendSms(const string& number, const string& message) {
	cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
	cout << "Send '" << message << "' to e-mail "  << email << endl;
}

void Notify(INotifier& notifier, const string& message) {
	notifier.Notify(message);
}


int main() {
	SmsNotifier sms{"+7-495-777-77-77"};
	EmailNotifier email{"na-derevnyu@dedushke.ru"};

	Notify(sms, "I have White belt in C++");
	Notify(email, "And want a Yellow one");
	return 0;
}
