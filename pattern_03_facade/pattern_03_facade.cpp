/*
*Завдання 3. Фасад
Створити програму-перекладач для роботи зі словником, що дозволяє перекладати тексти з однієї мови на іншу. Створити набір класів:
o	Слово (комбінація слово-переклад),
o	Колекція Слів (список слів та методи обробки списку, індексатор – по слову повертає переклад),
o	Перекладач (працює з колекцією  слів, виводить переклад на екран(чи повертає), дозволяє змінити колекцію слів),
o	Запис (записує колекцію слів в файл, зчитує з файлу),
o	Фасад (інкапсулює в собі всі об’єкти класів програми, надає методи для виклику користувачем з main() - функції).

*/


#include "stdafx.h"
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct WordTranslate
{
	string eng;
	string ukr;
};

class Word
{
private:
	WordTranslate word;

public:

	Word()
	{}

	void setEng(string wordEng)
	{
		word.eng = wordEng;
	}

	void setUkr(string wordUkr)
	{
		word.ukr = wordUkr;
	}

	string getEng()
	{
		return word.eng;
	}

	string getUkr()
	{
		return word.ukr;
	}
};

class CollectionWords
{
private:
	vector<Word> dictionary;

public:

	void translate(string word)
	{/*
		WordTranslate tmp;
		tmp.eng = word;
		tmp.ukr = "";
		if (find(dictionary.begin(), dictionary.end(), tmp) != dictionary.end()) 
			cout << "find" << endl;
		else 
			cout << "don't find\n";
			*/
	}

	void addWord()
	{
		string eng, ukr;
		cout << "\nAdding word in vocabulary\nEnter English word: ";
		cin >> eng;
		cout << "Enter Ukrainian translation: ";
		cin >> ukr;
		Word tmp;
		tmp.setEng(eng);
		tmp.setUkr(ukr);
		dictionary.push_back(tmp);
	}

	void addWord(string eng, string ukr)
	{
		Word tmp;
		tmp.setEng(eng);
		tmp.setUkr(ukr);
		dictionary.push_back(tmp);
	}

	int getSize() const
	{
		return dictionary.size();
	}

	Word getValue(int index) const
	{
		return dictionary[index];
	}
};

class Translator
{
private: 
	
public:

	void showVocabulary(CollectionWords dictionary)
	{
		for (int i = 0; i < dictionary.getSize(); ++i)
			cout << dictionary.getValue(i).getEng() << " - \t" << dictionary.getValue(i).getUkr() << endl;
		cout << endl;
	}
};

class Record
{
public:


	// завантажити словник
	void loadFile(string nameFile, CollectionWords dictionary)
	{
		int even = 0;
		string str;
		ifstream fin(nameFile, ios::app);

		if (!fin)
		{
			cout << "Error opening file\n";
			system("pause");
		}

		cout << "\nEng\t - Ukr\n------------------\n";
		while (getline(fin, str))
		{
			if (even % 2 == 0)
				cout << str;
			else
			{
				cout << "\t - " << str << endl;
			}
			++even;
		}

		fin.close();
	}


	// запис словника
	void saveFile(string nameFile, CollectionWords dictionary)
	{
		fstream add(nameFile, ios::app | ios::in);
		if (!add)
			cout << "Error opening file\n";

			for (int i = 0; i < dictionary.getSize(); ++i)
				add << endl << dictionary.getValue(i).getEng() << endl << dictionary.getValue(i).getUkr();

		add.close();
	}

};

class Facade
{
	
};

int main()
{
	setlocale(LC_ALL, ".1251");
	CollectionWords cw;
	cw.addWord("Cat", "кiт");
	cw.addWord("Car", "авто");
	cw.addWord();
	Translator tr;
	tr.showVocabulary(cw);
	cw.translate("Cat");
	Record r;
	r.saveFile("vocabulary.txt", cw);


	cout << endl;
	system("pause");
	return 0;
}