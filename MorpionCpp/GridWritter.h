#include <iostream>
using namespace std;

char grid[] = { '*', '|', '*', '|', '*', '\n', '*', '|', '*', '|', '*' , '\n', '*', '|', '*', '|', '*' };
char characters[] = { 'X', 'O' };

void PrintMorpionHelp()
{

}

void PrintMorpionGrid()
{
	for (int i = 0; i < 17; i++)
	{
		cout << grid[i];
	}
	cout << endl << endl;
}

void WriteMorpionCase(int choice, int playerId)
{
	int caseId = choice * 2;
	grid[caseId] = characters[playerId];
	PrintMorpionGrid();
}

