#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct TManualGiving { // Видача посібника
	string student;
	string date;
};
ostream& operator <<(ostream& out, const TManualGiving& giveManual);
istream& operator >>(istream& in, TManualGiving& giveManual);

class TManual { // Клас посібника
private:
	vector <TManualGiving> giveManuals;
	string nameManual;
	string subject;
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
	void setGivings(const vector<TManualGiving>& giveManuals_) { giveManuals = giveManuals_; };
	vector<TManualGiving>::const_iterator findStudent(string student_, string date_)const;
	bool ManualGive(string student_, string date_);  // Метод видачі
	bool ManualGive(const TManualGiving& giveManual); // посібника
	const vector<TManualGiving>& getStudents() const { return giveManuals; };
	bool ManualReturn(string student_, string date_); // Метод повернення посібника
	void findStudents()const; // Метод знаходження студента, який отримав посібник декілька раз
	int countGivesDate(string date_); // Метод знаходження числа виданих посібників за вказаною датою
	// Перевантаження операторів
	TManual& operator =(const TManual& obj);
	TManual& operator +=(const TManualGiving& giveManual);
	bool operator <(const TManual& arg2) const;
	operator int()const;

};
ostream& operator <<(ostream& out, const TManual& manual);
istream& operator >>(istream& in, TManual& manual);

bool cmpByManualsCount(const TManual& a, const TManual& b)
{
	return a.getCountManuals() < b.getCountManuals();
}


bool greater_4(const TManual& a)
{
	return a.getCountManuals() > 4;
}
const vector<TManualGiving>& getStudents(const TManual& m)
{
	return m.getStudents();
}
class ClistStudents
{
	vector<TManualGiving>& listStudents;
public:
	ClistStudents(vector<TManualGiving>& x) :listStudents(x) {};
	void operator ()(const TManual& y)
	{
		copy(y.getStudents().begin(), y.getStudents().end(), back_inserter(listStudents));
	}
};
const string& getStudentName(const TManualGiving& a) { return a.student; }
int averageCounts(int res, const TManual& m)
{
	res += m.getCountManuals();
	return res;
}
bool cmpManualByName(const TManual& a, const TManual& b)
{
	return a.getNameManual() == b.getNameManual();
}

int main() {
	ifstream fin("manuals.txt");
	if (!fin)
	{
		cerr << "File not found" << endl;
		system("pause");
		return 0;
	}
	// 1. забезпечити для контейнера можливість зчитування з файлу і запису в файл з використанням ітераторів потоків.
	vector<TManual> manuals;
	copy(istream_iterator<TManual>(fin), istream_iterator<TManual>(), back_inserter(manuals));
	cout << "Task 1: \n";
	copy(manuals.begin(), manuals.end(), ostream_iterator<TManual>(cout, "\n"));
	ofstream fout("result.txt");
	copy(manuals.begin(), manuals.end(), ostream_iterator<TManual>(fout, "\n"));
	// 2. забезпечити для контейнера сортування за числом видач
	cout << "Task 2: \n";
	cout << "Sort by count of manuals: \n";
	std::sort(manuals.begin(), manuals.end(), cmpByManualsCount);
	copy(manuals.begin(), manuals.end(), ostream_iterator<TManual>(cout, "\n"));
	//3. винести в окремий вектор всі посібники, починаючи з посібника з числом видач більше 4
	cout << "Task 3: \n";
	vector<TManual>::iterator it;
	it = find_if(manuals.begin(), manuals.end(), greater_4);
	vector<TManual> manuals_greater_4;
	copy(it, manuals.end(), back_inserter(manuals_greater_4));
	copy(manuals_greater_4.begin(), manuals_greater_4.end(), ostream_iterator<TManual>(cout, "\n"));
	//4. зберегти всі імена студентів з вектора з кроку 3 в новому векторі.
	cout << "Task 4: \n";
	vector<TManualGiving> students;
	for_each(manuals_greater_4.begin(), manuals_greater_4.end(), ClistStudents(students));
	vector<string> studentsNames;
	transform(students.begin(), students.end(), back_inserter(studentsNames), getStudentName);
	copy(studentsNames.begin(), studentsNames.end(),
		ostream_iterator<string>(cout, "\n"));
	//5. Визначити число студентів з іменами, які йдуть в алфавітному порядку за заданим в векторі, отриманому на кроці 4.
	cout << "\nTask 5: \n";
	cout << "Number of students in alphabetical order";
	int count = 0;
	string prev = studentsNames[0];
	count = count_if(studentsNames.begin() + 1, studentsNames.end(), [&](const string& a) { if (a.compare(prev) <= 0) return false; else { prev = a;  return true; } });
	cout << " = " << count << endl;
	//6. знайти середнє число видач за всіма посібниками з використанням accumulate ()
	cout << "\nTask 6: \n";
	int avarageCounts = accumulate(manuals.begin(), manuals.end(), 0, averageCounts);
	avarageCounts /= manuals.size();
	cout << "averageCounts of manuals  = " << avarageCounts << endl;
	//7. перевірити, чи входить вектор, отриманий на кроці 3, в вихідний вектор як підпослідовність.
	cout << "\nTask 7: \n";
	vector<TManual>::iterator itsub;
	itsub = search(manuals.begin(), manuals.end(), manuals_greater_4.begin(), manuals_greater_4.end(), cmpManualByName);
	if (itsub != manuals.end())
	{
		cout << "sub vector found: \n";
		copy(itsub, manuals.end(), ostream_iterator<TManual>(cout, "\n"));
	}
	system("pause");
	return 0;
}

