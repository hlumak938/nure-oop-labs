#pragma once
#ifndef _AEROFLOT_H_
#define _AEROFLOT_H_
#include <string>

namespace NAero {
	// ��������� AEROFLOT
	struct TAEROFLOT {
		std::string name;
		std::string type;
		int number;
	};
	// �������������� ������
	std::ostream& operator<<(std::ostream& out, const TAEROFLOT& Aero);
	std::istream& operator>>(std::istream& in, TAEROFLOT& Aero);
	// �����������
	std::ostream& manipStr(std::ostream& out);
	std::ostream& manipInt(std::ostream& out);
	// �������
	void input(TAEROFLOT* gr, int n, std::istream& in);
	void output(const TAEROFLOT* gr, int n, std::ostream& out);
	void outAero(const TAEROFLOT* gr, int n, std::ostream& out);
	void findAero(TAEROFLOT* gr, int n, std::ostream& out);
}

#endif 
