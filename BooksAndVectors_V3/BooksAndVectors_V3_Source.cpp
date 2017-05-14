//Reads books from a file into a vector, and allows the user to search for and display the books

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//loads the passed in vector with the passed in file, then closes the file
void loadVector(ifstream &file, vector <string> &myVect);

//prints out the contents of the vector passed in
void printVector(const vector <string> &myVect);

//searches the passed in vector for the string passed in, and returns its location as an int. Returns a -999 if it couldn't find the book
int searchByTitle(const vector <string> &myVect, string title);

//searches the passed in vector for the string which coresponds to the number passed in. Throws an exception if the number passed in is too large.
string searchByNumber(const vector <string> &myVect, int i);

int main()
{
	bool keepLooping = true;
	string myString = "";

	//define a vector
	vector <string> bookVector;

	//get file ready
	ifstream input;
	input.open("Book_List2.txt");

	//load the vector
	loadVector(input, bookVector);

	while (keepLooping)
	{
		cout << "Would you like to search by title or by number?\nEnter t for title, n for number, or e to exit and view all book titles: ";
		cin >> myString;
		if (myString == "t")
		{
			cout << "Search by title mode activated\nPlease enter the name of the book you would like to find: ";
			getline(cin.ignore(), myString);
			int myInt = searchByTitle(bookVector, myString);
			if (myInt > 0)
			{
				cout << "That book is number " << myInt << " on our list!\n";
			}
			else if (myInt <= 0)
			{
				cout << "Sorry, but it appears as though that book is not in our database\n";
			}
		}
		else if (myString == "n")
		{
			cout << "Search by number mode activated\nPlease enter a number, and we'll tell you the title of the book in that place: ";

		}
		else if (myString == "e")
			keepLooping = false;
		else
			cout << "That's not a valid input!\n";

	}


	//cout << "Enter a title and I'll tell you where that book is in the list: ";
	//string myString;
	//getline(cin, myString);
	//cout << "that book is in spot " << searchByTitle(bookVector, myString);



	//print out the whole vector
	printVector(bookVector);
}

void loadVector(ifstream &file, vector <string> &myVect)
{
	string input;
	while (file.good())
	{
		getline(file, input);
		myVect.push_back(input);
	}
	file.close();
}

void printVector(const vector <string> &myVect)
{
	vector <string>::const_iterator i;
	for (i = myVect.cbegin(); i != myVect.cend(); i++)
		cout << *i << endl;
}

int searchByTitle(const vector <string> &myVect, string title)
{
	vector<string>::const_iterator i;
	for (i = myVect.cbegin(); i != myVect.cend(); i++)
	{
		if (*i == title)
		{
			return distance(myVect.cbegin(), i) + 1;
		}
	}
	return -999;
}

string searchByNumber(const vector <string> &myVect, int i)
{
	if (i > myVect.size())
		throw out_of_range("There aren't that many books in the vector!");
	return myVect.at(i);
}