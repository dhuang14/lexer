// compiler test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void fsm(string);

int Keyword(char alp[])
{
	char keywords[33][10] = { "auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while","whileend" };
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

int main()
{
	fsm("while (fahr < upper) a = 23.00 whileend");
}

void fsm(string word)
{
	word += " ";
	// Define variables and identifiers //
	int count = 0;
	char ch = word.at(0);
	char dig[15];
	char alp[15];
	char operators[] = "+-*/%=<>()&|~^";
	char separators[] = "()";
	int i, j = 0, k = 0;

	// Output file header //

	cout << "Token       |  " << "Lexeme\n____________|________\n            |\n";

	// While ch is not the last character in the file //

	while (ch != NULL)
	{
		ch = word.at(count);
		// Operators or Separators //

		for (i = 0; i < 14; ++i)
		{
			if (ch == operators[i])
			{
				cout << "Operator    |  " << ch << "\n";
				//count++;
				break;
			}
			else if (ch == separators[i])
			{
				cout << "Separator   |  " << ch << "\n";
				//count++;
				break;
			}
		}

		// FSM Starts Here //

		if (isalpha(ch)) // If the character is an alphabetical character, store the ch value into string alp and increment //
		{
			alp[j++] = ch;
			//count++;
		}
		else if ((ch == ' ' || ch == '\n' || ch == '.' || ch == '\0') && (j != 0)) // If the character is a delimiter or end of line and j is not zero, terminate string and reset j //
		{
			alp[j] = '\0';
			j = 0;

			if (Keyword(alp) == 1)                                               // Send string alp to FSM function and if accepted, output as Keyword ----------------------------//
			{
				cout << "Keyword     |  " << alp << "\n";
				//count++;
			}
			else                                                                 // Otherwise, will output as an identifier -------------------------------------------------------//
			{
				cout << "Identifier  |  " << alp << "\n";
				//count++;
			}
		}
		else if (isdigit(ch) || ch == '.')                                       // Repeat a similar process for numbers...both integers and decimals -----------------------------//
		{
			dig[k++] = ch;
			//count++;
		}
		else if ((ch == ' ' || ch == '\n' || ch == '\0') && (k != 0))
		{
			dig[k] = '\0';
			k = 0;

			cout << "Real        |  " << dig << "\n";
			//count++;
		}

		count++;
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
