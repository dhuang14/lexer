/*
Asssignment 1
Tokens and Lexemes with FSM
Created by Gavin Shu on 9/11/19

 compiler test.cpp : This file contains the 'main' function. Program execution begins and ends there.
*/


// Define Libraries //

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fstream>

using namespace std;

void fsm(string);

int Keyword(char alp[]);

string readInFile(string fileName);



int Keyword(char alp[])
{
	char keywords[43][10] = { "auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while","whileend","bool","then","endif","doend","forend","input","output","and","or","function" };
	int i, flag = 0;

	// State selection by comparing input string with existing table ------//
	// If any acceptance state other than 0, will transition to next state //

	for (i = 0; i < 43; ++i) {
		if (strcmp(keywords[i], alp) == 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}


// Read From File //

string readInFile(string fileName) 
{

	ifstream file;
	file.open(fileName);

	if (!file) {
		cout << "Cannot find file name with " << fileName << endl;
		exit(1);
	}

	stringstream ss;

	ss << file.rdbuf();

	file.close();

	return ss.str();
}


int main(int argc, const char* argv[])
{
	fsm(readInFile("Test.txt"));

	// Output an exiting program instruction --------------//

	cout << "\nPlease press \"Enter\" to exit the program.\nThank you.\n";

	// Waiting for a keystroke (Enter) to exit the program //

	cin.get();

	return 0;
}


void fsm(string word)
{
	//word += " ";
	// Define variables and identifiers //
	int count = 0;
	int count2 = 0;
	char ch = word.at(0);
	char dig[15];
	char alp[15];
	char operators[] = "+-*/%=<>()&|~^";
	char separators[] = "()";
	int i, j = 0, k = 0;

	// Output file header //

	cout << "Token       |  " << "Lexeme\n____________|________\n            |\n";

	// While ch is not the last character in the file //

	cout << word.size() << "\n";

	while (count <= word.size())
	{
 		ch = word.at(count2);

		// Operators or Separators //

		for (i = 0; i < 14; ++i)
		{
			if (ch == operators[i])
			{
				cout << "Operator    |  " << ch << "\n";
				break;
			}
			else if (ch == separators[i])
			{
				cout << "Separator   |  " << ch << "\n";
				break;
			}
		}

		// FSM Starts Here //

		if (isalpha(ch)) // If the character is an alphabetical character, store the ch value into string alp and increment //
		{
			alp[j++] = ch;

			if (count == word.size())
			{
				alp[j] = '\0';
				j = 0;
				
				if (Keyword(alp) == 1)                                                 // Send string alp to FSM function and if accepted, output as Keyword ----------------------------//
				{
					cout << "Keyword     |  " << alp << "\n";
				}
				else                                                                   // Otherwise, will output as an identifier -------------------------------------------------------//
				{
					cout << "Identifier  |  " << alp << "\n";
				}
			}
		}
		else if ((ch == ' ' || ch == '\n' || ch == '.' || ch == '\0') && (j != 0)) // If the character is a delimiter or end of line and j is not zero, terminate string and reset j //
		{
			alp[j] = '\0';
			j = 0;

			if (Keyword(alp) == 1)                                                 // Send string alp to FSM function and if accepted, output as Keyword ----------------------------//
			{
				cout << "Keyword     |  " << alp << "\n";
			}
			else                                                                   // Otherwise, will output as an identifier -------------------------------------------------------//
			{
				cout << "Identifier  |  " << alp << "\n";
			}
		}
		else if (isdigit(ch) || ch == '.')                                         // Repeat a similar process for numbers...both integers and decimals -----------------------------//
		{
			dig[k++] = ch;

			if (count == word.size())
			{
				dig[k] = '\0';
				k = 0;
				
				cout << "Real        |  " << dig << "\n";
			}
		}
		else if ((ch == ' ' || ch == '\n' || ch == '\0') && (k != 0))
		{
			dig[k] = '\0';
			k = 0;

			cout << "Real        |  " << dig << "\n";
		}

		count++;
		count2 = count - 1;
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file