#pragma once
#include <algorithm> 
#include <iostream> 
#include <iomanip> 
#include <map> 
#include <set> 
#include <string> 
#include <sstream>

using namespace std;
namespace tools {
	void inputFile(string& text, string& black_words);
	void outputFile(const string& text);
	void processedText(string& text);
	int fillMap(const string& text, const set<string>& black_list, map<char, int>& letters);
	void fillSet(const string& words_string, set<string>& letters); void showSize(const int letters, const int words);
	int findRatio(const string& text, const set<string>& black_list, const map<char, int>& letters);
}
