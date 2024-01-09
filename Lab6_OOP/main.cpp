#include "Header.h"

int main()
{
	string text = "", black_words = "";
	tools::inputFile(text, black_words);
	tools::processedText(text);
	set<string> s_exclude;
	tools::fillSet(black_words, s_exclude);
	map<char, int> letters;
	int words_count = tools::fillMap(text, s_exclude, letters);
	int letters_count = tools::findRatio(text, s_exclude, letters);
	tools::showSize(letters_count, words_count);
	return 0;
}
