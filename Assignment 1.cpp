/*
Asssignment 1
Tokens and Lexemes with FSM
Created by Gavin Shu on 9/11/19
*/


// Define Libraries //

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;


// Keyword FSM Function //

int Keyword(char alp[]) {
	char keywords[33][10] = { "auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while","whileend"};
	int i, flag = 0;

	// State selection by comparing input string with existing table ------//
	// If any acceptance state other than 0, will transition to next state //

	for (i = 0; i < 33; ++i) {
		if (strcmp(keywords[i], alp) == 0) 
		{
			flag = 1;
			break;
		}
	}

	return flag;
}


// ---------Main Function--------- //

int main() 
{
	
	// Define variables and identifiers //

	char ch;
	char dig[15];
	char alp[15];
	char operators[] = "+-*/%=<>()&|~^";
	char separators[] = "()";
	ifstream fin("test.txt");
	int i, j = 0, k = 0;

	// Open file results //

	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}

	// Output file header //

	cout << "Token       |  " << "Lexeme\n____________|________\n            |\n";

	// While ch is not the last character in the file //

	while (!fin.eof())
	{
		ch = fin.get();

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
		}
		else if ((ch == ' ' || ch == '\n' || ch== '.' || fin.eof()) && (j != 0)) // If the character is a delimiter or end of line and j is not zero, terminate string and reset j //
		{
			alp[j] = '\0';
			j = 0;

			if (Keyword(alp) == 1)                                               // Send string alp to FSM function and if accepted, output as Keyword ----------------------------//
				cout << "Keyword     |  " << alp << "\n";
			else                                                                 // Otherwise, will output as an identifier -------------------------------------------------------//
				cout << "Identifier  |  " << alp << "\n";
		}
		else if (isdigit(ch) || ch == '.')                                       // Repeat a similar process for numbers...both integers and decimals -----------------------------//
		{
			dig[k++] = ch;
		}
		else if ((ch == ' ' || ch == '\n' || fin.eof()) && (k != 0))
		{
			dig[k] = '\0';
			k = 0;

			cout << "Real        |  " << dig << "\n";
		}
		
	}

	// Output an exiting program instruction --------------//

	cout << "\nPlease press \"Enter\" to exit the program.\nThank you.\n";

	// Waiting for a keystroke (Enter) to exit the program //

	cin.get();

	fin.close();

	return 0;
}