#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct TAuthor { // Автор посібника
	string author_name;
	string author_surname;
	string department_name;
};
ostream& operator <<(ostream& out, const TAuthor& author);
istream& operator >>(istream& in, TAuthor& author);

struct TManualGiving { // Видача посібника
	string student;
	string date;
};
ostream& operator <<(ostream& out, const TManualGiving& giveManual);
istream& operator >>(istream& in, TManualGiving& giveManual);

class TManual { // Клас посібника
private:
	TManualGiving* giveManuals;
	string nameManual;
	string subject;
	int n;
	int countManuals;
public:
	TManual();
	TManual(const TManual& obj);
	TManual(const string& nameManual_, const string& subject_, int countManuals_);
	~TManual();
	const string& getNameManual()const;
	const string& getSubject()const;
	int getCountManuals()const;
	void outputManualGive(ostream& out)const;
	void setNameManual(const string& nameMovie_);
	void setSubject(const string& country_);
	void setCountManuals(const int countManuals_);
	bool isExistdGive(string student_, string date_)const;
	bool ManualGive(string student_, string date_);  // Метод видачі
	bool ManualGive(const TManualGiving& giveManual); // посібника
	bool ManualReturn(string student_, string date_); // Метод повернення посібника
	void findStudents()const; // Метод знаходження студента, який отримав посібник декілька раз
	int countGivesDate(string date_); // Метод знаходження числа виданих посібників за вказаною датою
	// Перевантаження операторів
	TManual& operator =(const TManual& obj);
	TManual& operator +=(const TManualGiving& giveManual);
};
ostream& operator <<(ostream& out, const TManual& manual);
istream& operator >>(istream& in, TManual& manual);



int main() {
	time_t  sysdate = time(NULL);
	cout << "Current Datetime:" << asctime(localtime(&sysdate)) << endl;
	TAuthor Author;
	cin >> Author;
	TManual Manual;
	cin >> Manual;
	cout << Author;
	cout << Manual;
	Manual.findStudents();
	cout << "\nPlease enter date: ";
	string date;
	getline(cin, date);
	cout << Manual.countGivesDate(date) << endl;
	string student;
	cout << "\nPlease input name, if you want return manual:\n";
	getline(cin, student);
	cout << "Also input date of giving:\n";
	getline(cin, date);
	bool result = Manual.ManualReturn(student, date);
	if (!result) cout << "Warning: Manual not found " << endl;
	cout << Manual;
	return 0;
}

ostream& operator <<(ostream& out, const TManualGiving& giveManual) {
	out << giveManual.student
		<< "\t" << giveManual.date << endl;
	return out;
}
istream& operator >>(istream& in, TManualGiving& giveManual) {
	cout << "Please input your name: ";
	getline(in, giveManual.student);
	cout << "Please input date: ";
	getline(in, giveManual.date);
	return in;
}

ostream& operator <<(ostream& out, const TAuthor& author)
{
	out << "\nAuthor:\n" << author.author_name
		<< "  " << author.author_surname
		<< "  " << author.department_name << endl;
	return out;
}
istream& operator >>(istream& in, TAuthor& author)
{
	cout << "Manual's author:" << endl;
	cout << "Please input author's name: ";
	getline(in, author.author_name);
	cout << "Please input author's surname: ";
	getline(in, author.author_surname);
	cout << "Please input department name: ";
	getline(in, author.department_name);
	return in;
}

TManual::TManual() {}
TManual::TManual(const TManual& obj)
{
	nameManual = obj.nameManual;
	subject = obj.subject;
	countManuals = obj.countManuals;
	n = obj.n;
	giveManuals = new TManualGiving[n];
	for (int i = 0; i < n; ++i)
	{
		giveManuals[i] = obj.giveManuals[i];
	}

}

TManual::TManual(const string& nameMovie_, const string& subject_, int countManuals_) {}
TManual::~TManual() {
	if (giveManuals) delete[] giveManuals;
	giveManuals = NULL;
	n = 0;
}

const string& TManual::getNameManual()const { return nameManual; }
const string& TManual::getSubject()const { return subject; }
int TManual::getCountManuals()const { return countManuals; };
void TManual::outputManualGive(ostream& out)const
{
	for (int i = 0; i < n; ++i)
		out << giveManuals[i] << endl;
}

