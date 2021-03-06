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



class Word
{
private:
	struct WordTranslate
	{
		string eng;
		string ukr;
	} word;

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

	string getEng() const
	{
		return word.eng;
	}

	string getUkr() const
	{
		return word.ukr;
	}

	friend class Record;
};

class CollectionWords
{
private:
	vector<Word> dictionary;

public:

	//перекласти слово
	void translate()
	{
		string word;
		cout << "\nEnter word for translate: ";
		cin >> word;
		auto it = find_if(begin(dictionary), end(dictionary), [=](Word const& f)
		{
			if (f.getEng() == word)
				cout << f.getEng() << " -\t" << f.getUkr() << endl;
			return (f.getEng() == word);
		});

		if (it == end(dictionary))
			cout << "Word " << word << " not found!\n";
	}

	//редагувати слово
	void editWord()
	{
		string wordEng;
		cout << "\nEnter word for translate: ";
		cin >> wordEng;
		auto it = find_if(begin(dictionary), end(dictionary), [=](Word const& f)
		{
			return f.getEng() == wordEng;
		});

		if (it != end(dictionary))
		{
			string newTranslate;
			cout << "Write new translate for word \"" << wordEng << "\": ";
			cin >> newTranslate;
			delWord(wordEng);
			addWord(wordEng, newTranslate);
			cout << wordEng << " -\t" << newTranslate << endl;
		}
		else
			cout << "Word \"" << wordEng << "\" not found!\n";
	}

	//видалити слово
	void delWord()
	{
		string word;
		cout << "\nEnter word for delete: ";
		cin >> word;
		delWord(word);

	}

	void delWord(string word)
	{
		auto pred = [word](const Word & item)
		{
			return item.getEng() == word;
		};
		auto it = remove_if(begin(dictionary), end(dictionary), pred) != end(dictionary);
		if (!it)
			cout << "Word " << word << " not found!\n";
	}

	void addWord()
	{
		string eng, ukr;
		cout << "\nAdding word in vocabulary\nEnter English word: ";
		cin >> eng;
		cout << "Enter Ukrainian translation: ";
		cin >> ukr;
		addWord(eng, ukr);

	}

	void addWord(string eng, string ukr)
	{
		Word tmp;
		tmp.setEng(eng);
		tmp.setUkr(ukr);
		addWord(tmp);
	}

	//додати слово 
	void addWord(Word word)
	{
		dictionary.push_back(word);
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

	//показати увесь словник
	void showVocabulary(CollectionWords dictionary)
	{
		for (int i = 0; i < dictionary.getSize(); ++i)
			cout << dictionary.getValue(i).getEng() << " - " << dictionary.getValue(i).getUkr() << endl;
		cout << endl;
	}
};

class Record
{
public:

	// завантажити словник з файлу
	void loadFile(string nameFile, CollectionWords & dictionary)
	{
		fstream file(nameFile, ios::in);
		if (!file)
			cout << "Error opening file\n";
		else
		{
			Word reads;
			while (!file.eof())
			{
				file >> reads.word.eng >> reads.word.ukr;
				if (file)
				{
					dictionary.addWord(reads);
				}
				else
					break;
			}
		}
		file.close();
	}


	// запис словника у файл
	void saveFile(string nameFile, CollectionWords dictionary)
	{
		ofstream file;
		file.open(nameFile);
		if (!file)
			cout << "Error opening file\n";
		else
		{
			for (int i = 0; i < dictionary.getSize(); ++i)
				file << dictionary.getValue(i).getEng() << " " << dictionary.getValue(i).getUkr() << endl;
			file.close();
		}
	}

};

class Facade
{
public:

	int run()
	{
		Record r;
		CollectionWords cw;
		Translator tr;

		r.loadFile("vocabulary.txt", cw);

		for (;;) {
			switch (menu())
			{
			case 1:
				tr.showVocabulary(cw);
				break;
			case 2:
				cw.translate();
				break;
			case 3:
				cw.addWord();
				break;
			case 4:
				cw.editWord();
				break;
			case 5:
				cw.delWord();
				break;
			case 0:
				r.saveFile("vocabulary.txt", cw);
				return 0;
				break;
			default:
				cout << "Wrong choose\n";
				break;
			}
		}
	}

	int menu() const
	{
		int item;
		cout << "\n-----------------=  Menu  =-------------------\n";
		cout << "(1) Show all dictionary\t(2) Translate\n";
		cout << "(3) Add word\t\t(4) Edit Word\n";
		cout << "(5) Delete word\t\t(0) Exit";
		cout << "\n----------------------------------------------\n";
		cout << "\nEnter number of item: ";
		cin >> item;

		return item;
	}
};

int main()
{
	setlocale(LC_ALL, ".1251");
	Facade f;
	f.run();

	return 0;
}