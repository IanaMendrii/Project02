#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<vector>
#include<iomanip>

using namespace std;
class BookList;
class FWFile;
class PrintMenu;

 
class BookList

{
protected:

public:
	string Author;
	string Name;
	int Year;
	int NumOfCopy;
	void SetAuthor(string _Author)
	{
		Author = _Author;
	}
	void SetName(string _Name)
	{
		Name = _Name;
	}
	void SetYear(int _Year)
	{
		Year = _Year;
	}
	void SetNumOfCopy(int _NumOfCopy)
	{
		NumOfCopy = _NumOfCopy;
	}
	string GetName()const
	{
		return Name;
	}
	string GetAuthor()const
	{
		return Author;
	}
	void ShowHead()
	{
		cout << "Book catalog" << endl;
		cout << "|" << setw(20) << "Author" << "|" << setw(30) << "Name" << "|" << setw(6) << "Year" << "|" << setw(9) << "N Copy" << "|" << endl;
		cout << "_____________________________________________________________________________________" << endl;

	}
		void Print()
	{
		cout << "|" << setw(20) << Author << "|" << setw(30) << Name << "|" << setw(6) << Year << "|" << setw(9) << NumOfCopy << "|" << endl;
	}
	void ExtractFromString(string &line)
	{
		istringstream iss(line);
		string token;
		int i = 0;
		while (getline(iss, token, ';')) {
			if (i == 0) Author=token;
			if (i == 1) Name=token;
			if (i == 2) Year=atoi(token.c_str());//������� string � int;
			if (i == 3) NumOfCopy=atoi(token.c_str());//������� string � int
			i++;
		}
	}
	string GetString()
	{
		string line;
		return line = Author + "; " + Name + "; "+to_string(Year) + "; " + to_string(NumOfCopy) + "; ";
	}

};
class PrintMenu
{
public:
	int GetValue(int i1, int i2)// Checing int cin
	{
		int answer;
		while (true)
		{
			cin >> answer;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Incorrect value. Try again" << endl;
				cout << "Correct range " << i1 << "-" << i2 << endl;
			}
			else
			{
				if (answer < i1 || answer > i2)
					cout << "Incorrect value. Try again" << endl;
				//cout << "Correct range " << i1 << "-" << i2 << endl;
				if (answer >= i1 && answer <= i2)
					return answer;
			}
		}
	}

	
	int PrintMainMenu()
	{
		int key;
		cout << "What are you going to do?" << endl;
		cout << "1. Add new records" << endl;
		cout << "2. Show records" << endl;
		cout << "3. Modify records" << endl;
		cout << "4. Delete records" << endl;
		cout << "or Press 0 to exit" << endl;
		key = GetValue(0, 4);
		return key;

	}
	void AddMenu(BookList &Book)
	{
		string line; int num;
		cin.clear();
		cin.ignore(32767, '\n');
		cout << " Enter Book Author: "; getline(cin, line); Book.SetAuthor(line);
		cout << " Enter Name of book: "; getline(cin, line); Book.SetName(line);
		cout << " Enter Year of Publication: ";  num = GetValue(1900, 2050); Book.SetYear(num);
		cout << " Enter Avaliable number of copy: "; num = GetValue(0, 50); Book.SetNumOfCopy(num);
		Book.Print();
	}
	void ModifyMenu(BookList &Book)
	{
		string line; int num; int key;
		cout << "What are you going to modify (Press 1 -to change or 0 - to no change)" << endl;
		cout << " Author? (0/1)  ";  key = GetValue(0, 1);
		cin.clear();
		cin.ignore(32767, '\n');
		if (key == 1) { cout << " Enter Book Author:  "; getline(cin, line); Book.SetAuthor(line); }
		cout << " Name of Book? (0/1)  "; key = GetValue(0, 1);
		cin.ignore(32767, '\n');
		if (key == 1) { cout << " Enter Name of book:  "; getline(cin, line); Book.SetName(line); }
		cout << "Year of Publication? (0/1) ";  key = GetValue(0, 1);
		if (key == 1){ cout << " Enter Year of Publication:"; num = GetValue(1900, 2050); Book.SetYear(num); }
		cout << "Avaliable number of copy? (0/1) "; key = GetValue(0, 1);
		if (key == 1) { cout << " Enter Avaliable number of copy:"; num = GetValue(0, 50); Book.SetNumOfCopy(num); }
		Book.Print();
	}
		
};

