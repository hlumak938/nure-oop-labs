#include "aeroflot.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

namespace NAero {
	// власні маніпулятори
	ostream& manipStr(ostream& out)
	{
		out << " ";
		return out;
	}
	ostream& manipInt(ostream& out)
	{
		out << "Flight#";
		return out;
	}
	// перевантаження потоків
	ostream& operator<<(ostream& out, const TAEROFLOT& aero)
	{
		out << manipStr << aero.name
			<< manipStr << aero.type;
		out << manipInt << aero.number;
		return out;
	}
	istream& operator>>(istream& in, TAEROFLOT& aero)
	{
		getline(in, aero.name, ';');
		getline(in, aero.type, ';');
		std::string numberstr;
		getline(in, numberstr);
		std::stringstream numberstream(numberstr);
		std::string tmp;
		numberstream >> tmp;
		aero.number = atoi(tmp.c_str());
		return in;
	}
	// головні функції обробки данних
	void input(TAEROFLOT* gr, int n, std::istream& in) //введення з потоку
	{
		char i = 0;
		while (i < n && !in.eof())
			in >> gr[i++];
		for (char k = 0; k < n - 1; ++k)
			for (char i = 0; i < n - 1 - k; ++i)
				if (gr[i].name > gr[i + 1].name)
					swap(gr[i], gr[i + 1]);
	}
	void output(const TAEROFLOT* gr, int n, std::ostream& out) //виведення у потік
	{
		out << "All flights:" << endl;
		for (char i = 0; i < n; ++i)
			out << gr[i] << endl;
		out << endl;
	}
	void outAero(const TAEROFLOT* gr, int n, std::ostream& out)
	{
		std::string tmp;
		cout << "Enter the type of airplane for which you want to find a flight" << endl;
		getline(std::cin, tmp);
		bool isFound = false;
		out << "All flights on request " << tmp << ":" << endl;
		for (char i = 0; i < n; ++i)
		{
			if (gr[i].type == tmp) {
				isFound = true;
				out << gr[i] << endl;
			}
		}
		if (isFound == false)
			out << "There are no such flights." << endl;
		out << endl;
	}
	void findAero(TAEROFLOT* gr, int n, std::ostream& out)
	{
		std::string tmp;
		cout << "Enter a letter by which you want to find a flight" << endl;
		getline(std::cin, tmp);
		bool isFound = false;
		out << "Flights starting with a letter " << tmp << ":" << endl;
		for (int i = 0; i < n; ++i) {
			if (gr[i].name.find(tmp) == 0) {
				out << gr[i] << endl;
				isFound = true;
			}
		}
		if (isFound == false) {
			out << "There are no such flights.\n";
		}
	}
}
