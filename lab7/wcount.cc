#include <algorithm>
#include <iostream>
#include <string>
#include <ctype.h>
#include <map>

// So we don't have to type "std::" everywhere...
using namespace std;

int c_words = 0;
int number_to_show = 10;

string processWord(string &word);
void processText(map<string, int>& wordCounts);
void outputWordsByCount(map<string, int>& wordCounts);

int main()
{
  map<string, int> wordCounts;

  // Process the text on console-input, using the skip-list.
  processText(wordCounts);

  cout << "Total words in document:  " << c_words << endl;
  cout << "Unique words:  " << wordCounts.size() << endl;

  // Finally, output the word-list and the associated counts.
  outputWordsByCount(wordCounts);

  return 0;
}


/*
 * This helper-function converts a word to all lower-case, and then removes
 * any leading and/or trailing punctuation.
 *
 * Parameters:
 *   word    The word to process.  It is passed by-value so that it can be
 *           manipulated within the function without affecting the caller.
 *
 * Return value:
 *   The word after all leading and trailing punctuation have been removed.
 *   Of course, if the word is entirely punctuation (e.g. "--") then the result
 *   may be an empty string object (containing "").
 */
string processWord(string &word)
{
  	string str = "";

	char c;
	bool abc = false;

	for(int i=0 ; i < word.length() ; ++i) 
	{
		c = word[i];

    		if(isalpha(c))
		{
			if(!abc ) abc = true;

			if(isupper(c)) str.push_back((char)tolower(c));
			else str.push_back(c);
		}
		else if (abc && c == '\'')
		{
			if((i + 1) == word.length()) break;

			if(isalpha(word[i + 1])) str.push_back(c);
			else break;
		}
	}

	/*
	// remove punctuation marks
	str.erase( remove_if (str.begin(),str.end(), static_cast<int(*)(int)>(&ispunct)), str.end());

	// convert to lowercase
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	*/
	
	return (word = str);
}


void processText(map<string, int>& wordCounts)
{
	string word;

	// Read input until there is no more!
	while (cin >> word)
	{
		string str = processWord(word);
		if (str.length() > 0){
			++wordCounts[str];
			++c_words;
		}
	}
}


/*
 * This helper-function outputs the generated word-list in descending order
 * of count.  The function uses an STL associative container to sort the words
 * by how many times they appear.  Because multiple words can have the same
 * counts, a multimap is used.
 */
void outputWordsByCount(map<string, int>& wordCounts)
{
  multimap<int, string, greater<int> > sortByCount;
  map<string, int>::const_iterator wIter;

  for (wIter = wordCounts.begin(); wIter != wordCounts.end(); wIter++)
    	sortByCount.insert(pair<int, string>(wIter->second, wIter->first));

  multimap<int, string>::const_iterator cIter;
  for (cIter = sortByCount.begin(); cIter != sortByCount.end(); cIter++)
  {
    	if(--number_to_show < 0) break;

    	cout << cIter->second << "\t" << cIter->first << endl;
  }
}




