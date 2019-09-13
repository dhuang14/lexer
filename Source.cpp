#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void fsm(string);

int Keyword(char alp[]);

string readInFile(string fileName);

int main(int argc, const char argv[])
{
	fsm(readInFile("Text.txt"));

	return 0;
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

		if (count == word.size())
			return;

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

string readInFile(string fileName) {

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