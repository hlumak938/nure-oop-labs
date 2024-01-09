#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "aeroflot.h"
using namespace std;

int countString(istream& in)
{
	int count = 0;
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		if (in && !line.empty()) ++count;
	}
	return count;
}

int main() {
	std::string inputDataStr = "Paris;Boeing;53\nLondon;Airbus;21\nTokyo;Airbus;5";
	std::istringstream inputData(inputDataStr);
	int n = countString(inputData);
	NAero::TAEROFLOT* arr = new NAero::TAEROFLOT[n];
	inputData.seekg(0);
	inputData.clear();
	std::ofstream fin("inputdata.txt");
	fin << inputData.str() << endl;
	fin.close();
	std::ostringstream resultData;
	NAero::input(arr, n, inputData);
	NAero::output(arr, n, resultData);
	NAero::outAero(arr, n, resultData);
	NAero::findAero(arr, n, resultData);
	std::ofstream fout("resultdata.txt");
	cout << resultData.str() << endl;
	fout << resultData.str() << endl;
	fout.close();
	delete[] arr;
	return 0;
}