class RWFile
{
public:
	BookList Book;
	PrintMenu Menu;
	void AddToFile()
	{
		string line;
		Menu.AddMenu(Book);
		fstream file("BookCatalog.txt", ios::app);
		line = Book.GetString();
		file << line<<endl;
		file.close();
	}
	void ShowFromFile()
	{
		fstream file("BookCatalog.txt", ios::in);
		string line;
		    Book.ShowHead();
			while (getline(file, line))
			{
				Book.ExtractFromString(line);
				Book.Print();
			}
		file.close();
	}
	void ModDelRecords(bool Del)
	{
		fstream fileIn("BookCatalog.txt", ios::in);
		fstream fileTemp("Temp.txt", ios::out);
		fstream fileBuff("Buff.txt", ios::out);
		string line;
		string str1;
		string find;
		string text;
		Del ? text = "deleting" : text = "modifying";
		GetParamFind(str1, find, text);
		int nn = 0;
		int nnd;
		string::size_type n;
		while (getline(fileIn, line))
		{
			Book.ExtractFromString(line);
			find == "Name" ? n =Book.GetName().find(str1) : n = Book.GetAuthor().find(str1);
			if (n == string::npos)
				fileTemp << line << endl;
			else
			{
				nn++;
				cout << nn;
				Book.Print();
				fileBuff << line << endl;
			}

		}
		fileIn.close();
		fileBuff.close();
		    if (nn > 0) {
			if (nn > 1)
			{
				cout << "More then one records for "<<text << " are found" << endl;
				cout << "Input the number of records for " << text << " or 0 - to leave all records " << endl;
			}
			if (nn == 1) cout << "One string is found. " << (Del ?  "Delete" : "Modify") << " string? (0-no,1-yes)" << endl;
			cin >> nnd;
			fstream fileBuff("Buff.txt", ios::in);
			for (int i = 0; i < nn; i++)
			{
				getline(fileBuff, line);
				if (i != (nnd - 1)) fileTemp << line << endl;
				else
				if (!Del){
					Book.ExtractFromString(line);
					Menu.ModifyMenu(Book);
					line = Book.GetString();
					fileTemp << line<< endl;
				}
				}

		}
		if (nn == 0)
		{
			cout << "No records for " << text << " is found" << endl;
		}
		fileBuff.close();
		fileTemp.close();
		std::remove("Buff.txt");
		std::remove("BookCatalog.txt");
		std::rename("Temp.txt", "BookCatalog.txt");
	}
	
	void GetParamFind(string &str1, string &find, string&text)
	{
		cout << "How to find record? Press (N) to find by Name of book or (A) to find by Author." << endl;
		bool key=true;
		while(key)
		{
			
			cin >> find;
		if (find == "N" || find == "A")
		{
			find == "N" ? find += "ame" : find += "uther";
			cout << "Input " << find << " of book for " << text << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			getline(cin , str1);
			key = false;
		}
		else
		{
			cout << "Input N or A\t";
			}
	    }
}
	

};


int main()
{
	RWFile File;
	PrintMenu Menu;
	int key = 99;
	bool Del;
	cout << "Welcome to our BookShop" << endl;
	while (key != 0)
	{
		key = Menu.PrintMainMenu();
		switch (key)
		{
		case 1: //Add new records
			File.AddToFile();
			break;
		case 2:
			File.ShowFromFile();
			break;
		case 3:
			Del = false;
			File.ModDelRecords(Del);
			break;
		case 4:
			Del = true;
			File.ModDelRecords(Del);
			break;
		}
	}
	system("pause");
	return 0;
}
