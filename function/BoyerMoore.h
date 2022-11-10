#pragma once
#ifndef BOYERMOORE_H
#define BOYERMOORE_H
#include <iostream>
#define NO_OF_CHARS 256

void badCharHeuristic(std::string str, int size, int badchar[NO_OF_CHARS])
{
	int i;
	for (i = 0; i < NO_OF_CHARS; i++) { badchar[i] = -1; }
	for (i = 0; i < size; i++) { badchar[(int) str[i]] = i; }
}

void searchBoyerMoore(std::string txt, std::string pat)
{
	int m = pat.size();
	int n = txt.size();
	int badchar[NO_OF_CHARS];

	badCharHeuristic(pat, m, badchar);
	int s = 0;
	while (s <= (n - m))
	{
		int j = m - 1;
		while (j >= 0 && pat[j] == txt[s + j]) { j--; }
		if (j < 0)
		{
			std::cout << "position = " << s << std::endl;
			s += (s + m < n)? m-badchar[txt[s + m]] : 1;
		}
		else { s += std::max(1, j - badchar[txt[s + j]]); }
	}
}

bool boolBoyerMoore(std::string txt, std::string pat)
{
	int m = pat.size();
	int n = txt.size();
	int badchar[NO_OF_CHARS];

	badCharHeuristic(pat, m, badchar);
	int s = 0;
	while (s <= (n - m))
	{
		int j = m - 1;
		while (j >= 0 && pat[j] == txt[s + j]) { j--; }
		if (j < 0) { return true; }
		else { s += std::max(1, j - badchar[txt[s + j]]); }
	}
	return false;
}

#endif