void TManual::setNameManual(const string& nameManual_) { nameManual = nameManual_; }
void TManual::setSubject(const string& subject_) { subject = subject_; }
void TManual::setCountManuals(const int countManuals_) { countManuals = countManuals_; };
bool TManual::isExistdGive(string student_, string date_)const
{
	for (int i = 0; i < n; ++i)
	{
		if (giveManuals[i].student == student_ && giveManuals[i].date == date_)
		{
			return true;
		}
	}
	return false;
}

bool TManual::ManualGive(string student_, string date_) // Метод видачі посібника
{
	TManualGiving newGive = { student_, date_ };
	return ManualGive(newGive);
}
bool TManual::ManualGive(const TManualGiving& giveManual) // Метод видачі посібника
{
	if (isExistdGive(giveManual.student, giveManual.date)) return false;
	TManualGiving* arr = new TManualGiving[n + 1];
	for (int i = 0; i < n; ++i)
		arr[i] = giveManuals[i];
	arr[n] = giveManual;
	delete[]giveManuals;
	giveManuals = arr;
	++n;
	return true;
}

void TManual::findStudents()const // Метод знаходження студента, який отримав посібник декілька раз
{
	cout << "Frequent students:" << endl;
	if (n <= 0) cout << "Error";
	vector <string>all;
	int k = 0;
	bool somethingFound = false;
	for (int i = 0; i < n; ++i) {
		k = 1;
		bool isSkipped = false;
		for (auto a : all)
			if (a == giveManuals[i].student) { isSkipped = true; break; }
		if (isSkipped) continue;
		else all.push_back(giveManuals[i].student);
		for (int j = i + 1; j < n; ++j)
		{
			if (giveManuals[i].student == giveManuals[j].student) ++k;
		}
		if (k > 1) { cout << giveManuals[i].student << endl; somethingFound = true; }
	}
	if (somethingFound == false) cout << "Nothing was found!" << endl;
}

int TManual::countGivesDate(string date_) { // метод знаходження числа видач для заданої дати
	int count = 0;
	for (int i = 0; i < n; ++i)
		if (date_ == giveManuals[i].date) ++count;
	cout << "the number of manuals taken " << date_ << " = ";
	return count;
}

bool TManual::ManualReturn(string student_, string date_) // метод повернення посібника
{
	if (!isExistdGive(student_, date_)) return false;
	TManualGiving* arr = new TManualGiving[n - 1];
	int j = 0;
	for (int i = 0; i < n; ++i)
	{
		if (giveManuals[i].student == student_ && giveManuals[i].date == date_)
		{
			continue;
		}
		arr[j++] = giveManuals[i];
	}
	delete[]giveManuals;
	giveManuals = arr;
	--n;
}

TManual& TManual::operator =(const TManual& obj)
{
	if (this == &obj) return (*this);
	this->~TManual();
	nameManual = obj.nameManual;
	subject = obj.subject;
	countManuals = obj.countManuals;
	n = obj.n;
	giveManuals = new TManualGiving[n];
	for (int i = 0; i < n; ++i)
	{
		giveManuals[i] = obj.giveManuals[i];
	}
}
TManual& TManual::operator +=(const TManualGiving& giveManual)
{
	ManualGive(giveManual);
	return(*this);
}



ostream& operator <<(ostream& out, const TManual& manual)
{
	out << "\nManual:\n" << "Name: " << manual.getNameManual()
		<< endl << "Subject: " << manual.getSubject()
		<< endl << "Total manuals = " << manual.getCountManuals() << endl;
	cout << "\nStudents who took manual: " << endl;
	manual.outputManualGive(out);
	return out;
}
istream& operator >>(istream& in, TManual& manual)
{
	cout << "Manual:" << endl;
	string strTmp;
	cout << "Please input name manual: ";
	getline(in, strTmp);
	manual.setNameManual(strTmp);
	cout << "Please input subject manual: ";
	getline(in, strTmp);
	manual.setSubject(strTmp);
	cout << "Please input count manuals: ";
	getline(in, strTmp);
	manual.setCountManuals(atoi(strTmp.c_str()));
	string ansver;
	do
	{
		cout << "Give manual:\n";
		TManualGiving giveManual;
		in >> giveManual;
		manual += giveManual;
		cout << "Do wount continue give manual(y/n):";
		getline(in, ansver);
	} while (ansver.size() != 0 && ansver[0] == 'y');

	return in;
}
