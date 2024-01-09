#include "header.h"

void tools::inputFile(string& text, string& black_words)
{
	ifstream in("input.bin", ios::binary | ios::out);
	getline(in, text);
	getline(in, black_words);
	cout << "Text: " << text << '\n';
	cout << "Black list: " << black_words << '\n';
}

void tools::processedText(string& text)
{
	text.erase(remove_if(text.begin(), text.end(), [](auto& a) { return string(",.!()").find(a) != string::npos; }), text.end());
}

int tools::fillMap(const string& text, const set<string>& black_list, map<char, int>& letters)
{
	int words_count = 0; stringstream words(text);
	ofstream out("output.bin", ios::binary | ios::out); while (!words.eof()) {
		string tmp; words >> tmp;
		if (!tmp.empty()) {
			if (black_list.count(tmp) == 0) {
				for (string::const_iterator it = tmp.begin(); it != tmp.end(); ++it) {
					if (*it != ' ')
						letters[*it]++;
				}
				words_count++;
			}
			else {
				cout << "Word from black list was found! Word: " << tmp <<
					'\n';
				out << "Word from black list was found! Word: " << tmp <<
					'\n';
			}
		}
	}
	out.close();
	return words_count;
}

void tools::fillSet(const string& words_string, set<string>& letters)
{
	stringstream words(words_string);
	while (!words.eof()) {
		string tmp;
		words >> tmp;
		if (!tmp.empty())
			letters.insert(tmp);
	}
}

void tools::showSize(const int letters, const int words)
{
	cout << "Text has " << letters << " count of letters and "
		<< words << " count of words\n";
	ofstream out("output.bin", ios::binary | ios::app);
	out << "Text has " << letters << " count of letters and "
		<< words << " count of words\n"; out.close();
}

int tools::findRatio(const string& text, const set<string>& black_list, const map<char, int>& letters)
{
	cout.setf(ios::fixed); cout.unsetf(ios::scientific); cout.precision(4);
	int letters_count = 0, words_count = 0;
	ofstream out("output.bin", ios::binary | ios::app); out.setf(ios::fixed);
	out.unsetf(ios::scientific); out.precision(4);
	for (map<char, int>::const_iterator it = letters.begin(); it != letters.end(); ++it) {
		letters_count += it->second;
	}
	cout << endl;
	stringstream words(text);
	while (!words.eof()) {
		string tmp; words >> tmp;
		if (!tmp.empty()) {
			if (black_list.count(tmp) == 0) {
				words_count++;
				cout << "Word: " << tmp << " -> " << tmp.size() << "\n";
				out << "Word: " << tmp << " -> " << tmp.size() << "\n";
			}
		}
	}
	cout << endl;
	double avgSizeWords = letters_count / words_count;
	double Ratio = 1;
	stringstream words1(text);
	while (!words1.eof()) {
		string tmp; words1 >> tmp;
		if (!tmp.empty()) {
			if (black_list.count(tmp) == 0) {
				Ratio = tmp.size() / avgSizeWords;
				// Відношення довжини кожного слова до середньої довжині слів тексту
				cout << "Ratio = " << Ratio << "\n";
				out << "Ratio = " << Ratio << "\n";
			}
		}
	}
	out.close();
	return letters_count;
}