ostream& operator <<(ostream& out, const TManualGiving& giveManual) {
	out << giveManual.student
		<< "\t" << giveManual.date << endl;
	return out;
}
istream& operator >>(istream& in, TManualGiving& giveManual) {
	getline(in, giveManual.student, ':');
	getline(in, giveManual.date, ':');
	return in;
}

TManual::TManual() : nameManual("C++"), subject("OOP"), countManuals(0) {}
TManual::TManual(const TManual& obj)
{
	nameManual = obj.nameManual;
	subject = obj.subject;
	countManuals = obj.countManuals;
	giveManuals = obj.giveManuals;
}

TManual::TManual(const string& nameManual_, const string& subject_, int countManuals_) : nameManual(nameManual_), subject(subject_), countManuals(countManuals_) {}
TManual::~TManual() { giveManuals.clear(); }

const string& TManual::getNameManual()const { return nameManual; }
const string& TManual::getSubject()const { return subject; }
int TManual::getCountManuals()const { return countManuals; };
void TManual::outputManualGive(ostream& out)const
{
	copy(giveManuals.begin(), giveManuals.end(), ostream_iterator<TManualGiving>(out, " "));
}

void TManual::setNameManual(const string& nameManual_) { nameManual = nameManual_; }
void TManual::setSubject(const string& subject_) { subject = subject_; }
void TManual::setCountManuals(const int countManuals_) { countManuals = countManuals_; };

bool operator ==  (const TManualGiving& a, const TManualGiving& b)
{
	return (a.student == b.student && a.date == b.date);
}


vector<TManualGiving>::const_iterator TManual::findStudent(string student_, string date_)const
{
	TManualGiving giveManual = { student_, date_ };
	vector<TManualGiving>::const_iterator result = find(giveManuals.begin(), giveManuals.end(), giveManual);
	return result;
}


bool TManual::ManualGive(string student_, string date_) // Метод видачі посібника
{
	TManualGiving newGive = { student_, date_ };
	return ManualGive(newGive);
}
bool TManual::ManualGive(const TManualGiving& giveManual) // Метод видачі посібника
{
	if (find(giveManuals.begin(), giveManuals.end(), giveManual) != giveManuals.end()) return false;
	giveManuals.push_back(giveManual);
	return true;
}

void TManual::findStudents()const // Метод знаходження студента, який отримав посібник декілька раз
{
	cout << "Frequent students:" << endl;
	if (giveManuals.size() <= 0) cout << "Error";
	vector <string>all;
	int k = 0;
	bool somethingFound = false;
	for (int i = 0; i < giveManuals.size(); ++i) {
		k = 1;
		bool isSkipped = false;
		for (auto a : all)
			if (a == giveManuals[i].student) { isSkipped = true; break; }
		if (isSkipped) continue;
		else all.push_back(giveManuals[i].student);
		for (int j = i + 1; j < giveManuals.size(); ++j)
		{
			if (giveManuals[i].student == giveManuals[j].student) ++k;
		}
		if (k > 1) { cout << giveManuals[i].student << endl; somethingFound = true; }
	}
	if (somethingFound == false) cout << "Nothing was found!" << endl;
}

int TManual::countGivesDate(string date_) { // метод знаходження числа видач для заданої дати
	int count = 0;
	for (int i = 0; i < giveManuals.size(); ++i)
		if (date_ == giveManuals[i].date) ++count;
	cout << "the number of manuals taken " << date_ << " = ";
	return count;
}

bool TManual::ManualReturn(string student_, string date_) // метод повернення посібника
{
	vector<TManualGiving>::const_iterator it = findStudent(student_, date_);
	if (it == giveManuals.end()) return false;
	giveManuals.erase(it);
	return true;
}

TManual& TManual::operator =(const TManual& obj)
{
	if (this == &obj) return (*this);
	this->~TManual();
	nameManual = obj.nameManual;
	subject = obj.subject;
	countManuals = obj.countManuals;
	giveManuals = obj.giveManuals;

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
	out << "\nStudents who took manual: " << endl;
	manual.outputManualGive(out);
	return out;
}
istream& operator >>(istream& in, TManual& manual)
{
	string strTmp;
	getline(in, strTmp, '$');
	manual.setNameManual(strTmp);
	getline(in, strTmp, '$');
	manual.setSubject(strTmp);
	getline(in, strTmp, '$');
	manual.setCountManuals(atoi(strTmp.c_str()));
	getline(in, strTmp, '$');
	stringstream streamGivings(strTmp);
	vector<TManualGiving> givings;
	copy(istream_iterator<TManualGiving>(streamGivings), istream_iterator<TManualGiving>(), back_inserter(givings));
	manual.setGivings(givings);
	return in;
}